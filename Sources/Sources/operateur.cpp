#include "operateur.h"

Litterale* OperateurAddition::traitement(){


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
           return ad.traitement();

        }
        if(r2 && e1){ //idem
           OperateurAddition ad = OperateurAddition(r2,e1);
           return ad.traitement();

        }

        Reelle* re1=estdeType<Reelle>(l1);
        Reelle* re2=estdeType<Reelle>(l2);
        if(re1 && re2){ //si deux relles
           return(&(new Reelle(re1->getValeur()+re2->getValeur()))->Simplification());


        }
        if(re1 && e2){ //si relle et entier
           Reelle* tmp =new Reelle(re1->getValeur()+e2->getValeur());
                 return &(tmp->Simplification());

        }
        if(re2 && e1){
            OperateurAddition ad= OperateurAddition(re2,e1);
            return ad.traitement();
        }

        if(re1 && r2) //si relle et rationelle
        {
            Reelle temp=(r2->roundValue());
            OperateurAddition ad = OperateurAddition(re1,&temp);
            return ad.traitement();

        }
        if(re2 && r1) //idem
        {
            OperateurAddition ad = OperateurAddition(re2,r1);
            return ad.traitement();

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

            LitteraleNumerique* im=estdeType<LitteraleNumerique>(ad2.traitement());
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

Litterale* OperateurNeg::traitement(){
    LitteraleComplexe* lit=estdeType<LitteraleComplexe>(l1);
    if(lit)
    return lit->neg();
}

Litterale* OperateurSoustraction::traitement(){
    LitteraleComplexe* li1=estdeType<LitteraleComplexe>(l1);
    LitteraleComplexe* li2=estdeType<LitteraleComplexe>(l2);
    if(li1 && li2)
    {
        OperateurNeg ng = OperateurNeg(li2);
        OperateurAddition addTemp = OperateurAddition(li1,ng.traitement());
        return addTemp.traitement();
    }
}

Litterale* OperateurMultiplication::traitement(){


    LitteraleComplexe* litC1=estdeType<LitteraleComplexe>(l1);

    LitteraleComplexe* litC2=estdeType<LitteraleComplexe>(l2);

    if(litC1 && litC2) //si ce sont des littérales numériques
    {

        Rationnel* r1=estdeType<Rationnel>(l1);
        Rationnel* r2=estdeType<Rationnel>(l2);

        if(r1 && r2 ) //si les deux sont rationelles
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

        if(r1 && e2) //si il y a un rationel et un entier
        {
            Rationnel temp= Rationnel(e2->getValeur());
            OperateurMultiplication mul = OperateurMultiplication(r1,&temp);
            return mul.traitement();

        }
        if(r2 && e1){ //idem
            OperateurMultiplication mul = OperateurMultiplication(r2,e1);
            return mul.traitement();
        }

        Reelle* re1=estdeType<Reelle>(l1);
        Reelle* re2=estdeType<Reelle>(l2);
        if(re1 && re2){ //si deux relles
            return(&(new Reelle(re1->getValeur()*re2->getValeur()))->Simplification());

        }
        if(re1 && e2){ //si relle et entier
            return(&(new Reelle(re1->getValeur()*e2->getValeur()))->Simplification());

        }
        if(re2 && e1){

            OperateurMultiplication mul = OperateurMultiplication(re2,e1);
            return mul.traitement();
        }

        if(re1 && r2) //si relle et rationelle
        {
            Reelle temp=(r2->roundValue());
            OperateurMultiplication mul = OperateurMultiplication(re1,&temp);
            return mul.traitement();

        }
        if(re2 && r1) //idem
        {
            OperateurMultiplication mul = OperateurMultiplication(re2,r1);
            return mul.traitement();

        }


        Complexe* c1=estdeType<Complexe>(l1);
        Complexe* c2=estdeType<Complexe>(l2);

        if(c1 && c2){ //si deux complexe
            OperateurMultiplication mul1 = OperateurMultiplication(c1->getPartieReelle(),c2->getPartieReelle());
            OperateurMultiplication mul2 = OperateurMultiplication(c1->getPartieImaginaire(),c2->getPartieImaginaire());
            OperateurSoustraction sub = OperateurSoustraction(mul1.traitement(),mul2.traitement());
            LitteraleNumerique* real = estdeType<LitteraleNumerique>(sub.traitement());

            OperateurMultiplication mul3 = OperateurMultiplication(c1->getPartieImaginaire(),c2->getPartieReelle());
            OperateurMultiplication mul4 = OperateurMultiplication(c1->getPartieReelle(),c2->getPartieImaginaire());
            OperateurAddition  add = OperateurAddition(mul3.traitement(),mul4.traitement());
            LitteraleNumerique* img = estdeType<LitteraleNumerique>(add.traitement());
            return (new Complexe(*real,*img));
        }
        LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);

        LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);
        if(c1 && litNum2){ //si un complexe et une litNumérique
            LitteraleNumerique* zero=new Entier(0);
            Complexe* temp= new Complexe(*litNum2,*zero);
            return (OperateurMultiplication(c1,temp).traitement());

        }

        if(c2 && litNum1){
            return (OperateurMultiplication(c2,litNum1).traitement());
         }

    }
    throw LitteraleException("Error in Addition");


}


Litterale* OperateurDivision::traitement(){

    LitteraleComplexe* litC1=estdeType<LitteraleComplexe>(l1);

    LitteraleComplexe* litC2=estdeType<LitteraleComplexe>(l2);

    if(litC1 && litC2) //si ce sont des littérales numériques
    {

        Rationnel* r1=estdeType<Rationnel>(l1);
        Rationnel* r2=estdeType<Rationnel>(l2);

        if(r1 && r2 ) //si les deux sont rationelles
        {
            Entier newNum = Entier(r1->getNumerateur().getValeur()*r2->getDenominator().getValeur());
            Entier newDenum = Entier(r2->getNumerateur().getValeur()*r1->getDenominator().getValeur());
           return(&(new Rationnel(newNum,newDenum))->Simplification());

             }

        Entier* e1=estdeType<Entier>(l1);
        Entier* e2=estdeType<Entier>(l2);
        if(e1 && e2) //si deux entiers
        {
            return (new Rationnel(e1->getValeur(),e2->getValeur()));
          }

        if(r1 && e2) //si il y a un rationel et un entier
        {
            Rationnel* temp = new Rationnel(e2->getValeur());
            OperateurDivision(r1,temp).traitement();


        }
        if(r2 && e1){ //idem

            Rationnel* temp = new Rationnel(e1->getValeur());
            OperateurDivision(temp,r2).traitement();
        }

        Reelle* re1=estdeType<Reelle>(l1);
        Reelle* re2=estdeType<Reelle>(l2);
        if(re1 && re2){ //si deux relles
            return new Reelle((double)(re1->getValeur()/re2->getValeur()));
        }
        if(re1 && e2){ //si relle et entier
           Reelle* temp= new Reelle((double)e2->getValeur());
           return OperateurDivision(re1,temp).traitement();
        }
        if(re2 && e1){

            Reelle* temp= new Reelle((double)e1->getValeur());
           return OperateurDivision(temp,re2).traitement();
        }

        if(re1 && r2) //si relle et rationelle
        {
            return (OperateurDivision(re1,new Reelle(r2->roundValue())).traitement());

       }
        if(re2 && r1) //idem
        {
            return (OperateurDivision(new Reelle(r1->roundValue()),re2).traitement());
        }


        Complexe* c1=estdeType<Complexe>(l1);
        Complexe* c2=estdeType<Complexe>(l2);

        if(c1 && c2){ //si deux complexe
               LitteraleNumerique* c1Im= c1->getPartieImaginaire();
               LitteraleNumerique* c1Re= c1->getPartieReelle();

               LitteraleNumerique* c2Im= c2->getPartieImaginaire();
               LitteraleNumerique* c2Re= c2->getPartieReelle();


               OperateurMultiplication mulDenom1= OperateurMultiplication(c2Im,c2Im);
               OperateurMultiplication mulDenom2= OperateurMultiplication(c2Re,c2Re);
               LitteraleNumerique* newDenom = estdeType<LitteraleNumerique>(OperateurAddition(mulDenom1.traitement(),mulDenom2.traitement()).traitement());


               OperateurMultiplication mulNum1 = OperateurMultiplication(c2Re,c1Re);
               OperateurMultiplication mulNum2 = OperateurMultiplication(c2Im,c1Im);

               LitteraleNumerique* newNumRe= estdeType<LitteraleNumerique>( OperateurAddition(mulNum1.traitement(),mulNum2.traitement()).traitement());

               OperateurMultiplication mulNum3 = OperateurMultiplication(c2Re,c1Im);
               OperateurMultiplication mulNum4 = OperateurMultiplication(c2Im,c1Re);

               LitteraleNumerique* newNumIm=  estdeType<LitteraleNumerique>(OperateurSoustraction(mulNum3.traitement(),mulNum4.traitement()).traitement());

               LitteraleNumerique* re=  estdeType<LitteraleNumerique>(OperateurDivision(newNumRe,newDenom).traitement());
               LitteraleNumerique* im= estdeType<LitteraleNumerique>(OperateurDivision(newNumIm,newDenom).traitement());

               return new Complexe(*re,*im);
        }
        LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);

        LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);

        if(c1 && litNum2){ //si un complexe et une litNumérique

            LitteraleNumerique* zero=new Entier(0);
            Complexe* temp= new Complexe(*litNum2,*zero);
            return OperateurDivision(c1,temp).traitement();
       }

        if(c2 && litNum1){
            return OperateurDivision(c2,litNum1).traitement();
            }

    }
    throw LitteraleException("Error in Addition");





}
