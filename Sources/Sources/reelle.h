 #include "entier.h"

#ifndef REELLE_H
#define REELLE_H
class Reelle : public LitteraleNumerique{
    Entier p_entiere;
    Entier mantisse;
public:
    /*La partie entiere dit etre le second paramêtre pour avoir une valeur par défaut*/
    Reelle(Entier m,Entier p=0):p_entiere(p){
        /*Un réel ne peut pas être construit avec une mantisse nulle*/
        if(m.getValeur()==0){LitteraleException("Construction: Mantisse nulle !");}
        else{mantisse=p;}
    }
    ~Reelle(){};
    Entier getPartieEntiere(){return p_entiere;}
    Entier getMantisse(){return mantisse;}
    LitteraleNumerique& Simplification();
    const std::string toString() const;

};

#endif // REELLE_H
