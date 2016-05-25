#include "operande.h"
#include "litterales.h"

#ifndef OPERATEUR_H
#define OPERATEUR_H



class Operateur : public Operande
{
    static std::string symbole;
    static int arite;
public:

    Operateur(){}
    static int getArite(){return arite;}
    static std::string getSymbole(){return symbole;}
    virtual void chargerContexte() = 0;
    virtual Litterale* traitementOperateur()=0;
    virtual Litterale* operation(){Litterale* res=traitementOperateur(); pushResultat(); return res;}
    virtual void pushResultat() =0;
    Litterale* traitement(){chargerContexte();return traitementOperateur();}
};


class OperateurBinaire : public Operateur{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){}
    void pushResultat(){}
    OperateurBinaire(Litterale* lit1=nullptr, Litterale* lit2=nullptr):l1(lit1),l2(lit2){chargerContexte();}


};

class OperateurUnaire  : public Operateur{
protected:
   Litterale* l1;
public:
   void chargerContexte(){}

   void pushResultat(){}
   OperateurUnaire(Litterale* lit1=nullptr):l1(lit1){chargerContexte();}

};

class OperateurNeg : public OperateurUnaire{
public:
   Litterale* traitementOperateur();
   OperateurNeg(Litterale* lit1=nullptr):OperateurUnaire(lit1){}
};

class OperateurAddition : public OperateurBinaire{
public:
   Litterale* traitementOperateur();
   OperateurAddition(Litterale* lit1=nullptr, Litterale* lit2=nullptr):OperateurBinaire(lit1,lit2){}
};

class OperateurSoustraction : public OperateurBinaire{
public:
   Litterale* traitementOperateur();
   OperateurSoustraction(Litterale* lit1=nullptr, Litterale* lit2=nullptr):OperateurBinaire(lit1,lit2){}
};

class OperateurDivision : public OperateurBinaire{
public:
   Litterale* traitementOperateur();
   OperateurDivision(Litterale* lit1=nullptr, Litterale* lit2=nullptr):OperateurBinaire(lit1,lit2){}
};


class OperateurMultiplication : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

};
#endif // OPERATEUR_H
