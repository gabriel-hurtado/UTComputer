#include "litterales.h"

#ifndef OPERATEUR_H
#define OPERATEUR_H


class Operateur : public Operande
{
    static std::string symbole;
    static int arite;
public:

    Operateur();
    static int getArite(){return arite;}
    static std::string getSymbole(){return symbole;}
    virtual void chargerContexte() = 0;
    virtual Litterale* traitementOperateur() = 0;
    Litterale* traitement(){chargerContexte();return traitementOperateur();}
};

class OperateurBinaire : public Operateur{
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){l1 = new Entier(1);l2= new Entier(2);}

};
class OperateurUnaire  : public Operateur{

};



class OperateurAddition : public OperateurBinaire{
public:
   Litterale* traitementOperateur();

};

#endif // OPERATEUR_H
