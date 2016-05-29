

#ifndef H_LITTERALE
#define H_LITTERALE
#include "operande.h"
#include <math.h>

/*
 Classe pour gérer les exceptions sur les littérales
 Ces messages sont utile pour notre GUI (?)
*/
class LitteraleException : public std::exception
{
    std::string info;
public:
    LitteraleException (std::string in) : info(in) {}
    const std::string	getMessage() { return info; }
};




/*------------Classes "Litterales" abstraites------------*/

class Litterale : public Operande
{
public:
    Litterale() {}
    virtual ~Litterale() {}
    /*Template method pour afficher utilisant toString()*/
    std::ostream& afficher(std::ostream& f=std::cout){f<<toString();return f;}
    virtual const std::string toString() const = 0;
    virtual Litterale* getCopy() const = 0;
    Litterale* traitement(){return nullptr;}

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
private:

};

/*
    Fonction Template pour connaitre les types des objets :
    L'objet de type T est-il de type L ?
*/
template<typename L> L* estdeType(Litterale* Tobj){
    L* Lobj;
    if(Tobj==nullptr)

        return nullptr;
    if((Lobj=dynamic_cast<L*>(Tobj)))
        return Lobj;
    return nullptr;

}




/*------------Classe Litterale Entier------------*/

class Entier : public LitteraleNumerique {

    int valeur;
public:
    Entier(int v=0) :valeur(v) {}
    virtual ~Entier() {}
    int getValeur() const { return valeur; }
    const std::string toString() const { return std::to_string(getValeur());}
    LitteraleComplexe* neg(){Entier* res =getNumericCopy(); res->valeur=-res->valeur; return res;}
    Entier* getNumericCopy() const{return new Entier(*this);}

};



/*------------Classe Litterale Reelle------------*/

class Reelle : public LitteraleNumerique{
    double value;
public:


    /*La partie entiere dit etre le second paramêtre pour avoir une valeur par défaut*/
    Reelle(double d):value(d){}

    Reelle(const Entier& m,const Entier& p){
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
    const std::string toString() const;


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
    const std::string toString() const;
    LitteraleNumerique& Simplification();
    Reelle roundValue() const;

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
    const std::string toString() const;


};



/*------------Classe Litterale Atome------------*/
class Atome : public LitteraleSimple{
    std::string nom;
public:
    Atome(std::string n);
    std::string getNom() const {return nom;}
    const std::string toString() const {return getNom();}
    Litterale* getCopy() const;
    static bool isValidAtomeName(std::string s);
};

/*------------Classe Litterale Expression------------*/

class Expression : public Litterale{
    std::string value;
public:
    Expression(std::string v):value(v){}
    std::string getExpression() const {return value;}
    const std::string toString() const {return getExpression();}
    LitteraleComplexe* evaluer() const;
    Litterale* getCopy() const;
};


/*------------Classe Litterale Programme------------*/


class Programme : public Litterale{
    std::string valeur;
public:
    Programme(std::string p):valeur(p){}
    std::string getProgramme() const {return valeur;}
    const std::string toString() const {return getProgramme();}
    Litterale* getCopy() const;
};

#endif
