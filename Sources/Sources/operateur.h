#include "operande.h"
#include "litterales.h"
#include"pile.h"

#ifndef OPERATEUR_H
#define OPERATEUR_H

/*
 * Operation interact with stack, operator must be created withoud parameters
 * traitementOperator works alone, do not push results to the stack
 *
 */

class Operateur : public Operande
{
    static std::string symbole;
    static int arite;
 protected:
    Pile& p = Pile::donnerInstance();
public:

    Operateur(){}
    static int getArite(){return arite;}
    static std::string getSymbole(){return symbole;}
    virtual void chargerContexte() = 0;
    void operation(){Litterale* res=traitementOperateur(); pushResultat(res);}
    virtual void pushResultat(Litterale* res) {p<<(*res);}
    virtual Litterale* traitementOperateur()=0;
};


class OperateurBinaire : public Operateur{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){p>>l2;
                           p>>l1;}
    OperateurBinaire(){chargerContexte();}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):l1(lit1),l2(lit2){}


};

class OperateurUnaire  : public Operateur{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;}

   OperateurUnaire(){chargerContexte();}
   OperateurUnaire(Litterale* lit1):l1(lit1){}

};

class OperateurNeg : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurNeg():OperateurUnaire(){}
   OperateurNeg(Litterale* lit1):OperateurUnaire(lit1){}
};

class OperateurAddition : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurAddition():OperateurBinaire(){}
   OperateurAddition(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
};

class OperateurSoustraction : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurSoustraction():OperateurBinaire(){}
   OperateurSoustraction(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
};

class OperateurDivision : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurDivision():OperateurBinaire(){}
   OperateurDivision(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
};


class OperateurMultiplication : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

};
#endif // OPERATEUR_H
