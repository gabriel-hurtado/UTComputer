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
     *  @brief Lit une suite d'opérations à effectuer : empilement de littérale (2 modes) sur la pile ou execution d'opérateur.
     *  @param s chaine de caractère qui contient les différentes opérations à effectuer.
     *  @param litterale_mode mode de construction des littérales dans la litteralefactory.
     *  @return true si toutes les opérations ont été comprises, false sinon et s contient les instructions restantes.
     */
    bool commande(QString& s,QString litterale_mode = "RPN") const;

    /**
     *  @brief Permet d'extraire le premier mot (première action) à traiter.
     *  Pour trouver le mot on utilise l'objet de type WordIdentifier associé au symbole que l'on trouve dans l'interpretation_map.
     *  @param s chaine de caratère contenant plusieurs mots
     *  @return une chaine de caratère contenant le premier mot
    */
    static QString firstWord(QString s);

    /**
     *  @brief pour associer un symbole à un WordIdentifier
     *  Enregistre le symbole et le pointeur sur le WordIdentifier dans l'interpretation_map du controleur
     */
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
