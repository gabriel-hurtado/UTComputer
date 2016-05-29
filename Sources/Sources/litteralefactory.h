
#ifndef LITTERALEFACTORY_H
#define LITTERALEFACTORY_H

#include "litterales.h"
#include <map>

class LitteraleFactory
{
    static LitteraleFactory* instanceLitteraleFactory;
    /*
        lf_map stand for litteralefactory map

        Plus facile à manipuler si c'est static
        (évite de passer par l'instance pour la méthode enregistrer et creer)
    */
    static std::map<std::string, Litterale*> lf_map;
    LitteraleFactory();
    ~LitteraleFactory();
    void operator=(LitteraleFactory& l);
    LitteraleFactory(LitteraleFactory& l);

public:
    /*Méthodes du singleton*/
    static LitteraleFactory& donnerInstance();
    static void libererInstance();

    //Pour enregistrer de nouveaux objets
    static void enregistrer(const std::string& cle,Litterale* obj);

    //Pour créer des objets à partir de la factory
    Litterale* creer(const std::string& cle);

};

#endif // LITTERALEFACTORY_H
