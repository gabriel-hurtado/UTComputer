

#include "operateurslogiques.h"
#include "litterales.h"


namespace logique{


bool OperateurEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {

    }
    throw OperateurException("Error in $");
}

bool OperateurDiff::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

bool OperateurInfEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

bool OperateurSupEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

bool OperateurSup::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

bool OperateurInf::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

bool OperateurAND::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

bool OperateurOR::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}

bool OperateurNOT::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
    }
    throw OperateurException("Error in $");
}
}
