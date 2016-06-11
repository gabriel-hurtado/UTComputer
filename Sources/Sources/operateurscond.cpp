#include "operateurscond.h"
#include "litterales.h"
#include "operateursexpressions.h"
#include "operateurspile.h"
Litterale* conditionnel::OperateurIFT::traitementOperateur(){
    Entier* e1= estdeType<Entier>(l1);

    if(e1 && e1->getValeur()==0)
    {
            return nullptr;

    }
    else{
        return expression::OperateurEVAL(l2).traitementOperateur();


    }
    return nullptr;
}
