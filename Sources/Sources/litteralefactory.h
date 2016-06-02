
#ifndef LITTERALEFACTORY_H
#define LITTERALEFACTORY_H
#include "litterales.h"
#include <map>
#include "pile.h"

class LitteraleFactory
{
    static LitteraleFactory* instanceLitteraleFactory;
    /*
        lf_map stand for litteralefactory map

        Plus facile à manipuler si c'est static
        (évite de passer par l'instance pour la méthode enregistrer et creer)
    */
    static QMap<unsigned int, QString> priority_map_basic;
    static QMap<unsigned int, QString> priority_map_infix;
    static QMap<QString, Litterale*>   litterale_map;
    LitteraleFactory();
    ~LitteraleFactory();
    void operator=(LitteraleFactory& l);
    LitteraleFactory(LitteraleFactory& l);

public:
    /*Méthodes du singleton*/
    static LitteraleFactory& donnerInstance();
    static void libererInstance();

    //Pour enregistrer de nouveaux objets
    static void enregistrer(unsigned int,QString,Litterale*);
    static void enregistrerInfix(unsigned int,QString,Litterale*);

    //Pour créer des objets à partir de la factory
    Litterale* creerRPNLitterale(QString);
    Litterale* creerInfixLitterale(QString);

};



#endif // LITTERALEFACTORY_H
