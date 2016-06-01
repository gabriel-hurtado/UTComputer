#include "litterales.h"
#include "utils.h"
#include "operateursnumeriques.h"
#include <QTextStream>


/*Définition des méthodes de la classe Litterale*/


/*------------Définition des méthodes de la classe Réelle------------*/

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


const QString Reelle::toString() const {
    QString s;
        s.setNum(getValeur());
    return s;
}
Litterale* Reelle::getFromString(QString s){
    QStringList Ql = s.split('.');
    return new Reelle(Ql.at(0).toInt(),Ql.at(1).toInt());
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
    LitteraleNumerique* l1 = estdeType<LitteraleNumerique>(LF.creer(Ql.at(0)));
    LitteraleNumerique* l2 = estdeType<LitteraleNumerique>(LF.creer(Ql.at(1)));
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
    QString::iterator it=s.begin();
    //On vérifie que le premier caractère est une majuscule;
    if(s.begin()!=s.end() && *it<'Z' && *it>'A'){
        //On doit alors vérifier que tout les caractères ne sont que des lettres majuscules ou des chiffres
        while(it!=s.end()){
            if(('A'<=*it && *it<='Z') || ('0'<=*it && *it<='9'))
                continue;
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



/*------------Définition des méthodes de la classe Expression------------*/

LitteraleComplexe* Expression::evaluer() const{ return nullptr;}

Litterale* Expression::getCopy() const{return new Expression(value);}


/*------------Définition des méthodes de la classe Expression------------*/

Litterale* Programme::getCopy() const{return new Programme(valeur);}
