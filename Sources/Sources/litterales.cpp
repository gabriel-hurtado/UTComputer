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
    if(s.begin()!=s.end() && *it<='Z' && *it>='A'){
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

Litterale* Expression::evaluer() const{
    QString newVal = value;
    newVal=newVal.remove(0,1);
    newVal=newVal.remove(newVal.length()-1,newVal.length());
    QString result = readToken(newVal);
    Controleur::donnerInstance().commande(result);
    return nullptr;
}

Litterale* Expression::getFromString(QString s){
    if(s[0]=='\'')
        return new Expression(s);
    else return nullptr;
}

QString Expression::readToken(QString s) const{
    QString::iterator it = s.begin();
    QString postfix;
    QStack<QString> stack;
    const QMap<QString, Operateur*> op_map = OperateurFactory::getMap();
    const QMap<QString,QString>& symbol_map = Controleur::getSymbolMap();

    bool found;
    QString endTarget;

    QString tmp;
    while(it!=s.end()){
        found=false;

        if(*it==' '){
            it++;
            continue;
        }

        if(tmp == "" && symbol_map.find(*it)!=symbol_map.end()){
            endTarget=symbol_map.find(*it).value();
            if(endTarget!=""){
                while(it!=s.end() && *it != endTarget){
                    tmp+=*it++;
                }
                if(*it!=endTarget)
                    throw LitteraleException("Mot " +endTarget + " non trouvé");
                tmp+=endTarget;
                postfix+=tmp+" ";
                endTarget.clear();
                tmp.clear();
                it++;
                found=true;
            }
        }

        //On tombe dans le cas ou on a une valeur
        while(it!=s.end() && ((*it<='9' && *it>='0') || (symbol_map.find(*it)!=symbol_map.end()))){


              tmp+=*it;
              if(it!=s.end())
                  it++;
        }
        //Pour vider ce qu'on a trouvé
        if(tmp!=""){
            postfix+=tmp+" ";
            tmp.clear();
            found=true;

        }



        //On tombe dans le cas d'un morçeau de texte
        if((*it<='Z' && *it>='A')){
            while(it!=s.end() && ((*it<='Z' && *it>='A') || (*it<='9' && *it>='0'))){
                tmp+=* it;
                if(it!=s.end())
                    it++;
            }
            if(isOperator(tmp)){
                found=true;
                while(!stack.empty() && stack.top() != "(" && CompareOperators(stack.top(),tmp)<=0){
                    postfix += stack.top()+" ";
                    stack.pop();
                }
            stack.push(tmp);
            tmp.clear();
            }
            else if(isVariable(tmp)){
                found=true;
                Litterale* l = VariablesManager::getVariable(tmp);
                if(estdeType<Programme>(l))
                    throw OperateurException("Un programme est dans l'expression !");

                QString rep = l->toString();
                int length_it = s.indexOf(tmp);
                s.replace(tmp,rep);
                it = s.begin();
                for(int i=0; i<length_it;i++,it++);
                tmp.clear();

            }
            else
                throw(LitteraleException("Le mot "+tmp+" est inconnu"));

        }

        if(*it=='('){
            stack.push(*it);
            if(it!=s.end())
                it++;
            found=true;
        }
        if(*it==')'){
            while(stack.top()!="("){
                postfix+= stack.top()+" ";
                stack.pop();
            }
            stack.pop();
            if(it!=s.end())
            it++;
            found=true;
        }
        //On tombe dans le cas d'un opérateur à caractère
        if(!found){
            while(it!=s.end() && !op_map.contains(tmp)){
                tmp+=*it++;
            }
            if(it==s.end() && !op_map.contains(tmp))
                throw LitteraleException("Expression non valide dès "+tmp);
            while(!stack.empty() && stack.top() != "(" && CompareOperators(stack.top(),tmp)<=0){
                postfix += stack.top()+" ";
                stack.pop();
            }
        stack.push(tmp);
        tmp.clear();
        }
    }

    while(!stack.empty()){
        postfix+= stack.top() + " ";
        stack.pop();
    }
    return postfix;
}
Litterale* Expression::getCopy() const{return new Expression(value);}

int Expression::CompareOperators(QString s1,QString s2) const{
    const QMap<QString, Operateur*> op_map = OperateurFactory::getMap();
    int a = op_map.find(s1).value()->getPriority();
    int b = op_map.find(s2).value()->getPriority();
    if(a>b) return -1;
    if(a<b) return 1;
    return 0;

}

bool Expression::isOperator(QString s) const {
    const QMap<QString, Operateur*> op_map = OperateurFactory::getMap();
    if( op_map.find(s)!=op_map.end())
        return true;
    return false;
}

bool Expression::isVariable(QString s) const {
    VariablesManager& varMan = VariablesManager::donnerInstance();
    varMan.getVariable(s);
    return true;
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
