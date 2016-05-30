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
    static std::map<unsigned int,std::string> litterale_priority_map; //Map des symboles de litterales ex <"$",Complexe>
    std::map<std::string,std::string> operator_map;



public:
    /*Méthodes pour le singleton*/
    static Controleur& donnerInstance();
    static void libererInstance();
    static void enregistrer(std::string symbole,unsigned int priority);

    void commande(const std::string s);
    std::string firstWord(std::string s);


};

#endif // CONTROLEUR_H
