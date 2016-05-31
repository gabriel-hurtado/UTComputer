#ifndef OPERATEURSLOGIQUES_H
#define OPERATEURSLOGIQUES_H

#include "operateur.h"
#include "litterales.h"

#include"pile.h"


/*
 * Operation interact with stack, operator must be created withoud parameters
 * traitementOperator works alone, do not push results to the stack
 *
 */

namespace logique{

class OperateurLogique : public Operateur
{
public:

    OperateurLogique(){}
    bool operation(){chargerContexte(); return traitementOperateur();}
    virtual bool traitementOperateur() =0;
    virtual OperateurLogique* getCopy()=0;
};


class OperateurBinaire : public OperateurLogique{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){p>>l2;
                           p>>l1;}
    OperateurBinaire(){}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):l1(lit1),l2(lit2){}
};

class OperateurUnaire  : public OperateurLogique{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;}

   OperateurUnaire(){}
   OperateurUnaire(Litterale* lit1):l1(lit1){}
};


class OperateurEgal : public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurEgal():OperateurBinaire(){}
   OperateurEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurEgal* getCopy() {return new OperateurEgal(*this);}

};

class OperateurDiff : public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurDiff():OperateurBinaire(){}
   OperateurDiff(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurDiff* getCopy() {return new OperateurDiff(*this);}

};

class OperateurInfEgal : public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurInfEgal():OperateurBinaire(){}
   OperateurInfEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurInfEgal* getCopy() {return new OperateurInfEgal(*this);}

};


class OperateurSupEgal : public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurSupEgal():OperateurBinaire(){}
   OperateurSupEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSupEgal* getCopy() {return new OperateurSupEgal(*this);}

};

class OperateurSup : public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurSup():OperateurBinaire(){}
   OperateurSup(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSup* getCopy() {return new OperateurSup(*this);}

};


class OperateurInf: public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurInf():OperateurBinaire(){}
   OperateurInf(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurInf* getCopy() {return new OperateurInf(*this);}

};


class OperateurAND: public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurAND():OperateurBinaire(){}
   OperateurAND(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurAND* getCopy() {return new OperateurAND(*this);}

};

class OperateurOR: public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurOR():OperateurBinaire(){}
   OperateurOR(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurOR* getCopy() {return new OperateurOR(*this);}

};

class OperateurNOT: public OperateurBinaire{
public:
   bool traitementOperateur();

   OperateurNOT():OperateurBinaire(){}
   OperateurNOT(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurNOT* getCopy() {return new OperateurNOT(*this);}

};
}
#endif // OPERATEURSLOGIQUES_H
