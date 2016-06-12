#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include <QMap>
#include "operande.h"
class WordIdentifier;


class Controleur
{
    /**
     * @brief Pointeur sur l'unique instance du controleur (Signleton)
     *
     */
    static Controleur* instanceControleur;
    /**
     * @brief Map qui contient les pointeurs sur l'objet d'interpretation du mot
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

    /**
     *  @brief Lit une suite d'opérations à effectuer : empilement de littérale sur la pile ou execution d'opérateur.
     *  @param s chaine de caractère qui contient les différentes opérations à effectuer
     *  @param litterale_mode mode de construction des littérales dans la litteralefactory
     *  Valeur de retour :
     *      -lorsque toutes les actions se sont correctement éffectuées : true
     *      -sinon false et s contient seulement l'action non comprise
    */
    bool commande(QString& s,QString litterale_mode = "RPN") const;

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
    static void enregistrerSymbole(QString, WordIdentifier* W = nullptr);

    static QString SpaceCleaner(QString);

    /**
     * @brief Supprime les parenthèses inutiles
     * Sert pour des opérations entre deux expressions
     * @param s chaine de caractères de l'expression
     * @param priority priorité de l'opérateur utilisé lors de l'opération entre expressions
     * @return la chaine de caractères, de l'expression, sans parenthèses si elles sont inutiles
     */
    static QString ParenthesisCleaner(QString s, unsigned int priority);

    static const QMap<QString,WordIdentifier*>& getInterpretationMap(){return interpretationMap;}


};

#endif // CONTROLEUR_H
