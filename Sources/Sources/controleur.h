#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "pile.h"
#include "litteralefactory.h"
#include "operateur.h"
#include "operateurfactory.h"
class Controleur
{
    /*
        Instance du controleur
        car on en a besoin que d'un seul.
    */
    static Controleur* instanceControleur;

    //----------Méthodes privés pour le singleton-------------//

    Controleur();
    virtual ~Controleur();
    Controleur(const Controleur&);
    void operator =(const Controleur&);

public:

    //----------Méthodes publiques pour le singleton-------------//
    static Controleur& donnerInstance();
    static void libererInstance();

    /*
        Reçoie une QString qui regroupe les différentes actions à effetuer
        Celles-ci sont de 2 type :
            -construction et empilement d'une littérale
            -execution d'un commande

        Valeur de retour :
            -lorsque toutes les actions se sont correctement éffectuées : true
            -sinon false et s contient seulement l'action non comprise
    */
    bool commande(QString& s);

    /*
        Permet d'extraire le premier mot (première action) à traiter.
        Les programmes et expressions pouvant contenir des espaces,
        leur détection à été écrite en dur dans cette méthode.
        L'idéal serait de trouver une autre façon de faire mais celà est difficile par manque de temps
    */
    QString firstWord(QString s);


};

#endif // CONTROLEUR_H
