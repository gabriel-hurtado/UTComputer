#ifndef H_OPERATEURFACTORY
#define H_OPERATEURFACTORY

#include "operateur.h"
#include "operateursnumeriques.h"
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
    static QMap<QString, Operateur*> of_map;
    OperateurFactory();
    ~OperateurFactory();
    void operator=(OperateurFactory& l);
    OperateurFactory(OperateurFactory& l);

public:
    /*Méthodes du singleton*/
    static OperateurFactory& donnerInstance();
    static void libererInstance();

    //Pour enregistrer de nouveaux objets
    static void enregistrer(const QString& cle,Operateur* obj);

    //Pour créer des objets à partir de la factory
    Operateur* creer(const QString& cle);

    //Pour acceder à la qmap dans atome
    static const QMap<QString,Operateur*> getMap(){return of_map;}

};


#endif // OPERATEURFACTORY_H
