#ifndef VARIABLE_H
#define VARIABLE_H
#include "litterales.h"
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
    /*Méthodes du singleton*/
    static VariablesManager& donnerInstance();
    static void libererInstance();

    //Pour enregistrer des nouvelles variables
    static void enregistrer(const QString& nom,Litterale* obj);
    static void supprimer(const QString& nom);
    static Litterale* getVariable(const QString& nom);
    static QMap<QString, Litterale*>::iterator getVariablesBegin();
    static QMap<QString, Litterale*>::iterator getVariablesEnd();

};

#endif // VARIABLE_H
