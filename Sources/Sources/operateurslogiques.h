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

class OperateurLogique : public virtual Operateur
{
public:
    virtual void pushResultat(Litterale* res) {Pile::donnerInstance()<<(*res);}
    void operation(){
                     try{OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
                        chargerContexte(); Litterale* res=traitementOperateur(); pushResultat(res);
                            }
                        catch(OperateurException op){
                       resetContexte();
                       throw OperateurException(op);
                            }
                         catch(PileException op){
                        resetContexte();
                        throw PileException(op);
                            }
                        }
    OperateurLogique(){}

    virtual Litterale* traitementOperateur() =0;

};




class OperateurEgal : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){ symbole="=";}

   OperateurEgal():OperateurBinaire(){}
   OperateurEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurEgal* getCopy() {return new OperateurEgal(*this);}

};

class OperateurDiff : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();


   void initSymbole(){ symbole="!=";}
   OperateurDiff():OperateurBinaire(){}
   OperateurDiff(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurDiff* getCopy() {return new OperateurDiff(*this);}

};

class OperateurInfEgal : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="<=";}
   OperateurInfEgal():OperateurBinaire(){}
   OperateurInfEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurInfEgal* getCopy() {return new OperateurInfEgal(*this);}

};


class OperateurSupEgal : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){ symbole=">=";}
   OperateurSupEgal():OperateurBinaire(){}
   OperateurSupEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSupEgal* getCopy() {return new OperateurSupEgal(*this);}

};

class OperateurSup : public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole=">";}
   OperateurSup():OperateurBinaire(){}
   OperateurSup(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSup* getCopy() {return new OperateurSup(*this);}

};


class OperateurInf: public OperateurBinaire, public OperateurLogique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="<";}
   OperateurInf():OperateurBinaire(){}
   OperateurInf(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurInf* getCopy() {return new OperateurInf(*this);}

};


class OperateurAND: public OperateurBinaire, public OperateurLogique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){   symbole="AND";}
   OperateurAND():OperateurBinaire(){}
   OperateurAND(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurAND* getCopy() {return new OperateurAND(*this);}

};

class OperateurOR: public OperateurBinaire, public OperateurLogique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){ symbole="OR";}
   OperateurOR():OperateurBinaire(){}
   OperateurOR(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurOR* getCopy() {return new OperateurOR(*this);}

};

class OperateurNOT: public OperateurBinaire, public OperateurLogique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){ symbole="NOT";}
   OperateurNOT():OperateurBinaire(){}
   OperateurNOT(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurNOT* getCopy() {return new OperateurNOT(*this);}

};
}
#endif // OPERATEURSLOGIQUES_H
