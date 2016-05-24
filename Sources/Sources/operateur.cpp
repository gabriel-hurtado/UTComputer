#include "operateur.h"

Litterale* OperateurAddition::traitementOperateur(){


    LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);

    LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);

    if(l1 && l2){

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

    Reelle* re1=estdeType<Reelle>(l1);
    Reelle* re2=estdeType<Reelle>(l2);
    if(re1 && re2){
        Entier e1= re1->getPartieEntiere() ;
        Entier e2=re2->getPartieEntiere();

        Entier m1= re1->getMantisse() ;
        Entier m2=re2->getMantisse();

        OperateurAddition ad = OperateurAddition(&m1,&m2);
        Entier* newMantisse=estdeType<Entier>(ad.traitement());
       // ATENTION SOUCIS DE RETENUES

       ad = OperateurAddition(&e1,&e2);
        Entier* newEntier=estdeType<Entier>(ad.traitement());
        Reelle* re= new Reelle(*newMantisse,*newEntier);

        return &(re->Simplification());

    }

    if(re1 && r2){
        Reelle temp=(r2->roundValue());
        OperateurAddition ad = OperateurAddition(re1,&temp);
        return ad.traitement();

    }
    }
    throw LitteraleException("Error in Addition");


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


Litterale* OperateurDivision::traitementOperateur(){


    Entier* e1=estdeType<Entier>(l1);
    Entier* e2=estdeType<Entier>(l2);
    if(e1 && e2){
        return (new Rationnel(e1->getValeur(),e2->getValeur()));
    }
}
