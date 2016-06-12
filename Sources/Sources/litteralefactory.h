
#ifndef LITTERALEFACTORY_H
#define LITTERALEFACTORY_H
#include "litterales.h"
#include "wordidentifier.h"//Obligé pour le parametre par défaut
#include <QMap>
class LitteraleFactory
{
    /**
     * Instance de la LitteraleFactory
     * On en a besoin que d'une seule après tout.
     */
    static LitteraleFactory* instanceLitteraleFactory;

    /**
     * Map qui contient seulement les priorités et symboles des litterales à considérer dans la ligne de commande
     */
    static QMap<unsigned int, QString> priority_map_basic;

    /**
     * Map qui contient absolument toutes les litterales dont le symbole est enregistré
     * Cette map sera utile pour parser des expression car l'écriture de la litterale est infixe.
    */
    static QMap<unsigned int, QString> priority_map_infix;

    /**
     * Map qui contient le symbole d'une litterale et un exemple de litterale qui lui est associé
     * La litterale associée est fourni lors de l'enregistrement et sert a pouvoir appeler la bonne version d'une méthode,
     * car le polymorphysme n'est pas utilisable puisque la donnée provient d'un string
    */
    static QMap<QString, Litterale*>   litterale_map;

    //----------Méthodes privés pour le singleton-------------//

    LitteraleFactory();
    virtual ~LitteraleFactory();
    void operator=(LitteraleFactory& l);
    LitteraleFactory(LitteraleFactory& l);

public:

    //----------Méthodes publiques et statiques pour le singleton-------------//

    static LitteraleFactory& donnerInstance();
    static void libererInstance();


    //----------Méthodes pour enregistrer de nouveaux objets-------------//

    /**
     * @brief Permet d'enregistrer un nouveau symbole de littérale dans la prority_basic_map.
     * @details En stockant un nouveau symbole dans la priority_basic_map, on peut créer une nouvelle littérale grâce à la méthode créerRPNLitterale ou creerInfixLitterale.
     * La méthode enregistre le symbole identifiant la littérale et l'exemple de littérale (l) dans la litterale_map, afin de permettre la construction ultérieur d'une nouvelle littérale.
     * On profite de cette méthode pour stocker l'objet qui permettra l'identification (W) dans l'interpretaion_map du controleur, ou elle est utilisée pour trouver la littérale en question dans une String contenant plusieurs opérations.
     * Attention : Cette méthode sert pour enregistrer des symboles interprétables :
     *     -> Directement par la commande
     *     -> Dans des programmes ou expressions ou tout autre objet appelant la méthode creerInfixLitterale ou la méthode creerRPNLitterale
     *
     * @param prio priorité unique (0 est le plus prioritaire).
     * @param ltok symbole permettant d'identifier la littérale (ou le début de celle-ci).
     * @param l exemple de litterale qui nous permettra d'acceder à la méthode getFromString(..).
     * @param W méthode d'identification de la littérale qui sera stockée dans l'interpretation_map du controleur (par défaut la méthode s'arretant au prochain espace est choisie).
     *
     */
    static void enregistrer(unsigned int prio,QString ltok,Litterale* l, WordIdentifier* W = new WordIdentifier);

    /**
     * @brief Identique à la méthode enregistrer sauf que l'on ne peut construire une littérale avec ce symbole unqiuement avec la méthode creerInfixLitterale
     *
     * @details Cette méthode sert à déclarer des symboles de littérale que l'on veut ne pouvoir construire qu'en évaluant des expressions
     */
    static void enregistrerInfix(unsigned int,QString,Litterale*, WordIdentifier* W = new WordIdentifier);

    /**
     * @brief Cette méthode crée des Litterales en fonction des symboles enregistrés dans la priority_basic_map.
     * @details La méthode détecte le symbole le plus prioritaire dans la string en paramêtre, et construit une nouvelle littérale en utilisant la méthode getFromString de la littérale associée au symbole détecté (association faite grâce à la litterale_map).
     * Attention : la méthode ne s'attend qu'a recevoir 1 SEUL mot, c'est à dire sans espaces !
     * La méthode getFromString doit être redéfinie dans la classe de la littérale linkée pour pouvoir créer l'objet correctement.
     * @param s littérale sous forme de chaine de caractère à traduire
     * @return Renvoie une littérale allouée dynamiquement correspondant à celle de la string s.
     */
    Litterale* creerRPNLitterale(QString s) const;

    /**
     * @brief Identique à la méthode créerRPNLitterale, mais fonctionne aussi avec les littérales déclarées grâce à la méthode enregistrerInfix
     * @details Cette méthode est donc plus puissante que creerRPNLitterale est peu être utilisée dans le controleur quand l'appelle avec "INFIX" en second paramêtre
     * @return Renvoie une littérale allouée dynamiquement correspondant à celle de la string s.
     */
    Litterale* creerInfixLitterale(QString) const;

    /**
     * @brief Détecte le type de litterale du paramêtre s et renvoie l'exemple de littérale stocké dans la litterale_map correspondant.
     * @param s littérale sous forme de string qui servira à trouver l'exemple correspondant.
     * @return Renvoie l'exemple de littérale stcoké ou nullptr s'il n'a trouvé aucune correspondance
     */
    Litterale* getRPNExampleOf(QString s) const;

    /**
     * @brief Idem à getRPNExampleOf avec les littérales paramétrées comme Infix
     * @param s littérale sous forme de string qui servira à trouver l'exemple correspondant.
     * @return Renvoie l'exemple de littérale stocké ou nullptr s'il n'a trouvé aucune correspondance.
     */
    Litterale* getInfixExampleOf(QString s) const;

    static const QMap<unsigned int,QString>& getPriorityMap(){return priority_map_basic;}

    static const QMap<QString,Litterale*>& getLitteraleMap(){return litterale_map;}
};



#endif // LITTERALEFACTORY_H
