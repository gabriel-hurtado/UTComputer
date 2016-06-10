#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include <QMap>
#include "operande.h"
class WordIdentifier;


class Controleur
{
    /*
        Instance du controleur
        car on en a besoin que d'un seul.
    */
    static Controleur* instanceControleur;
    /*
        Map qui contient tous les symboles connus
    */
    static QMap<QString,QString> symbolMap;
    /*
        Map qui contient les pointeurs sur la class d'interprétation du mot
    */
    static QMap<QString,WordIdentifier*> interpretationMap;


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
    bool commande(QString& s,QString litterale_mode = "RPN");

    /*
        Permet d'extraire le premier mot (première action) à traiter.
        Les programmes et expressions pouvant contenir des espaces,
        leur détection à été écrite en dur dans cette méthode.
        L'idéal serait de trouver une autre façon de faire mais celà est difficile par manque de temps
    */
    static QString firstWord(QString s);
    /*
        Méthode pour enregistrer un symbole pour le WordFinder
    */
    //static void enregistrerSymbole(QString,QString rtok ="");
    static void enregistrerSymbole(QString,QString rtok ="", WordIdentifier* W = nullptr);

    static QString SpaceCleaner(QString);

    static QString ParenthesisCleaner(QString s, unsigned int priority);

    static const QMap<QString,WordIdentifier*>& getInterpretationMap(){return interpretationMap;}

    static const QMap<QString,QString>& getSymbolMap(){return symbolMap;}

};

#endif // CONTROLEUR_H
