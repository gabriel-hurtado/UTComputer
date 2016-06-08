#include "litterales.h"
#include "litteralefactory.h"
#include "litteraleexception.h"
#include "operateurfactory.h"
#include "operateur.h"
#include "controleur.h"
#include "variable.h"
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
Litterale* Entier::getFromString(QString s){
    return new Entier(s.toInt());
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


//Pour le moment dépile la littérale si son parenthésage est correct
Litterale* Expression::evaluer() const{
    QString newVal = value;
    newVal=newVal.remove(0,1);
    newVal=newVal.remove(newVal.length()-1,newVal.length());


    /*
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
    */
    //newVal de la forme 2*8+3 (pas de parenthèses), plus qu'a l'interpréter
    //Partie interprétation
    return new Expression(readToken(newVal));


/*
    QString::iterator it = newVal.begin();

    QString _toTreat(""); //Qstring which has the first Litterale/Operator
    QString _toTest("");
    QString _Resultat("");

    bool foundThisSymbol = false;

    //Récupération de la
    LitteraleFactory& LF (LitteraleFactory::donnerInstance());
    VariablesManager& varMan = VariablesManager::donnerInstance();
    const QMap<QString,Litterale*>& litterale_map(LitteraleFactory::getLitteraleMap());
    const QMap<QString, WordIdentifier*>& interpretation_map(Controleur::getInterpretationMap());

    //3$7+4$5
    while(it!=newVal.end()){
        foundThisSymbol = false;
        _toTest+=*it;

        //Cas d'un nombre toujours bon
        if(*it<'9' && *it>'0'){
            foundThisSymbol = true;
        }
        else if(interpretation_map.find(*it).value()->WordGuesser(_toTest)){//Si le symbole est interprétable
            Litterale* l = LF.getRPNExampleOf(_toTest); //On essaye de savoir ce que c'est comme litterale
            if(l){ //Si c'est bien une litterale
                if(estdeType<Atome>(l)){
                    try{
                    Litterale* l_atome = varMan.getVariable(_toTreat);

                    }
                    catch(LitteraleException& e){
                        throw("L'atome "+_toTreat+"n'identifie pas de variable");
                    }
                }
                else
                    _toTreat=*it++; //On peut l'ajouter serenement à _toTreat
            }
            //Dans l'autre cas, _toTest n'as plus de sens et on empile _toTreat qui lui en avait
            else{
                //Si c'est un atome alors il doit être valide

                _Resultat+=_toTreat;
                _Resultat+=" ";
                _toTreat.clear();
                _toTest.clear();
                it++;
                continue;
            }

        }

    }*/
}
//3+5*7 -> 3 5 7 * +
QString Expression::readToken(QString s) const{
    QString::iterator it = s.begin();
    QString postfix;
    QStack<QString> stack;
    const QMap<QString, Operateur*> op_map = OperateurFactory::getMap();
    const QMap<QString,Litterale*>& litterale_map(LitteraleFactory::getLitteraleMap());
    bool found;

    QString tmp;
    while(it!=s.end()){

        if(*it==' ')
            continue;

//4+4*7 4 4 7 * +
        //On tombe dans le cas ou on a une valeur
        while(it!=s.end() && ((*it<'9' && *it>'0') || (litterale_map.find(*it))!=litterale_map.end())){
              tmp+=*it;
              if(it!=s.end())
                  it++;
        }
        //Pour vider ce qu'on a trouvé
        if(tmp!=""){
            postfix+=tmp+" ";
            tmp.clear();
        }
        //On tombe dans le cas d'un opérateur d'un seul caractère
        if(isOperator(*it)){

            while(!stack.empty() && stack.top() != "(" && CompareOperators(stack.top(),*it)<=0){
                postfix += stack.top()+" ";
                stack.pop();
            }
        stack.push(*it);
        if(it!=s.end())
            it++;
        }


        //On tombe dans le cas d'un morçeau de texte
        if((*it<='Z' && *it>'A')){
            while(it!=s.end() && ((*it<='Z' && *it>'A') || (*it<'9' && *it>'0'))){
                tmp+=* it;
                if(it!=s.end())
                    it++;
            }
            if(isOperator(tmp)){
                while(!stack.empty() && stack.top() != "(" && CompareOperators(stack.top(),tmp)<=0){
                    postfix += stack.top()+" ";
                    stack.pop();
                }
            stack.push(tmp);
            }

        }

        if(*it=='('){
            stack.push(*it);
            if(it!=s.end())
                it++;
        }
        if(*it==')'){
            while(stack.top()!="("){
                postfix+= stack.top()+" ";
                stack.pop();
            }
            stack.pop();
            if(it!=s.end())
                it++;
        }
    }

    while(!stack.empty()){
        postfix+= stack.top() + " ";
        stack.pop();
    }
    std::cout<< postfix.toStdString();
    return postfix;
}
Litterale* Expression::getCopy() const{return new Expression(value);}

int Expression::CompareOperators(QString s1,QString s2) const{
    const QMap<QString, Operateur*> op_map = OperateurFactory::getMap();
    int a = op_map.find(s1).value()->getPriority();
    int b = op_map.find(s2).value()->getPriority();
    if(a>b) return -1;
    if(a==b) return 0;
    if(a<b) return 1;
}

bool Expression::isOperator(QString s) const {
    const QMap<QString, Operateur*> op_map = OperateurFactory::getMap();
    if( op_map.find(s)!=op_map.end())
        return true;
    return false;
}

/*------------Définition des méthodes de la classe Programme------------*/

Litterale* Programme::getCopy() const{return new Programme(valeur);}
Litterale* Programme::traitement(){
    QString tmp = valeur;
    tmp=tmp.remove(0,1);
    tmp=tmp.remove(tmp.length()-1,tmp.length());
    Controleur::donnerInstance().commande(tmp);
    return nullptr;
}
