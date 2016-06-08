#ifndef VARIABLE_H
#define VARIABLE_H
#include <QMap>
#include "operande.h"


//Forward declarations
class gestionvariableWindow;
class Litterale;

//gère aussi les programmes
class VariablesManager{
    static QMap<QString, Litterale*> var_map;
    static VariablesManager* instance;
    VariablesManager(){}
    ~VariablesManager();
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

    //Pour enregistrer des nouvelles variables
    static void enregistrer(const QString& nom,Litterale* obj);
    static void supprimer(const QString& nom);
    static Litterale* getVariable(const QString& nom);
    static QMap<QString, Litterale*>::iterator getVariablesBegin();
    static QMap<QString, Litterale*>::iterator getVariablesEnd();

};

#endif // VARIABLE_H
