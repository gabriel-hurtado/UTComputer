#include "operande.h"
#include "litterales.h"
#include"pile.h"

#ifndef OPERATEUR_H
#define OPERATEUR_H


/*
 Classe pour gérer les exceptions sur les opérateurs
 Ces messages sont utile pour notre GUI (?)
*/
class OperateurException : public std::exception
{
    std::string info;
public:
    OperateurException (std::string in) : info(in) {}
    const std::string	getMessage() { return info; }
};


/*
 * Operation interact with stack, operator must be created withoud parameters
 * traitementOperator works alone, do not push results to the stack
 *
 */

class Operateur : public Operande
{
    static std::string symbole;
 protected:
    Pile& p = Pile::donnerInstance();
public:

    Operateur(){}
    static std::string getSymbole(){return symbole;}
    virtual void chargerContexte() = 0;
    virtual void pushResultat(Litterale* res) {p<<(*res);}
    void operation(){chargerContexte(); Litterale* res=traitementOperateur(); pushResultat(res);}
    virtual bool checkContext() =0;
    Litterale* traitementOperateur() {if(checkContext()) return traitement(); else throw OperateurException("Pas le bon nombre de litérales");}
    virtual Litterale* traitement()=0;
    virtual Operateur* getCopy()=0;
};


class OperateurBinaire : public Operateur{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){p>>l2;
                           p>>l1;}
    OperateurBinaire(){}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):l1(lit1),l2(lit2){}
    bool checkContext(){return (!(l1==nullptr || l2 == nullptr));}
};

class OperateurUnaire  : public Operateur{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;}

   OperateurUnaire(){}
   OperateurUnaire(Litterale* lit1):l1(lit1){}
   bool checkContext(){return (!(l1==nullptr));}
};

class OperateurNeg : public OperateurUnaire{
public:
   Litterale* traitement();

   OperateurNeg():OperateurUnaire(){}
   OperateurNeg(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNeg* getCopy() {return new OperateurNeg(*this);}
};

class OperateurAddition : public OperateurBinaire{
public:
   Litterale* traitement();

   OperateurAddition():OperateurBinaire(){}
   OperateurAddition(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurAddition* getCopy() {return new OperateurAddition(*this);}
};

class OperateurSoustraction : public OperateurBinaire{
public:
   Litterale* traitement();

   OperateurSoustraction():OperateurBinaire(){}
   OperateurSoustraction(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSoustraction* getCopy() {return new OperateurSoustraction(*this);}
};

class OperateurDivision : public OperateurBinaire{
public:
   Litterale* traitement();

   OperateurDivision():OperateurBinaire(){}
   OperateurDivision(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   OperateurDivision* getCopy() {return new OperateurDivision(*this);}
};


class OperateurMultiplication : public OperateurBinaire{
public:
   Litterale* traitement();

   OperateurMultiplication():OperateurBinaire(){}
   OperateurMultiplication(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurMultiplication* getCopy() {return new OperateurMultiplication(*this);}

};
#endif // OPERATEUR_H
