
#ifndef OPERATEURSNUMERIQUES_H
#define OPERATEURSNUMERIQUES_H

#include "operateur.h"

class Litterale;

/*
 * Operation interact with stack, operator must be created withoud parameters
 * traitementOperator works alone, do not push results to the stack
 *
 */

namespace numerique{

class OperateurNumerique : public virtual Operateur
{
public:
    virtual void pushResultat(Litterale* res);

    OperateurNumerique(){setPriority(2);}

    virtual Litterale* traitementOperateur() =0;
    virtual ~OperateurNumerique(){}
    Operateur* getCopy() const = 0;

};



class OperateurNEG : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurNEG():OperateurUnaire(){}
   OperateurNEG(Litterale* lit1):OperateurUnaire(lit1){}
   Operateur* getCopy() const{return new OperateurNEG(*this);}

};

class OperateurAddition : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurAddition():OperateurBinaire(){setPriority(3);}
   OperateurAddition(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(3);}
   Operateur* getCopy() const{return new OperateurAddition(*this);}
};

class OperateurSoustraction : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurSoustraction():OperateurBinaire(){setPriority(3);}
   OperateurSoustraction(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(3);}
   Operateur* getCopy() const{return new OperateurSoustraction(*this);}

};

class OperateurDivision : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurDivision():OperateurBinaire(){setPriority(4);}
   OperateurDivision(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(4);}
   Operateur* getCopy() const{return new OperateurDivision(*this);}
};


class OperateurMultiplication : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   OperateurMultiplication():OperateurBinaire(){setPriority(4);}
   OperateurMultiplication(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(4);}
   Operateur* getCopy() const{return new OperateurMultiplication(*this);}
};

class OperateurDIV : public OperateurBinaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurDIV():OperateurBinaire(){}
   OperateurDIV(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurDIV(*this);}

};

class OperateurMOD : public OperateurBinaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurMOD():OperateurBinaire(){}
   OperateurMOD(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new OperateurMOD(*this);}

};

class OperateurNUM : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();
   OperateurNUM():OperateurUnaire(){}
   OperateurNUM(Litterale* lit1):OperateurUnaire(lit1){}
   Operateur* getCopy() const{return new OperateurNUM(*this);}

};

class OperateurDEN : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurDEN():OperateurUnaire(){}
   OperateurDEN(Litterale* lit1):OperateurUnaire(lit1){}
   Operateur* getCopy() const{return new OperateurDEN(*this);}

};

class OperateurIM : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurIM():OperateurUnaire(){}
   OperateurIM(Litterale* lit1):OperateurUnaire(lit1){}
   Operateur* getCopy() const{return new OperateurIM(*this);}

};

class OperateurRE : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   OperateurRE():OperateurUnaire(){}
   OperateurRE(Litterale* lit1):OperateurUnaire(lit1){}
   Operateur* getCopy() const{return new OperateurRE(*this);}

};

class Operateur$ : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   Operateur$():OperateurBinaire(){}
   Operateur$(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}
   Operateur* getCopy() const{return new Operateur$(*this);}

};
}

#endif // OPERATEURSNUMERIQUES_H
