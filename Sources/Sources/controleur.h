#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "operande.h"
#include "pile.h"
#include "litteralefactory.h"

class Controleur
{
    static Controleur* instanceControleur;
    Controleur();
    virtual ~Controleur();
    Controleur(const Controleur&);
    void operator =(const Controleur&);
    static std::map<unsigned int,QString> litterale_priority_map; //Map des symboles de litterales ex <"$",Complexe>
    std::map<QString,QString> operator_map;



public:
    /*Méthodes pour le singleton*/
    static Controleur& donnerInstance();
    static void libererInstance();
    static void enregistrer(QString symbole,unsigned int priority);

    void commande(const QString s);
    QString firstWord(QString s);


};

#endif // CONTROLEUR_H
