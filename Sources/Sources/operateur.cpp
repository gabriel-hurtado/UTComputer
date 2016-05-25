#include "operateur.h"

Litterale* OperateurAddition::traitementOperateur(){


    LitteraleComplexe* litC1=estdeType<LitteraleComplexe>(l1);

    LitteraleComplexe* litC2=estdeType<LitteraleComplexe>(l2);

    if(litC1 && litC2) //si ce sont des littérales numériques
    {

        Rationnel* r1=estdeType<Rationnel>(l1);
        Rationnel* r2=estdeType<Rationnel>(l2);

        if(r1 && r2 ) //si les deux sont rationelles
        {
            int newDen=r1->getDenominator().getValeur()*r2->getDenominator().getValeur();
            int newNum = r1->getNumerateur().getValeur()*r2->getDenominator().getValeur()+r2->getNumerateur().getValeur()*r1->getDenominator().getValeur();
            return &((new Rationnel(newNum, newDen))->Simplification());
        }

        Entier* e1=estdeType<Entier>(l1);
        Entier* e2=estdeType<Entier>(l2);
        if(e1 && e2) //si deux entiers
        {
            return ( new Entier(e1->getValeur()+e2->getValeur()));
        }

        if(r1 && e2) //si il y a un rationel et un entier
        {
           Rationnel temp= Rationnel(e2->getValeur());
           OperateurAddition ad = OperateurAddition(r1,&temp);
           return ad.operation();

        }
        if(r2 && e1){ //idem
           OperateurAddition ad = OperateurAddition(r2,e1);
           return ad.operation();

        }

        Reelle* re1=estdeType<Reelle>(l1);
        Reelle* re2=estdeType<Reelle>(l2);
        if(re1 && re2){ //si deux relles
           return(&(new Reelle(re1->getValeur()+re2->getValeur()))->Simplification());


        }
        if(re1 && e2){ //si relle et entier
           return(&(new Reelle(re1->getValeur()+e2->getValeur()))->Simplification());

        }
        if(re2 && e1){
            OperateurAddition ad= OperateurAddition(re2,e1);
            return ad.operation();
        }

        if(re1 && r2) //si relle et rationelle
        {
            Reelle temp=(r2->roundValue());
            OperateurAddition ad = OperateurAddition(re1,&temp);
            return ad.operation();

        }
        if(re2 && r1) //idem
        {
            OperateurAddition ad = OperateurAddition(re2,r1);
            return ad.operation();

        }


        Complexe* c1=estdeType<Complexe>(l1);
        Complexe* c2=estdeType<Complexe>(l2);

        if(c1 && c2){ //si deux complexe
            LitteraleNumerique* pr1=c1->getPartieReelle();
            LitteraleNumerique* pr2=c2->getPartieReelle();
            OperateurAddition ad = OperateurAddition(pr1,pr2);
            LitteraleNumerique* reel=estdeType<LitteraleNumerique>(ad.traitement());


            LitteraleNumerique* pi1=c1->getPartieImaginaire();
            LitteraleNumerique* pi2=c2->getPartieImaginaire();
            OperateurAddition ad2 = OperateurAddition(pi1,pi2);

            LitteraleNumerique* im=estdeType<LitteraleNumerique>(ad.traitement());
                   return new Complexe(*reel,*im);
        }
        LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);

        LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);
        if(c1 && litNum2){ //si un complexe et une litNumérique

            LitteraleNumerique* pr1=c1->getPartieReelle();

            OperateurAddition ad = OperateurAddition(pr1,litNum2);
            LitteraleNumerique* reel=estdeType<LitteraleNumerique>(ad.traitement());


            LitteraleNumerique* im=c1->getPartieImaginaire();
             return new Complexe(*reel,*im);

        }

        if(c2 && litNum1){
            OperateurAddition ad = OperateurAddition(c2,litNum1);
            return ad.traitement();
        }

    }
    throw LitteraleException("Error in Addition");


}

Litterale* OperateurNeg::traitementOperateur(){
    LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);
    if(litNum1)
    return litNum1->neg();
}

Litterale* OperateurSoustraction::traitementOperateur(){
    LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);

    LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);
    if(litNum1 && litNum2)
    {
        OperateurNeg ng = OperateurNeg(litNum1);
        OperateurAddition add = OperateurAddition(ng.traitement(),litNum2);
        return add.operation();
    }
}

Litterale* OperateurMultiplication::traitementOperateur(){

    Rationnel* r1=estdeType<Rationnel>(l1);
    Rationnel* r2=estdeType<Rationnel>(l2);

    if(r1 && r2)// si deux rationelles
    {
        int newDen=r1->getDenominator().getValeur()*r2->getDenominator().getValeur();
        int newNum = r1->getNumerateur().getValeur()*r2->getNumerateur().getValeur();
        return ( new Rationnel(newDen, newNum));
    }

    Entier* e1=estdeType<Entier>(l1);
    Entier* e2=estdeType<Entier>(l2);
    if(e1 && e2) //si deux entiers
    {
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
