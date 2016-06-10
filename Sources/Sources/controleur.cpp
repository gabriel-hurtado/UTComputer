#include "controleur.h"
#include "pile.h"
#include "litteralefactory.h"
#include "operateurfactory.h"
#include "operateur.h"
#include "wordidentifier.h"
#include "litteraleexception.h"
#include "operateursexpressions.h"

Controleur* Controleur::instanceControleur=nullptr;

//Map qui contient les symboles des opérateurs
QMap<QString,QString> Controleur::symbolMap = QMap<QString,QString>();

QMap<QString,WordIdentifier*> Controleur::interpretationMap = QMap<QString,WordIdentifier*>();


Controleur& Controleur::donnerInstance(){
    if(instanceControleur==nullptr)
        instanceControleur= new Controleur;
    return *instanceControleur;
}

void Controleur::libererInstance(){
    if(instanceControleur!=nullptr)
        delete instanceControleur;
}


Controleur::Controleur(){}
Controleur::~Controleur(){}




bool Controleur::commande(QString& s,QString litterale_mode){
    // On extraie le mot que l'on veut
    QString word = firstWord(s);

    if(word==""){return true;} //On a bien terminé tous les mots [CONDITION D'ARRET]

    else{
            /*
                On tente de fabriquer une littérale a partir du mot, si on recoie nullptr alors ce n'en n'est pas une
            */
            Litterale* l;
            if(litterale_mode == "RPN")
               l = LitteraleFactory::donnerInstance().creerRPNLitterale(word);
            else if(litterale_mode == "INFIX")
                l = LitteraleFactory::donnerInstance().creerInfixLitterale(word);
            if(l){
                    Atome* a= estdeType<Atome>(l);
                        if(a){
                            expression::OperateurUserMade op = expression::OperateurUserMade(a);

                             op.traitementOperateur();


                        }
                        else{
                            Pile::donnerInstance()<<*l;
                        }

                }

            /*
                Idem, mais avec un opérateur. Si on reçoit null c'est que ce n'est pas un opérateur
                Il faut bien faire attention à vérrouiler la pile pour éviter les sauvegardes
            */

            Operateur* op = OperateurFactory::donnerInstance().creer(word);
            Pile::donnerInstance().setAtomicLock(true);
            if(op){
                //Seul morçeau de code statique [A CHANGER SI POSSIBLE]
                if(word!="UNDO" && word!= "REDO")Pile::donnerInstance().sauverPile();

                op->operation();}
            Pile::donnerInstance().setAtomicLock(false);

            /*
                Dans le cas ou ce n'était ni l'un ni l'autre, alors l'execution du mot a échoué
            */
            if(!op && !l){return false;}

            /*
                On peut en fin se permettre d'enlever le mot de la string vu que celui-ci à bien été executé.
            */
            s=s.remove(0,(s.indexOf(word)+word.length()));

            /*
                [APPEL RÉCURSSIF]
                Sinon, si la commande suivante est valide, on valide la notre, la commande vide étant par défaut valide mais inutile
            */
            if(commande(s))
                return true;
            return false;
        }
}

/**
 * @brief Permet de sauter le contenu des parenthèses
 * Utile lors d'opérations entre expressions
 * @param start indice du début de la partie de la chaine s à considérer
 * @param s la chaine dont il faut ignorer une partie
 * @return l'indice à partir duquel la parenthèse est fermée (si il y en avait), start sinon
 */

int skipParentheses(int start,QString s){
    int temp=start;

    if(s.mid(temp,1)=="("){
        int nb=0;
        do{
            if(s.mid(temp,1)!=")")
                nb--;
            if(s.mid(temp,1)!="(")
                nb++;
            temp++;
        }while(nb!=0 && temp<500);
        if(temp>=500)
            throw LitteraleException("Erreur de parenthèses","Expression");
        temp+=1;
    }
    return temp;
}


QString Controleur::ParenthesisCleaner(QString s, unsigned int priority){
    //  s="(5+8+9-7)" ici avoir d'une manière ou d'une autre la première littérale dans word


    int start =1;

     int i;
    bool can_clear=true;
     QString sub;

     //cas litterale premiere

    do{
         start= skipParentheses(start,s);
         Litterale* l=nullptr,* l2=nullptr ;

         Operateur* op;
         i=0;


         if( s.length()-2<=start) break;
            do{
            i++;
            sub= s.mid( start, i);
            try{
            l = LitteraleFactory::donnerInstance().creerInfixLitterale(sub);
            }
            catch (LitteraleException e){
                if(e.getType()!="Reelle" && e.getType()!="Complexe" && e.getType()!="Rationnel")
                    throw e;
                l=nullptr;
                if( e.getType()=="Rationnel")
                    break;
            }
            if(!l){
                int j=i+1;
                try{
                l2 = LitteraleFactory::donnerInstance().creerInfixLitterale(s.mid( start, j));}
                catch (LitteraleException e){
                    if(e.getType()!="Reelle" && e.getType()!="Complexe" && e.getType()!="Rationnel")
                        throw e;
                    l2=nullptr;
                }
                if(l2){
                    i=j;
                    l=l2;
                }
            }

            }while(l && s.length()-2>start+i);

         if( s.length()-2<=start+i) break;

            op = OperateurFactory::donnerInstance().creer(sub);
            if(op) //si c'était en fait un opérateur
            {
                if(priority!=op->getPriority()){
                    can_clear=false;
                    break;
                }

                start+=i;

            }
            else
            start+=i-1;



            /*On est a l'eventuel opérateur
            */



            start= skipParentheses(start,s);


            i=0;

            if( s.length()-2<=start) break;
            do{
            i++;
            sub= s.mid( start, i);
            op = OperateurFactory::donnerInstance().creer(sub);
             if( s.length()-2<=start) break;
            }while(!op && i<20);

            if (i>=20) throw LitteraleException("Expression invalide !","Expression");

            if(priority!=op->getPriority()){
                can_clear=false;
                break;
            }

            start=start+i;

     }while(can_clear || s.length()-2<=start);

     QString tmp = QString(s);
    if(can_clear)
    {
        tmp=tmp.remove(0,1);
        tmp=tmp.remove(tmp.length()-1,tmp.length());
    }
    return tmp;
}


void Controleur::enregistrerSymbole(QString ltok, QString rtok, WordIdentifier* W){
    QMap<QString,QString>::iterator it_map = symbolMap.find(ltok);
    if(it_map==symbolMap.end()){
        symbolMap[ltok]=rtok;
        interpretationMap[ltok]=W;
    }
}

QString Controleur::SpaceCleaner(QString s){
    while(*(s.begin())==' '){
        s=s.remove(0,1);
        continue;
    }
    return s;
}


QString Controleur::firstWord(QString s){


    //On nettoie les espaces à gauche
    s=SpaceCleaner(s);

    //On arrive ici quand il n'y a plus d'espace à gauche


    //Dans le cas ou c'est la fin on renvoie la vide
    if(s.begin()==s.end())
        return "";

    //Dans les autres cas il faut savoir ou on s'arrete
    //On initialise pour cela notre curseur
    SelectedPosition _cursor(s.begin(),s.begin());
    _cursor.it_fin++;

    //On initialise aussi un booleén quand on a trouvé
    bool found = false;

    //Il faut commencer dans l'ordre de priorité des opérateurs
    const QMap<unsigned int, QString>& prioMap = LitteraleFactory::getPriorityMap();
    QMap<unsigned int, QString>::const_iterator it_map = prioMap.begin();
    while(it_map!=prioMap.end() && !found){
        WordIdentifier* _currentWordIdentifier = interpretationMap.find(it_map.value()).value();
        if(_currentWordIdentifier->WordGuesser(s)){
            _currentWordIdentifier->WordPosition(s,_cursor);
            found=true;
        }
        it_map++;
    }

    //Maintenant notre premier mot est borné entre it_debut et it_fin
    QString ret("");
    for(;_cursor.it_debut!=_cursor.it_fin;_cursor.it_debut++)
       ret+=*_cursor.it_debut;
    return ret;

}



