
#ifndef OPERATEURSNUMERIQUES_H
#define OPERATEURSNUMERIQUES_H

#include "operateur.h"
#include"pile.h"
#include "litterales.h"
#include "litteraleexception.h"

/*
 * Operation interact with stack, operator must be created withoud parameters
 * traitementOperator works alone, do not push results to the stack
 *
 */

namespace numerique{

class OperateurNumerique : public Operateur
{
public:
    virtual void pushResultat(Litterale* res) {Pile::donnerInstance()<<(*res);}
    void operation(){
                     try{OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
                            chargerContexte(); Litterale* res=traitementOperateur();
                           pushResultat(res);
                            }
                        catch(OperateurException op){
                       resetContexte();
                       throw OperateurException(op);
                            }
                         catch(PileException op){
                        resetContexte();
                        throw PileException(op);
                            }

                        catch(LitteraleException& op){
                       resetContexte();
                       throw LitteraleException(op);
                           }
                        }
    OperateurNumerique(){}

    virtual Litterale* traitementOperateur() =0;

};


class OperateurBinaire : public OperateurNumerique{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){Pile::donnerInstance()>>l2;
                           Pile::donnerInstance()>>l1;
                          OperationManager::donnerInstance().add(l1);
                          OperationManager::donnerInstance().add(l2);}

    void resetContexte(){if(l1) Pile::donnerInstance()<<*l1;
                         if(l2)  Pile::donnerInstance()<<*l2;}

    OperateurBinaire(){}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):l1(lit1),l2(lit2){}
};

class OperateurUnaire  : public OperateurNumerique{
protected:
   Litterale* l1;
public:
   void chargerContexte(){Pile::donnerInstance()>>l1;
                         OperationManager::donnerInstance().add(l1);}

   void resetContexte(){if(l1) Pile::donnerInstance()<<*l1;}
   OperateurUnaire(){}
   OperateurUnaire(Litterale* lit1):l1(lit1){}
};

class OperateurNEG : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurNEG():OperateurUnaire(){}
   OperateurNEG(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNEG* getCopy() {return new OperateurNEG(*this);}
};

class OperateurAddition : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurAddition():OperateurBinaire(){}
   OperateurAddition(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurAddition* getCopy() {return new OperateurAddition(*this);}
};

class OperateurSoustraction : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurSoustraction():OperateurBinaire(){}
   OperateurSoustraction(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSoustraction* getCopy() {return new OperateurSoustraction(*this);}
};

class OperateurDivision : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurDivision():OperateurBinaire(){}
   OperateurDivision(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   OperateurDivision* getCopy() {return new OperateurDivision(*this);}
};


class OperateurMultiplication : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurMultiplication():OperateurBinaire(){}
   OperateurMultiplication(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurMultiplication* getCopy() {return new OperateurMultiplication(*this);}

};

class OperateurDIV : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurDIV():OperateurBinaire(){}
   OperateurDIV(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurDIV* getCopy() {return new OperateurDIV(*this);}

};

class OperateurMOD : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurMOD():OperateurBinaire(){}
   OperateurMOD(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurMOD* getCopy() {return new OperateurMOD(*this);}

};

class OperateurNUM : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurNUM():OperateurUnaire(){}
   OperateurNUM(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNUM* getCopy() {return new OperateurNUM(*this);}
};

class OperateurDEN : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurDEN():OperateurUnaire(){}
   OperateurDEN(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurDEN* getCopy() {return new OperateurDEN(*this);}
};

class OperateurIM : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurIM():OperateurUnaire(){}
   OperateurIM(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurIM* getCopy() {return new OperateurIM(*this);}
};

class OperateurRE : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurRE():OperateurUnaire(){}
   OperateurRE(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurRE* getCopy() {return new OperateurRE(*this);}
};

class Operateur$ : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   Operateur$():OperateurBinaire(){}
   Operateur$(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   Operateur$* getCopy() {return new Operateur$(*this);}

};
}

#endif // OPERATEURSNUMERIQUES_H
