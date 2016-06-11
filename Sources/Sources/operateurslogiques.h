#ifndef OPERATEURSLOGIQUES_H
#define OPERATEURSLOGIQUES_H

#include "operateur.h"

//Forward declarations
class Litterale;

/*
 * Operation interact with stack, operator must be created withoud parameters
 * traitementOperator works alone, do not push results to the stack
 *
 */

namespace logique{

class OperateurLogique : public virtual Operateur
{
public:
    virtual void pushResultat(Litterale* res);

    OperateurLogique(){setPriority(1);}

    virtual Litterale* traitementOperateur() =0;
    Operateur* getCopy() const = 0;

};

class OperateurEgal : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();


   OperateurEgal():OperateurBinaire(){}
   OperateurEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurEgal(*this);}


};

class OperateurDiff : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();


OperateurDiff():OperateurBinaire(){}
   OperateurDiff(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurDiff(*this);}


};

class OperateurInfEgal : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurInfEgal():OperateurBinaire(){}
   OperateurInfEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurInfEgal(*this);}


};


class OperateurSupEgal : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurSupEgal():OperateurBinaire(){}
   OperateurSupEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurSupEgal(*this);}

};

class OperateurSup : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurSup():OperateurBinaire(){}
   OperateurSup(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurSup(*this);}

};


class OperateurInf: public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurInf():OperateurBinaire(){}
   OperateurInf(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurInf(*this);}

};


class OperateurAND: public OperateurBinaire, public OperateurLogique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurAND():OperateurBinaire(){}
   OperateurAND(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurAND(*this);}

};

class OperateurOR: public OperateurBinaire, public OperateurLogique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurOR():OperateurBinaire(){}
   OperateurOR(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurOR(*this);}

};

class OperateurNOT: public OperateurBinaire, public OperateurLogique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurNOT():OperateurBinaire(){}
   OperateurNOT(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurNOT(*this);}

};
}
#endif // OPERATEURSLOGIQUES_H
