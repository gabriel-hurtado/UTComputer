#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "pile.h"
#include "litteralefactory.h"
#include "operateur.h"
#include "operateurfactory.h"

/*
    Classe contenant la statégie d'identification à adopter
*/
struct SelectedPosition{
    QString::iterator it_debut;
    QString::iterator it_fin;
};
/*
    Version générique de l'identifieur, va jusqu'au prochain espace.
*/
class WordIdentifier{
public:
    WordIdentifier(){}
    virtual ~WordIdentifier(){}
    virtual void WordPosition(QString s, const SelectedPosition& Select);
};

/*
    Pour des encapsulateurs comme des expressions
*/
class EncapsulatorIdentifier: public WordIdentifier{
    QString rightDelimiter;
    QString leftDelimiter;
public:
    EncapsulatorIdentifier(QString rD="",QString lD=""):rightDelimiter(rD),leftDelimiter(lD){}
    void WordPosition(QString s, const SelectedPosition& Select);
    void setRightDelimiter(QString s){rightDelimiter = s;}
    void setLeftDelimiter(QString s){leftDelimiter = s;}

};
/*
    Pour des encapsulateurs réccursifs, comme des programmes
*/
class RecursiveEncapsulatorIdentifier: public WordIdentifier{
    QString rightDelimiter;
    QString leftDelimiter;
public:
    RecursiveEncapsulatorIdentifier(QString rD="",QString lD=""):rightDelimiter(rD),leftDelimiter(lD){}
    void WordPosition(QString s, const SelectedPosition& Select);
    void setRightDelimiter(QString s){rightDelimiter = s;}
    void setLeftDelimiter(QString s){leftDelimiter = s;}


};

class Controleur
{
    /*
        Instance du controleur
        car on en a besoin que d'un seul.
    */
    static Controleur* instanceControleur;
    static QMap<QString,QString> symbolMap;
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
    bool commande(QString& s);

    /*
        Permet d'extraire le premier mot (première action) à traiter.
        Les programmes et expressions pouvant contenir des espaces,
        leur détection à été écrite en dur dans cette méthode.
        L'idéal serait de trouver une autre façon de faire mais celà est difficile par manque de temps
    */
    QString firstWord(QString s);
    /*
        Méthode pour enregistrer un symbole pour le WordFinder
    */
    static void enregistrerSymbole(QString,QString rtok ="");
    static void enregistrerSymbole(QString,QString rtok ="", WordIdentifier* W = new WordIdentifier);


};

#endif // CONTROLEUR_H
