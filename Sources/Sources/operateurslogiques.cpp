

#include "operateurslogiques.h"
#include "litterales.h"


namespace logique{


Litterale* OperateurEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {

    }
    throw OperateurException("Error in $");
}

Litterale* OperateurDiff::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

Litterale* OperateurInfEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

Litterale* OperateurSupEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

Litterale* OperateurSup::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

Litterale* OperateurInf::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

Litterale* OperateurAND::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

Litterale* OperateurOR::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

Litterale* OperateurNOT::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}
}
