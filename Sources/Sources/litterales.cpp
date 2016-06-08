#include "litterales.h"
#include "litteralefactory.h"
#include "litteraleexception.h"
#include "operateurfactory.h"
#include "controleur.h"
#include <QVector>

/*Définition des méthodes de la classe Litterale*/
Litterale* Litterale::traitement(){return nullptr;}


/*------------Définition des méthodes de la classe Réelle------------*/

Reelle::Reelle(const Entier& p,const Entier& m){
    /*Un réel ne peut pas être construit avec une mantisse nulle*/
    if(m.getValeur()==0){LitteraleException("Construction: Mantisse nulle !");}
    else{value=p.getValeur();
            double mantisse=(double)m.getValeur();
           while(mantisse>=1)
            mantisse=mantisse/10.0;
            value+=mantisse;}
}


    /*Simplification retourne une référence sur litterale numerique allouée dynaiquement*/
LitteraleNumerique& Reelle::Simplification(){
    LitteraleNumerique* ptr;
    if(getMantisse().getValeur()==0)
         ptr = new Entier(getPartieEntiere());
    else{
             ptr=this;
    }
    return *ptr;
}


LitteraleComplexe& Complexe::Simplification(){
    LitteraleComplexe* ptr;
    if(getPartieImaginaire()->getValeur()==0)
         ptr = estdeType<LitteraleComplexe>(getPartieReelle()->getCopy());
    else{
             ptr=this;
    }
    return *ptr;
}

const QString Reelle::toString() const {
    QString s;
        s.setNum(getValeur());
    return s;
}
Litterale* Reelle::getFromString(QString s){
    QStringList Ql = s.split('.');
    LitteraleFactory& LF = LitteraleFactory::donnerInstance();
    Entier* l1 = estdeType<Entier>(LF.creerRPNLitterale(Ql.at(0)));
    Entier* l2 = estdeType<Entier>(LF.creerRPNLitterale(Ql.at(1)));
    if(l1 && l2)
        return new Reelle(*l1,*l2);
    else
        throw LitteraleException(s+" n'est pas une Réelle valide");
}



/*------------Définition des méthodes de la classe Rationnel------------*/


Rationnel::Rationnel(int n, int d){
    if (d == 0)
        throw LitteraleException("Le dénominateur ne peut être nul !");
    else {
        int pg = pgcd(n, d);
        n = n / pg;
        d = d / pg;
        numerateur = n;
        denominateur = d;
        }
    }

const QString Rationnel::toString() const { std::stringstream s;
                                s << getNumerateur().getValeur() << "/" << getDenominator().getValeur();
                                return QString::fromStdString(s.str());
                                }

LitteraleNumerique& Rationnel::Simplification(){
    LitteraleNumerique* ptr;
    if(denominateur.getValeur()==1)
        ptr= new Entier(numerateur.getValeur());
    else
        ptr=this;
    return *ptr;
}


Reelle Rationnel::roundValue() const{
     double rounded= (numerateur.getValeur()/(double)(denominateur.getValeur()));
     return Reelle(0,(int)(rounded));
}

Litterale* Rationnel::getFromString(QString s){
    QStringList Ql = s.split('/');
    return new Rationnel(Ql.at(0).toInt(),Ql.at(1).toInt());
}


/*------------Définition des méthodes de la classe Entier------------*/
Litterale* Entier::getFromString(QString ){
    throw LitteraleException("Création d'entier depuis la factory");
    return nullptr;
}



/*------------Définition des méthodes de la classe Complexe------------*/
const QString Complexe::toString() const{
    QString s;
    s+=p_reelle.toString();
    s+='$';
    s+=p_imaginaire.toString();
    return s;
}
Litterale* Complexe::getFromString(QString s){
    QStringList Ql = s.split('$');
    LitteraleFactory& LF = LitteraleFactory::donnerInstance();
    LitteraleNumerique* l1 = estdeType<LitteraleNumerique>(LF.creerInfixLitterale(Ql.at(0)));
    LitteraleNumerique* l2 = estdeType<LitteraleNumerique>(LF.creerInfixLitterale(Ql.at(1)));
    if(l1 && l2)
        return new Complexe(*l1,*l2);
    else
        throw LitteraleException(s+" n'est pas un Complexe valide");
}


/*------------Définition des méthodes de la classe Atome------------*/

Atome::Atome(QString n){
    if(isValidAtomeName(n))
        nom=n;
    else
        throw LitteraleException("Nom d'atome invalide");
}


bool Atome::isValidAtomeName(QString s){
    QString::iterator it = s.begin();
    //Avant de vérifier quoi que ce soit on vérifie le la string ne désigne pas un opérateur
    if(OperateurFactory::getMap().find(s)!=OperateurFactory::getMap().end())
        return false;

    //On vérifie que le premier caractère est une majuscule;
    if(s.begin()!=s.end() && *it<'Z' && *it>'A'){
        //On doit alors vérifier que tout les caractères ne sont que des lettres majuscules ou des chiffres
        while(it!=s.end()){
            if(('A'<=*it && *it<='Z') || ('0'<=*it && *it<='9')){
                it++;
                continue;
            }
            else
                return false;
        }
        return true;
    }
    //Si le premier caractère n'est pas une lettre majuscule, alors ce ne peut pas être un nom d'atome
    else
        return false;
}

Litterale* Atome::getCopy() const{return new Atome(nom);}

QString const Atome::toString() const {
    try{
        return nom;//VariablesManager::donnerInstance().getVariable(nom);
    }
    catch(LitteraleException& e){
        return nom;
    }
}



/*------------Définition des méthodes de la classe Expression------------*/

/*utile pour EVAL, on prend la QString, on la parse de manière infixe, et on esaaye de trouver la valeur numérique.
ne pas hésiter a lancer des exceptions si un atome référence un programme ou si un atome ne correspond pas au
nom d'une variable
!!n'utilise pas la pile*/

//donne l'indice de début de la parenthèse la plus profonde
int indexOfDeepestParentheses(QString s, bool* hasPar){
    int temp=0;
     int ouvert=0;
     QVector<bool> vectok(30,true);
     int nb=0;
     *hasPar= false;

        int maxProf=0;
        do{

            if(s.mid(temp,1)=="("){
                *hasPar=true;
               maxProf=temp;
               vectok[ouvert]=false;
               ouvert++;
            }
            else if(s.mid(temp,1)==")"){
                ouvert--;
                vectok[ouvert]=true;

           }
            temp++;
        }while(temp<s.length());

        foreach (bool val, vectok) {
            if(!val){
                throw LitteraleException("Parenthésage incorrect");
            }
        }

    return maxProf;

}

int getLengthOfSubExp(QString s,int begin_at){
    int res=0;
    do{
        res++;
    }while(s.mid(begin_at+res,1)!=")");
    return res;
}


//Pour le moment dépille la littérale si son parenthésage est correct
LitteraleComplexe* Expression::evaluer() const{
    QString newVal = value;
    newVal=newVal.remove(0,1);
    newVal=newVal.remove(newVal.length()-1,newVal.length());
    bool* hasPar= new bool(false);
    int begin_at= indexOfDeepestParentheses(newVal,hasPar);
    QString sub;

    while(*hasPar){ //tant qu'il reste des "choses" parenthésées dans la value
        int length= getLengthOfSubExp(newVal,begin_at);
        sub= newVal.mid(begin_at+1,length-1);
        //traiter sub et modifier newVal en conséquence, du coup begin at va diminuer
        LitteraleComplexe* resTempExp= Expression("\""+sub+"\"").evaluer();
        //remplacer la partie de newVal correspondant a sub par resTempExp
        newVal=newVal.mid(0,begin_at)+resTempExp->toString()+newVal.mid(begin_at+length+1,sub.length());
        //en attendant
        begin_at= indexOfDeepestParentheses(newVal,hasPar);

    }
    //newVal de la forme 2*8+3 (pas de parenthèses)
    return new Entier(1);
}

Litterale* Expression::getCopy() const{return new Expression(value);}


/*------------Définition des méthodes de la classe Programme------------*/

Litterale* Programme::getCopy() const{return new Programme(valeur);}
Litterale* Programme::traitement(){
    QString tmp = valeur;
    tmp=tmp.remove(0,1);
    tmp=tmp.remove(tmp.length()-1,tmp.length());
    Controleur::donnerInstance().commande(tmp);
    return nullptr;
}
