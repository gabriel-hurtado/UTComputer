#include "operande.h"

#ifndef H_LITTERALE
#define H_LITTERALE


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
	virtual ~Litterale() {};
    /*Template method pour afficher utilisant toString()*/
    void afficher(std::ostream& f=std::cout){f<<toString();}
    virtual const std::string toString() const = 0;
    //virtual Litterale* getCopy() const= 0;

private:

};


class LitteraleSimple : public Litterale
{
public:
	LitteraleSimple() {}
	virtual ~LitteraleSimple() {};

private:

};

class LitteraleComplexe : public LitteraleSimple
{
public:
	LitteraleComplexe() {}
	virtual ~LitteraleComplexe() {};

private:

};

class LitteraleNumerique : public LitteraleComplexe
{
public:
	LitteraleNumerique() {}
	virtual ~LitteraleNumerique() {};
    virtual LitteraleNumerique* getNumericCopy() const =0;

private:

};

/*
    Fonction Template pour connaitre les types des objets :
    L'objet de type T est-il de type L ?
*/
template<typename T,typename L> bool estdeType(T* Tobj){
    L* Lobj;
    if(Lobj=dynamic_cast<L*>(Tobj))
        return true;
    return false;

}




/*------------Classe Litterale Entier------------*/

class Entier : public LitteraleNumerique {

    int valeur;
public:
    Entier(int v=0) :valeur(v) {}
    ~Entier() {};
    int getValeur() const { return valeur; }
    const std::string toString() const { return std::to_string(getValeur());}
    Litterale* getCopy() const {return getNumericCopy();}
    LitteraleNumerique* getNumericCopy() const{return new Entier(*this);}




    /*Les opérateurs sont dorénavant des objets*/
    /*
    Entier operator+(Entier e) { return Entier(e.getValeur() + getValeur()); }
    Entier operator+(int e) { return Entier(e+ getValeur()); }
    Entier operator*(Entier e) { return Entier(e.getValeur() * getValeur()); }
    Entier operator*(int e) { return Entier(e * getValeur()); }
    */
};




/*------------Classe Litterale Rationnel------------*/

class Rationnel : public LitteraleNumerique
{
    Entier numerateur;
    Entier denominateur;
public:
    Rationnel(int n, int d=1);
    Rationnel(const Entier& n, const Entier& d) { Rationnel(n.getValeur(), d.getValeur()); }
    ~Rationnel(){ }
    Entier getNumerateur() const { return numerateur; }
    Entier getDenominator() const { return denominateur; }
    LitteraleNumerique* getNumericCopy() const{return new Rationnel(*this);}
    Litterale* getCopy() const {return getNumericCopy();}
    const std::string toString() const;
    LitteraleNumerique& Simplification();
    /*Opérateurs objets donc définis ailleurs*/
    /*
    Rationnel operator+(const Rationnel& r) {	int newDen=r.getDenominator()*getDenominator();
                                                int newNum = r.getNumerateur()*getDenominator()+getNumerateur()*r.getDenominator();
                                                return Rationnel(newDen, newNum);
                                            }
    Rationnel operator*(const Rationnel& r) {
                                                int newDen = r.getDenominator()*getDenominator();
                                                int newNum = r.getNumerateur()*getNumerateur();
                                                return Rationnel(newDen, newNum);
                                            }
    */

};




/*------------Classe Litterale Reelle------------*/

class Reelle : public LitteraleNumerique{
    Entier p_entiere;
    Entier mantisse;
public:
    /*La partie entiere dit etre le second paramêtre pour avoir une valeur par défaut*/
    Reelle(Entier m,Entier p=0):p_entiere(p){
        /*Un réel ne peut pas être construit avec une mantisse nulle*/
        if(m.getValeur()==0){LitteraleException("Construction: Mantisse nulle !");}
        else{mantisse=p;}
    }
    ~Reelle(){};
    Entier getPartieEntiere(){return p_entiere;}
    Entier getMantisse(){return mantisse;}
    LitteraleNumerique& Simplification();
    LitteraleNumerique* getNumericCopy() const{return new Reelle(*this);}
    Litterale* getCopy() const{return getNumericCopy();}
    const std::string toString() const;


};




/*------------Classe Litterale Complexe------------*/

class Complexe : public LitteraleComplexe{
    LitteraleNumerique& p_reelle;
    LitteraleNumerique& p_imaginaire;
public:
    /*Le comportement par défaut du constructeur est suffisant car pas de pointeur*/
    Complexe(LitteraleNumerique& pR,LitteraleNumerique& pI):p_reelle(*pR.getNumericCopy()),p_imaginaire(*pI.getNumericCopy()){}
    const LitteraleNumerique& getPartieReelle() const {return p_reelle;}
    const LitteraleNumerique& getPartieImaginaire() const {return p_imaginaire;}
    Litterale* getCopy() const {return new Complexe(p_reelle,p_imaginaire);}
    const std::string toString() const;


};



/*------------Classe Litterale Atome------------*/
class Atome : public LitteraleSimple{
    std::string nom;
public:
    Atome(std::string n){
        std::string::iterator it=n.begin();
        if(isValidAtomeName(n))
            nom=n;
        else
            throw LitteraleException("Nom d'atome invalide");
    }
    std::string getNom() const {return nom;}
    const std::string toString() const {return getNom();}
    Litterale* getCopy() const;
    static bool isValidAtomeName(std::string s);
};

/*------------Classe Litterale Expression------------*/

class Expression : public Litterale{
    std::string value;
public:
    Expression(std::string v):value(v){};
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
