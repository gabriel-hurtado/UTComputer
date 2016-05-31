#include "operande.h"
#include "litterales.h"
#include"pile.h"

#ifndef OPERATEUR_H
#define OPERATEUR_H


/*
 Classe pour gérer les exceptions sur les opérateurs
 Ces messages sont utile pour notre GUI (?)
*/
class OperateurException : public std::exception
{
    QString info;
public:
    OperateurException (QString in) : info(in) {}
    virtual const char* what() const throw()
      {
        return info.toStdString().c_str();
      }

};


/*
 * Operation interact with stack, operator must be created withoud parameters
 * traitementOperator works alone, do not push results to the stack
 *
 */

class Operateur : public Operande
{
    static QString symbole;
 protected:
    Pile& p = Pile::donnerInstance();
public:

    Operateur(){}
    static QString getSymbole(){return symbole;}
    virtual void chargerContexte() = 0;
    virtual void pushResultat(Litterale* res) {p<<(*res);}
    void operation(){chargerContexte(); Litterale* res=traitementOperateur(); pushResultat(res);}
    virtual Litterale* traitementOperateur() =0;
    virtual Operateur* getCopy()=0;
};


class OperateurBinaire : public Operateur{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){p>>l2;
                           p>>l1;}
    OperateurBinaire(){}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):l1(lit1),l2(lit2){}
};

class OperateurUnaire  : public Operateur{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;}

   OperateurUnaire(){}
   OperateurUnaire(Litterale* lit1):l1(lit1){}
};

class OperateurNeg : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurNeg():OperateurUnaire(){}
   OperateurNeg(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNeg* getCopy() {return new OperateurNeg(*this);}
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
#endif // OPERATEUR_H
