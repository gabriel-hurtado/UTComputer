#ifndef VARIABLE_H
#define VARIABLE_H
#include "litterales.h"
#include "gestionvariablewindow.h"
#include <map>




//gère aussi les programmes
class VariablesManager{
    static QMap<QString, Litterale*> var_map;
    static VariablesManager* instance;
    VariablesManager(){}
    ~VariablesManager();
    void operator=(VariablesManager& l);
    VariablesManager(VariablesManager& l);

public:
    friend class gestionvariableWindow;
    /*Méthodes du singleton*/
    static VariablesManager& donnerInstance();
    static void libererInstance();

    //Pour enregistrer des nouvelles variables
    static void enregistrer(const QString& nom,Litterale* obj);
    static void supprimer(const QString& nom);
    static Litterale* getVariable(const QString& nom);

    //
};

#endif // VARIABLE_H
