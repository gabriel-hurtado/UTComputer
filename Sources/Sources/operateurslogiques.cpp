

#include "operateurslogiques.h"
#include "litterales.h"


namespace logique{


Litterale* OperateurEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()==li2->getValeur())
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in egal");
}

Litterale* OperateurDiff::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()!=li2->getValeur())
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in diff");
}

Litterale* OperateurInfEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()<=li2->getValeur())
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in InfOuEgal");
}

Litterale* OperateurSupEgal::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()>=li2->getValeur())
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in SupOuEgal");
}

Litterale* OperateurSup::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()>li2->getValeur())
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in sup");
}

Litterale* OperateurInf::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()<li2->getValeur())
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in inf");
}

Litterale* OperateurAND::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()!=0 && li2->getValeur()!=0)
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in and");
}

Litterale* OperateurOR::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()!=0 || li2->getValeur()!=0)
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in or");
}

Litterale* OperateurNOT::traitementOperateur(){
    LitteraleNumerique* li1=estdeType<LitteraleNumerique>(l1);
    LitteraleNumerique* li2=estdeType<LitteraleNumerique>(l2);
    if(li1 && li2)
    {
        if(li1->getValeur()==0 && li2->getValeur()==0)
            return new Entier(1);
        return new Entier(0);
    }
    throw OperateurException("Error in not");
}
}
