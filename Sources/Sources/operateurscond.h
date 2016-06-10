#ifndef OPERATEURSCOND_H
#define OPERATEURSCOND_H

#include"operateur.h"
namespace conditionnel{

class OperateurConditionnel : public virtual Operateur
{
public:

    OperateurConditionnel(){}

};




/* T dépile 2 arguments. Le 1er (i.e. le dernier dépilé) est un test logique. Si la valeur de ce test est vrai, le 2e argument est évalué sinon il est abandonné.*/
class OperateurIFT : public OperateurBinaire, public OperateurConditionnel, public OperateurPrefixe{



public:
   Litterale* traitementOperateur(); //a faire après avoir géré les expressions


   OperateurIFT():OperateurBinaire(){}



};
}





#endif // OPERATEURSCOND_H
