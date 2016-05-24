#include "operateur.h"

Litterale* OperateurAddition::traitementOperateur(){

    Rationnel* r1=estdeType<Rationnel>(l1);
    Rationnel* r2=estdeType<Rationnel>(l2);

    if(r1 && r2 ){
        int newDen=r1->getDenominator().getValeur()*r2->getDenominator().getValeur();
        int newNum = r1->getNumerateur().getValeur()*r2->getDenominator().getValeur()+r2->getNumerateur().getValeur()*r1->getDenominator().getValeur();
        return (new Rationnel(newNum, newDen));
    }

    Entier* e1=estdeType<Entier>(l1);
    Entier* e2=estdeType<Entier>(l2);
    if(e1 && e2){
        return ( new Entier(e1->getValeur()+e2->getValeur()));
    }

    if(r1 && e2){
       Rationnel temp= Rationnel(e2->getValeur());
       OperateurAddition ad = OperateurAddition(r1,&temp);
       return ad.traitement();

    }
    if(r2 && e1){
       Rationnel temp= Rationnel(e1->getValeur());
       OperateurAddition ad = OperateurAddition(r2,&temp);
       return ad.traitement();

    }
}

Litterale* OperateurMultiplication::traitementOperateur(){

    Rationnel* r1=estdeType<Rationnel>(l1);
    Rationnel* r2=estdeType<Rationnel>(l2);

    if(r1 && r2){
        int newDen=r1->getDenominator().getValeur()*r2->getDenominator().getValeur();
        int newNum = r1->getNumerateur().getValeur()*r2->getNumerateur().getValeur();
        return ( new Rationnel(newDen, newNum));
    }

    Entier* e1=estdeType<Entier>(l1);
    Entier* e2=estdeType<Entier>(l2);
    if(e1 && e2){
        return (new Entier(e1->getValeur()*e2->getValeur()));
    }
}
