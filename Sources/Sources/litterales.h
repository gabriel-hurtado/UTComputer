

#ifndef H_LITTERALE
#define H_LITTERALE
#include "operande.h" //Pour savoir ce que sont des opérandes pour l'héritage

//Forward declarations
class LitteraleFactory;




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
    virtual Litterale* getFromString(QString s) const = 0;
    virtual Litterale* traitement() const;

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

    virtual LitteraleComplexe* neg() const =0;


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
    const QString toString() const {return QString::number(valeur);}
    LitteraleComplexe* neg() const {Entier* res =getNumericCopy(); res->valeur=-res->valeur; return res;}
    Entier* getNumericCopy() const{return new Entier(*this);}
    Litterale* getFromString(QString) const;//Cas spécial impossible normalement

};



/*------------Classe Litterale Reelle------------*/

class Reelle : public LitteraleNumerique{
    double value;
public:


    /*La partie entiere dit etre le second paramêtre pour avoir une valeur par défaut*/
    Reelle(double d):value(d){}

    Reelle(const Entier& p,const Entier& m);

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
    LitteraleComplexe* neg() const{Reelle* res=getNumericCopy(); res->value=-res->value;return res;}
    Reelle* getNumericCopy() const{return new Reelle(*this);}
    const QString toString() const;
    Litterale* getFromString(QString s) const;


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
    virtual ~Rationnel(){}
    Entier getNumerateur() const { return numerateur; }
    Entier getDenominator() const { return denominateur; }

    LitteraleComplexe* neg() const{Rationnel* res=getNumericCopy(); res->numerateur.neg();return res;}
    Rationnel* getNumericCopy() const{return new Rationnel(*this);}
    const QString toString() const;
    LitteraleNumerique& Simplification();
    Reelle roundValue() const;
    double getValeur() const{return roundValue().getValeur();}
    Litterale* getFromString(QString s) const;

};

/*------------Classe Litterale Complexe------------*/

class Complexe : public LitteraleComplexe{
    LitteraleNumerique& p_reelle;
    LitteraleNumerique& p_imaginaire;
public:
    /*Le comportement par défaut du constructeur est suffisant car pas de pointeur*/
    Complexe(LitteraleNumerique& pR,LitteraleNumerique& pI):p_reelle(*pR.getNumericCopy()),p_imaginaire(*pI.getNumericCopy()){}
    virtual ~Complexe(){
        delete &p_reelle;
        delete &p_imaginaire;
    }
    Complexe(Complexe& e):p_reelle(*e.getPartieReelle()),p_imaginaire(*e.getPartieImaginaire()){}
    Complexe operator=(Complexe& e);
    LitteraleNumerique* getPartieReelle() const {return p_reelle.getNumericCopy();}
    LitteraleNumerique* getPartieImaginaire() const {return p_imaginaire.getNumericCopy();}

    LitteraleComplexe* neg() const{Complexe* res=getCopy(); res->p_reelle.neg();return res;}
    Complexe* getCopy() const {return new Complexe(p_reelle,p_imaginaire);}
    const QString toString() const;
    Litterale* getFromString(QString s) const;
    LitteraleComplexe& Simplification();

};



/*------------Classe Litterale Atome------------*/
class Atome : public LitteraleSimple{
    QString nom;
public:
    Atome(QString n);
    virtual ~Atome(){}
    QString getNom() const {return nom;}
    const QString toString() const;
    Litterale* getCopy() const;
    static bool isValidAtomeName(QString s);
    Litterale* getFromString(QString s) const{return new Atome(s);}
};

/*------------Classe Litterale Expression------------*/

class Expression : public Litterale{
    QString value;

public:

    int CompareOperators(QString,QString) const;

    bool isOperator(QString) const;

    bool isVariable(QString s) const ;

    Expression(QString v):value(v){}
    virtual ~Expression(){}
    QString getExpression() const {return value;}
    const QString toString() const {return getExpression();}
    Litterale* evaluer() const;
    Litterale* getCopy() const;
    Litterale* getFromString(QString s) const;
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
    virtual ~Programme(){}
    QString getProgramme() const {return valeur;}
    const QString toString() const {return getProgramme();}
    Litterale* getCopy() const;
    Litterale* getFromString(QString s) const{
        if(s[0]=='[')
            return new Programme(s);
        else
            return nullptr;
    }

    Litterale* traitement() const override; //parse le programme et fait les différentes opérations, par ex + avec un élément de la pile
};

#endif
