#ifndef OPERATEURFACTORY_H
#define OPERATEURFACTORY_H


#include "operateur.h"
#include <map>


// !! A n'utiliser qu'avec la pile

class OperateurFactory
{
    static OperateurFactory* instanceOperateurFactory;
    /*
        of_map stand for operateurfactory map

        Plus facile à manipuler si c'est static
        (évite de passer par l'instance pour la méthode enregistrer et creer)
    */
    static std::map<std::string, Operateur*> of_map;
    OperateurFactory();
    ~OperateurFactory();
    void operator=(OperateurFactory& l);
    OperateurFactory(OperateurFactory& l);

public:
    /*Méthodes du singleton*/
    static OperateurFactory& donnerInstance();
    static void libererInstance();

    //Pour enregistrer de nouveaux objets
    static void enregistrer(const std::string& cle,Operateur* obj);

    //Pour créer des objets à partir de la factory
    Operateur* creer(const std::string& cle);

};


#endif // OPERATEURFACTORY_H
