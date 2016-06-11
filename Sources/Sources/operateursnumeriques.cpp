#include "operateursnumeriques.h"
#include"pile.h"
#include "litterales.h"
#include "litteraleexception.h"

namespace numerique {

void OperateurNumerique::pushResultat(Litterale* res) {Pile::donnerInstance()<<(*res);}


Litterale* OperateurAddition::traitementOperateur(){


    LitteraleComplexe* litC1=estdeType<LitteraleComplexe>(l1);

    LitteraleComplexe* litC2=estdeType<LitteraleComplexe>(l2);

    if(litC1 && litC2) //si ce sont des littérales numériques
    {

        Rationnel* r1=estdeType<Rationnel>(l1);
        Rationnel* r2=estdeType<Rationnel>(l2);

        if(r1 && r2 ) //si les deux sont rationelles
        {
            //getDenominator & getNumerator dont send newly allocated, safe to be auto deleted
            int newDen=r1->getDenominator().getValeur()*r2->getDenominator().getValeur();
            int newNum = r1->getNumerateur().getValeur()*r2->getDenominator().getValeur()+r2->getNumerateur().getValeur()*r1->getDenominator().getValeur();

            // simplification return a dynamiccaly allocated value
            return &(Rationnel(newNum, newDen).Simplification());
        }

        Entier* e1=estdeType<Entier>(l1);
        Entier* e2=estdeType<Entier>(l2);
        if(e1 && e2) //si deux entiers
        {
            return (new Entier(e1->getValeur()+e2->getValeur()));
        }

        if(r1 && e2) //si il y a un rationel et un entier
        {
           Rationnel temp(e2->getValeur());
           OperateurAddition ad(r1,&temp);
           return ad.traitementOperateur();
        }
        if(r2 && e1){ //idem
           OperateurAddition ad = OperateurAddition(r2,e1);
           return ad.traitementOperateur();
        }

        Reelle* re1=estdeType<Reelle>(l1);
        Reelle* re2=estdeType<Reelle>(l2);
        if(re1 && re2){ //si deux relles
           return &(Reelle(re1->getValeur()+re2->getValeur()).Simplification());


        }
        if(re1 && e2){ //si relle et entier
           return &(Reelle(re1->getValeur()+e2->getValeur()).Simplification());

        }
        if(re2 && e1){
            OperateurAddition ad(re2,e1);
            return ad.traitementOperateur();
        }

        if(re1 && r2) //si relle et rationelle
        {
            Reelle temp=(r2->roundValue());
            OperateurAddition ad(re1,&temp);
            return ad.traitementOperateur();

        }
        if(re2 && r1) //idem
        {
            OperateurAddition ad(re2,r1);
            return ad.traitementOperateur();

        }

        //Belong to the object ! Not to be deallocated
        Complexe* c1=estdeType<Complexe>(l1);
        Complexe* c2=estdeType<Complexe>(l2);

        if(c1 && c2){ //si deux complexe
            LitteraleNumerique* pr1=c1->getPartieReelle();
            LitteraleNumerique* pr2=c2->getPartieReelle();
            OperateurAddition ad(pr1,pr2);
            LitteraleNumerique* reel=estdeType<LitteraleNumerique>(ad.traitementOperateur());

            LitteraleNumerique* pi1=c1->getPartieImaginaire();
            LitteraleNumerique* pi2=c2->getPartieImaginaire();
            OperateurAddition ad2(pi1,pi2);

            LitteraleNumerique* im=estdeType<LitteraleNumerique>(ad2.traitementOperateur());

            Complexe tmp(*reel,*im);

            //deallocations
            delete pr1;
            delete pr2;
            delete pi1;
            delete pi2;
            delete reel;
            delete im;

            return &tmp.Simplification();
        }

        LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);
        LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);
        if(c1 && litNum2){ //si un complexe et une litNumérique

            LitteraleNumerique* pr1=c1->getPartieReelle();
            OperateurAddition   ad(pr1,litNum2);
            LitteraleNumerique* reel=estdeType<LitteraleNumerique>(ad.traitementOperateur());
            LitteraleNumerique* im=c1->getPartieImaginaire();

            Complexe tmp(*reel,*im);

            //deallocations
            delete pr1;
            delete reel;
            delete im;

            return &tmp.Simplification();

        }

        if(c2 && litNum1){
            OperateurAddition ad(c2,litNum1);
            return ad.traitementOperateur();
        }

    }
    throw OperateurException("Error in Addition");


}

Litterale* OperateurNEG::traitementOperateur(){
    LitteraleComplexe* lit=estdeType<LitteraleComplexe>(l1);
    if(lit)
        return lit->neg();
    else throw OperateurException("Error in NEG");
}

Litterale* OperateurSoustraction::traitementOperateur(){
    LitteraleComplexe* li1=estdeType<LitteraleComplexe>(l1);
    LitteraleComplexe* li2=estdeType<LitteraleComplexe>(l2);
    if(li1 && li2)
    {
        OperateurNEG ng(li2);
        OperateurAddition addTemp(li1,ng.traitementOperateur());
        return addTemp.traitementOperateur();
    }
    throw OperateurException("Error in soustraction");
}

Litterale* OperateurMultiplication::traitementOperateur(){


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
            return &(Rationnel(newNum,newDen).Simplification());

             }

        Entier* e1=estdeType<Entier>(l1);
        Entier* e2=estdeType<Entier>(l2);
        if(e1 && e2) //si deux entiers
        {
            return (new Entier(e1->getValeur()*e2->getValeur()));

          }

        if(r1 && e2) //si il y a un rationel et un entier
        {
            Rationnel temp(e2->getValeur(),1);
            OperateurMultiplication mul = OperateurMultiplication(r1,&temp);
            return mul.traitementOperateur();

        }
        if(r2 && e1){ //idem
            OperateurMultiplication mul = OperateurMultiplication(r2,e1);
            return mul.traitementOperateur();
        }

        Reelle* re1=estdeType<Reelle>(l1);
        Reelle* re2=estdeType<Reelle>(l2);
        if(re1 && re2){ //si deux relles
            return &(Reelle(re1->getValeur()*re2->getValeur()).Simplification());

        }
        if(re1 && e2){ //si relle et entier
            return &(Reelle(re1->getValeur()*e2->getValeur()).Simplification());

        }
        if(re2 && e1){

            OperateurMultiplication mul = OperateurMultiplication(re2,e1);
            return mul.traitementOperateur();
        }

        if(re1 && r2) //si relle et rationelle
        {
            Reelle temp=(r2->roundValue());
            OperateurMultiplication mul = OperateurMultiplication(re1,&temp);
            return mul.traitementOperateur();

        }
        if(re2 && r1) //idem
        {
            OperateurMultiplication mul = OperateurMultiplication(re2,r1);
            return mul.traitementOperateur();

        }


        Complexe* c1=estdeType<Complexe>(l1);
        Complexe* c2=estdeType<Complexe>(l2);

        if(c1 && c2){ //si deux complexe

            //Needed to be deallocated after
            LitteraleNumerique* cpr1 = c1->getPartieReelle();
            LitteraleNumerique* cpr2 = c2->getPartieReelle();
            LitteraleNumerique* cpi1 = c1->getPartieImaginaire();
            LitteraleNumerique* cpi2 = c2->getPartieImaginaire();

            OperateurMultiplication mul1(cpr1,cpr2);
            OperateurMultiplication mul2(cpi1,cpi2);

            //Needed to be deallocated after also
            Litterale* resmult1 = mul1.traitementOperateur();
            Litterale* resmult2 = mul2.traitementOperateur();

            OperateurSoustraction sub = OperateurSoustraction(resmult1,resmult2);

            //Needed to be deallocated after also
            Litterale* ressub = sub.traitementOperateur();
            LitteraleNumerique* real = estdeType<LitteraleNumerique>(ressub);

            OperateurMultiplication mul3(cpi1,cpr2);
            OperateurMultiplication mul4(cpr1,cpi2);

            //Needed to be deallocated after also
            Litterale* resmult3 = mul3.traitementOperateur();
            Litterale* resmult4 = mul4.traitementOperateur();

            OperateurAddition  add(resmult3,resmult4);

            //Needed to be deallocated after also
            LitteraleNumerique* img = estdeType<LitteraleNumerique>(add.traitementOperateur());

            Complexe tmp(*real,*img);

            //deallocation
            delete cpr1;
            delete cpr2;
            delete cpi1;
            delete cpi2;
            delete resmult1;
            delete resmult2;
            delete resmult3;
            delete resmult4;
            delete ressub;
            delete real;
            delete img;

            return &tmp.Simplification();

        }
        LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);
        LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);

        if(c1 && litNum2){ //si un complexe et une litNumérique
             Entier zero(0);
             Complexe temp(*litNum2,zero);

            return (OperateurMultiplication(c1,&temp).traitementOperateur());

        }

        if(c2 && litNum1){
            return (OperateurMultiplication(c2,litNum1).traitementOperateur());
         }

    }
    throw OperateurException("Error in Multiplication");


}


Litterale* OperateurDivision::traitementOperateur(){

    LitteraleComplexe* litC1=estdeType<LitteraleComplexe>(l1);
    LitteraleComplexe* litC2=estdeType<LitteraleComplexe>(l2);

    if(litC1 && litC2) //si ce sont des littérales numériques
    {

        Rationnel* r1=estdeType<Rationnel>(l1);
        Rationnel* r2=estdeType<Rationnel>(l2);

        if(r1 && r2 ) //si les deux sont rationelles
        {
            Entier newNum(r1->getNumerateur().getValeur()*r2->getDenominator().getValeur());
            Entier newDenum(r2->getNumerateur().getValeur()*r1->getDenominator().getValeur());
            Rationnel res(newNum.getValeur(),newDenum.getValeur());

            return &(res.Simplification());
        }

        Entier* e1=estdeType<Entier>(l1);
        Entier* e2=estdeType<Entier>(l2);
        if(e1 && e2) //si deux entiers
        {
            return &(Rationnel(e1->getValeur(),e2->getValeur()).Simplification());
        }
        if(r1 && e2) //si il y a un rationel et un entier
        {
            Rationnel temp(e2->getValeur());
            return OperateurDivision(r1,&temp).traitementOperateur();


        }
        if(r2 && e1){ //idem
            Rationnel temp(e1->getValeur());
             return OperateurDivision(&temp,r2).traitementOperateur();
        }

        Reelle* re1=estdeType<Reelle>(l1);
        Reelle* re2=estdeType<Reelle>(l2);
        if(re1 && re2){ //si deux relles
            return &(Reelle((double)(re1->getValeur()/re2->getValeur())).Simplification());
        }
        if(re1 && e2){ //si relle et entier
           Reelle temp((double)e2->getValeur());
           return OperateurDivision(re1,&temp).traitementOperateur();
        }
        if(re2 && e1){

           Reelle temp((double)e1->getValeur());
           return OperateurDivision(&temp,re2).traitementOperateur();
        }

        if(re1 && r2) //si relle et rationelle
        {
            Reelle temp(r2->roundValue());
            return OperateurDivision(re1,&temp).traitementOperateur();

       }
        if(re2 && r1) //idem
        {
            Reelle temp(r1->roundValue());
            return OperateurDivision(&temp,re2).traitementOperateur();
        }


        Complexe* c1=estdeType<Complexe>(l1);
        Complexe* c2=estdeType<Complexe>(l2);

        if(c1 && c2){ //si deux complexe

               //Needed to be deallocated after
               LitteraleNumerique* c1Im= c1->getPartieImaginaire();
               LitteraleNumerique* c1Re= c1->getPartieReelle();

               //Needed to be deallocated after also
               LitteraleNumerique* c2Im= c2->getPartieImaginaire();
               LitteraleNumerique* c2Re= c2->getPartieReelle();


               OperateurMultiplication mulDenom1(c2Im,c2Im);
               OperateurMultiplication mulDenom2(c2Re,c2Re);

               //Needed to be deallocated after also
               Litterale* resmultDenom1 = mulDenom1.traitementOperateur();
               Litterale* resmultDenom2 = mulDenom2.traitementOperateur();
               LitteraleNumerique* newDenom = estdeType<LitteraleNumerique>(OperateurAddition(resmultDenom1,resmultDenom2).traitementOperateur());

               OperateurMultiplication mulNum1 = OperateurMultiplication(c2Re,c1Re);
               OperateurMultiplication mulNum2 = OperateurMultiplication(c2Im,c1Im);

               //Needed to be deallocated after also
               Litterale* resmultNum1 = mulNum1.traitementOperateur();
               Litterale* resmultNum2 = mulNum2.traitementOperateur();
               LitteraleNumerique* newNumRe= estdeType<LitteraleNumerique>( OperateurAddition(resmultNum1,resmultNum2).traitementOperateur());

               OperateurMultiplication mulNum3 = OperateurMultiplication(c2Re,c1Im);
               OperateurMultiplication mulNum4 = OperateurMultiplication(c2Im,c1Re);

               //Needed to be deallocated after also
               Litterale* resmultNum3 = mulNum3.traitementOperateur();
               Litterale* resmultNum4 = mulNum4.traitementOperateur();
               LitteraleNumerique* newNumIm=  estdeType<LitteraleNumerique>(OperateurSoustraction(resmultNum3,resmultNum4).traitementOperateur());

               LitteraleNumerique* re= estdeType<LitteraleNumerique>(OperateurDivision(newNumRe,newDenom).traitementOperateur());
               LitteraleNumerique* im= estdeType<LitteraleNumerique>(OperateurDivision(newNumIm,newDenom).traitementOperateur());

               Complexe tmp(*re,*im);

               //deallocations
               delete c1Im;
               delete c2Im;
               delete c1Re;
               delete c2Re;
               delete resmultDenom1;
               delete resmultDenom2;
               delete resmultNum1;
               delete resmultNum2;
               delete resmultNum3;
               delete resmultNum4;
               delete newNumRe;
               delete newNumIm;
               delete re;
               delete im;

               return &(tmp.Simplification());
        }
        LitteraleNumerique* litNum1=estdeType<LitteraleNumerique>(l1);
        LitteraleNumerique* litNum2=estdeType<LitteraleNumerique>(l2);

        if(c1 && litNum2){ //si un complexe et une litNumérique

            Entier zero(0);
            Complexe temp(*litNum2,zero);

            return OperateurDivision(c1,&temp).traitementOperateur();
        }

        if(c2 && litNum1){
            return OperateurDivision(c2,litNum1).traitementOperateur();
        }

    }
    throw OperateurException("Error in Division");





}

Litterale* OperateurDIV::traitementOperateur(){
    Entier* e1=estdeType<Entier>(l1);
    Entier* e2=estdeType<Entier>(l2);
    if(e1 && e2)
    {
        return (new Entier(e1->getValeur()/e2->getValeur()));
    }
    throw OperateurException("Error in DIV");
}

Litterale* OperateurMOD::traitementOperateur(){
    Entier* e1=estdeType<Entier>(l1);
    Entier* e2=estdeType<Entier>(l2);
    if(e1 && e2)
    {
        return (new Entier((int)e1->getValeur()%(int)e2->getValeur()));
    }
    throw OperateurException("Error in MOD");
}

Litterale* OperateurNUM::traitementOperateur(){
    Entier* e=estdeType<Entier>(l1);
    if(e)
        return e->getNumericCopy();
    Rationnel* re=estdeType<Rationnel>(l1);
    if(re)
        return new Entier(re->getNumerateur());

    else throw OperateurException("Error in NUM");
}

Litterale* OperateurDEN::traitementOperateur(){
    Entier* e=estdeType<Entier>(l1);
    if(e)
        return (new Entier(1));
    Rationnel* re=estdeType<Rationnel>(l1);
    if(re)
        return new Entier(re->getDenominator());

    else throw OperateurException("Error in DEN");
}

Litterale* OperateurIM::traitementOperateur(){
    LitteraleComplexe* lit=estdeType<LitteraleComplexe>(l1);
    if(lit){
       Complexe* cmp=estdeType<Complexe>(l1);
       if(cmp)
           return  cmp->getPartieImaginaire();

       else
           return new Entier(0);
    }

    else throw OperateurException("Error in IM");
}

Litterale* OperateurRE::traitementOperateur(){
    LitteraleComplexe* lit=estdeType<LitteraleComplexe>(l1);
    if(lit){
       Complexe* cmp=estdeType<Complexe>(l1);
       if(cmp)
           return cmp->getPartieReelle();

       else{
            LitteraleNumerique* num=estdeType<LitteraleNumerique>(l1);
            return num->getNumericCopy();
       }
    }

    else throw OperateurException("Error in RE");
}

Litterale* Operateur$::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        return &(Complexe(*li1,*li2).Simplification());
    }
    throw OperateurException("Error in $");
}
}
