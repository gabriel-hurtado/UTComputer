
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

};



class OperateurNEG : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="NEG";}
   OperateurNEG():OperateurUnaire(){}
   OperateurNEG(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNEG* getCopy() {return new OperateurNEG(*this);}
};

class OperateurAddition : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){ symbole="+";}
   OperateurAddition():OperateurBinaire(){setPriority(3);}
   OperateurAddition(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(3);}

   OperateurAddition* getCopy() {return new OperateurAddition(*this);}
};

class OperateurSoustraction : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){   symbole="-";}
   OperateurSoustraction():OperateurBinaire(){setPriority(3);}
   OperateurSoustraction(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(3);}

   OperateurSoustraction* getCopy() {return new OperateurSoustraction(*this);}
};

class OperateurDivision : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="/";}
   OperateurDivision():OperateurBinaire(){setPriority(4);}
   OperateurDivision(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(4);}
   OperateurDivision* getCopy() {return new OperateurDivision(*this);}
};


class OperateurMultiplication : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){ symbole="*";}
   OperateurMultiplication():OperateurBinaire(){setPriority(4);}
   OperateurMultiplication(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){setPriority(4);}

   OperateurMultiplication* getCopy() {return new OperateurMultiplication(*this);}

};

class OperateurDIV : public OperateurBinaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="DIV";}
   OperateurDIV():OperateurBinaire(){}
   OperateurDIV(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurDIV* getCopy() {return new OperateurDIV(*this);}

};

class OperateurMOD : public OperateurBinaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="MOD";}
   OperateurMOD():OperateurBinaire(){}
   OperateurMOD(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   OperateurMOD* getCopy() {return new OperateurMOD(*this);}

};

class OperateurNUM : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="NUM";}
   OperateurNUM():OperateurUnaire(){}
   OperateurNUM(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurNUM* getCopy() {return new OperateurNUM(*this);}
};

class OperateurDEN : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="DEN";}
   OperateurDEN():OperateurUnaire(){}
   OperateurDEN(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurDEN* getCopy() {return new OperateurDEN(*this);}
};

class OperateurIM : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="IM";}
   OperateurIM():OperateurUnaire(){}
   OperateurIM(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurIM* getCopy() {return new OperateurIM(*this);}
};

class OperateurRE : public OperateurUnaire, public OperateurNumerique,public OperateurPrefixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="RE";}
   OperateurRE():OperateurUnaire(){}
   OperateurRE(Litterale* lit1):OperateurUnaire(lit1){}

   OperateurRE* getCopy() {return new OperateurRE(*this);}
};

class Operateur$ : public OperateurBinaire, public OperateurNumerique,public OperateurInfixe{

public:
   Litterale* traitementOperateur();

   void initSymbole(){symbole="$";}
   Operateur$():OperateurBinaire(){}
   Operateur$(Litterale* lit1, Litterale* lit2):OperateurBinaire(lit1,lit2){}

   Operateur$* getCopy() {return new Operateur$(*this);}

};
}

#endif // OPERATEURSNUMERIQUES_H
