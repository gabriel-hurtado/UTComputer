

#ifndef H_LITTERALE
#define H_LITTERALE
#include "operande.h" //Pour savoir ce que sont des opérandes pour l'héritage
#include "litteralefactory.h" //
#include "litteraleexception.h"


/*------------Classes "Litterales" abstraites------------*/

class Litterale : public Operande
{
public:
    Litterale() {}
    virtual ~Litterale() {}
    /*Template method pour afficher utilisant toString()*/
    std::ostream& afficher(std::ostream& f=std::cout){f<<toString().toStdString();return f;}
    virtual const QString toString() const = 0;
    virtual Litterale* getCopy() const = 0;
    virtual Litterale* getFromString(QString s) = 0;
    virtual Litterale* traitement();

private:

};


class LitteraleSimple : public Litterale
{
public:
    LitteraleSimple() {}
    virtual ~LitteraleSimple() {}
private:

};

class LitteraleComplexe : public LitteraleSimple
{
public:
    LitteraleComplexe() {}
    virtual ~LitteraleComplexe() {}

    virtual LitteraleComplexe* neg() =0;


private:

};

class LitteraleNumerique : public LitteraleComplexe
{
public:
    LitteraleNumerique() {}
    virtual ~LitteraleNumerique() {}
    virtual LitteraleNumerique* getNumericCopy() const =0;
    Litterale* getCopy() const {return getNumericCopy();}
    virtual double getValeur() const=0;
private:

};






/*------------Classe Litterale Entier------------*/

class Entier : public LitteraleNumerique {

    int valeur;
public:
    Entier(int v=0) :valeur(v) {}
    virtual ~Entier() {}
    double getValeur() const { return (double)valeur; }
    const QString toString() const {QString s; return s.setNum(getValeur());}
    LitteraleComplexe* neg(){Entier* res =getNumericCopy(); res->valeur=-res->valeur; return res;}
    Entier* getNumericCopy() const{return new Entier(*this);}
    Litterale* getFromString(QString ){throw LitteraleException("Création d'entier depuis la factory"); return nullptr;}//Cas spécial

};



/*------------Classe Litterale Reelle------------*/

class Reelle : public LitteraleNumerique{
    double value;
public:


    /*La partie entiere dit etre le second paramêtre pour avoir une valeur par défaut*/
    Reelle(double d):value(d){}

    Reelle(const Entier& p,const Entier& m){
        /*Un réel ne peut pas être construit avec une mantisse nulle*/
        if(m.getValeur()==0){LitteraleException("Construction: Mantisse nulle !");}
        else{value=p.getValeur();
                double mantisse=(double)m.getValeur();
               while(mantisse>=1)
                mantisse=mantisse/10.0;
                value+=mantisse;}
    }

    Reelle(int x,int y=0):Reelle( Entier(x), Entier(y)){}
    virtual ~Reelle(){}
    Entier getPartieEntiere() const{return Entier(floor(value));}
    Entier getMantisse()const {
        double res=value-floor(value);
                               if(res==0)
                                   return 0;
                           while(res-floor(res)!=0){
                               res=res*10;
                           }
                           return Entier((int)res);}
    LitteraleNumerique& Simplification();
    double  getValeur()const {return value;}
    LitteraleComplexe* neg(){Reelle* res=getNumericCopy(); res->value=-res->value;return res;}
    Reelle* getNumericCopy() const{return new Reelle(*this);}
    const QString toString() const;
    Litterale* getFromString(QString s);


};

/*------------Classe Litterale Rationnel------------*/

class Rationnel : public LitteraleNumerique
{
protected:
    Entier numerateur;
    Entier denominateur;
public:
    Rationnel(int n, int d=1);
    Rationnel(const Entier& n, const Entier& d) { Rationnel(n.getValeur(), d.getValeur()); }
    virtual ~Rationnel(){ }
    Entier getNumerateur() const { return numerateur; }
    Entier getDenominator() const { return denominateur; }

    LitteraleComplexe* neg(){Rationnel* res=getNumericCopy(); res->numerateur.neg();return res;}
    Rationnel* getNumericCopy() const{return new Rationnel(*this);}
    const QString toString() const;
    LitteraleNumerique& Simplification();
    Reelle roundValue() const;
    double getValeur() const{return roundValue().getValeur();}
    Litterale* getFromString(QString s);

};

/*------------Classe Litterale Complexe------------*/

class Complexe : public LitteraleComplexe{
    LitteraleNumerique& p_reelle;
    LitteraleNumerique& p_imaginaire;
public:
    /*Le comportement par défaut du constructeur est suffisant car pas de pointeur*/
    Complexe(LitteraleNumerique& pR,LitteraleNumerique& pI):p_reelle(*pR.getNumericCopy()),p_imaginaire(*pI.getNumericCopy()){}
    LitteraleNumerique* getPartieReelle() const {return p_reelle.getNumericCopy();}
    LitteraleNumerique* getPartieImaginaire() const {return p_imaginaire.getNumericCopy();}

    LitteraleComplexe* neg(){Complexe* res=getCopy(); res->p_reelle.neg();return res;}
    Complexe* getCopy() const {return new Complexe(p_reelle,p_imaginaire);}
    const QString toString() const;
    Litterale* getFromString(QString s);
    LitteraleComplexe& Simplification();

};



/*------------Classe Litterale Atome------------*/
class Atome : public LitteraleSimple{
    QString nom;
public:
    Atome(QString n);
    QString getNom() const {return nom;}
    const QString toString() const {return getNom();}
    Litterale* getCopy() const;
    static bool isValidAtomeName(QString s);
    Litterale* getFromString(QString s){return new Atome(s);}
};

/*------------Classe Litterale Expression------------*/

class Expression : public Litterale{
    QString value;
public:
    Expression(QString v):value(v){}
    QString getExpression() const {return value;}
    const QString toString() const {return getExpression();}
    LitteraleComplexe* evaluer() const;
    Litterale* getCopy() const;
    Litterale* getFromString(QString s){return new Expression(s);}
    const QString getExpressionNoBorders() const{

                                                    QString tmp = QString(value);
                                                    tmp=tmp.remove(0,1);
                                                    tmp=tmp.remove(tmp.length()-1,tmp.length());
                                                    return tmp;
                                                }
};


/*------------Classe Litterale Programme------------*/


class Programme : public Litterale{
    QString valeur;
public:
    Programme(QString p):valeur(p){}
    QString getProgramme() const {return valeur;}
    const QString toString() const {return getProgramme();}
    Litterale* getCopy() const;
    Litterale* getFromString(QString s){return new Programme(s);}
    Litterale* traitement() override; //parse le programme et fait les différentes opérations, par ex + avec un élément de la pile
};

#endif
