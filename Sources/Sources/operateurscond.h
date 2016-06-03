#ifndef OPERATEURSCOND_H
#define OPERATEURSCOND_H
#ifndef OPERATEURSPILE_H
#define OPERATEURSPILE_H

#include"operateur.h"
namespace conditionnel{

class OperateurConditionnel : public Operateur
{
public:

    OperateurConditionnel(){}

    void operation(){
                     try{OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
                        chargerContexte(); traitementOperateur(); }
                        catch(OperateurException op){
                       resetContexte();
                       throw OperateurException(op);
                            }
                         catch(PileException op){
                        resetContexte();
                        throw PileException(op);
                            }
                        }

    virtual void traitementOperateur() =0;
};


class OperateurBinaire : public OperateurPile{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){p>>l2;
                           p>>l1;
                          OperationManager::donnerInstance().add(l1);
                          OperationManager::donnerInstance().add(l2);}

    void resetContexte(){if(l1) p<<*l1;
                         if(l2)  p<<*l2;}

    OperateurBinaire(){}
};

class OperateurUnaire  : public OperateurPile{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;
                         OperationManager::donnerInstance().add(l1);}

   void resetContexte(){if(l1) p<<*l1;}
   OperateurUnaire(){}
};



/* T dépile 2 arguments. Le 1er (i.e. le dernier dépilé) est un test logique. Si la valeur de ce test est vrai, le 2e argument est évalué sinon il est abandonné.*/
class OperateurIFT : public OperateurBinaire{
public:
   void traitementOperateur(); //a faire après avoir géré les expressions

   OperateurIFT():OperateurBinaire(){}

   OperateurIFT* getCopy() {return new OperateurIFT(*this);}

};






#endif // OPERATEURSCOND_H
