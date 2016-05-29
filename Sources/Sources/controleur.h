#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "operande.h"
#include "pile.h"

class Controleur
{
    static Controleur* instanceControleur;
    Controleur();
    virtual ~Controleur();
    Controleur(const Controleur&);
    void operator =(const Controleur&);
    std::map<std::string,std::string> symbol_map;


public:
    /*Méthodes pour le singleton*/
    static Controleur& donnerInstance();
    static Controleur& libererInstance();

    void commande(const std::string s);

    static std::string firstWord(std::string s);


};

#endif // CONTROLEUR_H
