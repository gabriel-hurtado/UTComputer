#ifndef VARIABLE_H
#define VARIABLE_H
#include <QMap>
#include "operande.h"


//Forward declarations
class gestionvariableWindow;
class Litterale;


/**
 * @brief Classe de gestion de variables et de programmes
 *
 */
class VariablesManager{
    static QMap<QString, Litterale*> var_map;
    static VariablesManager* instance;
    VariablesManager(){}
    virtual ~VariablesManager();
    void operator=(VariablesManager& l);
    VariablesManager(VariablesManager& l);
    static unsigned int nb_prog;
    static unsigned int nb_var;

public:
    /*Méthodes du singleton*/
    static VariablesManager& donnerInstance();
    static void libererInstance();
    static unsigned int getNbProg(){return nb_prog;}
    static unsigned int getNbVar(){return nb_var;}

    /**
     * @brief Pour enregistrer des nouvelles variables
     * @param nom
     * @param obj
     */
    static void enregistrer(const QString& nom,Litterale* obj);
    static void supprimer(const QString& nom);
    static Litterale* getVariable(const QString& nom);
    static QMap<QString, Litterale*>::const_iterator getVariablesBegin();
    static QMap<QString, Litterale*>::const_iterator getVariablesEnd();
    static void clearVariables();

};

#endif // VARIABLE_H
