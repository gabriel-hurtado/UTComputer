
#ifndef LITTERALEFACTORY_H
#define LITTERALEFACTORY_H
#include "litterales.h"
#include <map>
#include "pile.h"

class LitteraleFactory
{
    /*
        Instance de la LitteraleFactory
        On en a besoin que d'une seule après tout.
    */
    static LitteraleFactory* instanceLitteraleFactory;

    /*
        Map qui contient seulement les priorités et symboles des litterales à considérer dans la ligne de commande
    */
    static QMap<unsigned int, QString> priority_map_basic;
    /*
        Map qui contient absolument toutes les litterales dont le symbole est enregistré
        Cette map sera utile pour parser des expression car l'écriture de la litterale est infixe.
    */
    static QMap<unsigned int, QString> priority_map_infix;

    /*
        Map qui contient le symbole d'une litterale et un exemple de litterale qui lui est associé
        La litterale associée est fourni lors de l'enregistrement et sert a pouvoir appeler la bonne version d'une méthode,
        car le polymorphysme n'est pas utilisable puisque la donnée provient d'un string
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

    /*
        Permet d'enregistrer une nouvelle litterale avec :
            -une priorité unique (unsigned int)
            -un symbole qui permet d'identifier la litterale (QString)
            -un exemple de litterale ou l'on pourra acceder à la méthode getFromString(..).
        Attention : c'est au programmeur de définir le comportement de la méthode getFromString.


        Attention : Cette méthode sert pour enregistrer des symboles interprétables :
            -> Directement par la commande
            -> Dans des programmes ou expressions ou tout autre objet appelant la méthode creerInfixLitterale ou la méthode creerRPNLitterale

    */
    static void enregistrer(unsigned int,QString,Litterale*);

    /*
        Cette méthode est une version similaire de la méthode enregistrer
        Cependant les symboles enregistrés grâce à cette méthode ne fonctionnent que dans dans la méthode
            creerInfixLitterale

        Ils servent par exemple à traiter des litterales écrites dans des programmes ou des expressions.
    */
    static void enregistrerInfix(unsigned int,QString,Litterale*);

    /*
        Cette méthode cree des Litterales en fonction des symboles enregistrés dans la priority_basic_map,
        c'est à dire grâce à la méthode enregistrer

        Attention : la méthode ne s'attend qu'a recevoir 1 SEUL mot, c'est à dire sans espaces !
    */
    Litterale* creerRPNLitterale(QString);

    /*
        Cette méthode cree des Litterales en fonction des symboles enregistrés dans la priority_infix_map,
        c'est à dire grâce à la méthode enregistrerInfix

        Attention : la méthode ne s'attend qu'a recevoir 1 SEUL mot, c'est à dire sans espaces !
    */
    Litterale* creerInfixLitterale(QString);

};



#endif // LITTERALEFACTORY_H
