#include "reelle.h"
/*Simplification retourne une référence sur litterale numerique allouée dynaiquement*/
LitteraleNumerique& Reelle::Simplification(){
    LitteraleNumerique* ptr;
    if(mantisse.getValeur()==0)
         ptr = new Entier(p_entiere);
    else{ptr=this;}
    return *ptr;
}

const std::string Reelle::toString() const {
    std::stringstream s;
    if(p_entiere.getValeur()!=0)
        s<<p_entiere.toString();
    s<<".";
    if(mantisse.getValeur()!=0)
        s<<mantisse.toString();
    return s.str();
}
