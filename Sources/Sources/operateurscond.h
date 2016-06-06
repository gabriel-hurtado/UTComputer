#ifndef OPERATEURSCOND_H
#define OPERATEURSCOND_H

#include"operateur.h"
namespace conditionnel{

class OperateurConditionnel : public virtual Operateur
{
public:

    OperateurConditionnel(){}

    void operation(){
                     try{OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
                        actualiserContexte(); traitementOperateur(); }
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




/* T dépile 2 arguments. Le 1er (i.e. le dernier dépilé) est un test logique. Si la valeur de ce test est vrai, le 2e argument est évalué sinon il est abandonné.*/
class OperateurIFT : public OperateurBinaire, public OperateurConditionnel, public OperateurPrefixe{



public:
   void traitementOperateur(); //a faire après avoir géré les expressions

   void initSymbole() override{symbole="IFT";}

   OperateurIFT():OperateurBinaire(){}


   OperateurIFT* getCopy() {return new OperateurIFT(*this);}

};






#endif // OPERATEURSCOND_H
