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

class OperateurNEG : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurNEG():OperateurUnaire(){}
   OperateurNEG(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNEG* getCopy() {return new OperateurNEG(*this);}
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

class OperateurNUM : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurNUM():OperateurUnaire(){}
   OperateurNUM(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNUM* getCopy() {return new OperateurNUM(*this);}
};

class OperateurDEN : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurDEN():OperateurUnaire(){}
   OperateurDEN(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurDEN* getCopy() {return new OperateurDEN(*this);}
};

class OperateurIM : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurIM():OperateurUnaire(){}
   OperateurIM(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurIM* getCopy() {return new OperateurIM(*this);}
};

class OperateurRE : public OperateurUnaire{
public:
   Litterale* traitementOperateur();

   OperateurRE():OperateurUnaire(){}
   OperateurRE(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurRE* getCopy() {return new OperateurRE(*this);}
};

class Operateur$ : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   Operateur$():OperateurBinaire(){}
   Operateur$(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   Operateur$* getCopy() {return new Operateur$(*this);}

};

class OperateurEgal : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurEgal():OperateurBinaire(){}
   OperateurEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurEgal* getCopy() {return new OperateurEgal(*this);}

};

class OperateurDiff : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurDiff():OperateurBinaire(){}
   OperateurDiff(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurDiff* getCopy() {return new OperateurDiff(*this);}

};

class OperateurInfEgal : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurInfEgal():OperateurBinaire(){}
   OperateurInfEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurInfEgal* getCopy() {return new OperateurInfEgal(*this);}

};


class OperateurSupEgal : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurSupEgal():OperateurBinaire(){}
   OperateurSupEgal(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSupEgal* getCopy() {return new OperateurSupEgal(*this);}

};

class OperateurSup : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurSup():OperateurBinaire(){}
   OperateurSup(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurSup* getCopy() {return new OperateurSup(*this);}

};


class OperateurInf: public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurInf():OperateurBinaire(){}
   OperateurInf(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurInf* getCopy() {return new OperateurInf(*this);}

};


class OperateurAND: public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurAND():OperateurBinaire(){}
   OperateurAND(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurAND* getCopy() {return new OperateurAND(*this);}

};

class OperateurOR: public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurOR():OperateurBinaire(){}
   OperateurOR(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurOR* getCopy() {return new OperateurOR(*this);}

};

class OperateurNOT: public OperateurBinaire{
public:
   Litterale* traitementOperateur();

   OperateurNOT():OperateurBinaire(){}
   OperateurNOT(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurNOT* getCopy() {return new OperateurNOT(*this);}

};
#endif // OPERATEUR_H
