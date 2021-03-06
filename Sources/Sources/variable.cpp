#include "variable.h"
#include "litterales.h"
#include "litteraleexception.h"

unsigned int VariablesManager::nb_prog=0;
unsigned int VariablesManager::nb_var=0;
QMap<QString, Litterale*> VariablesManager::var_map= QMap<QString,Litterale*>();
VariablesManager* VariablesManager::instance=nullptr;
VariablesManager& VariablesManager::donnerInstance(){
    if(instance==nullptr)
        instance= new VariablesManager;
    return *instance;
}
void VariablesManager::libererInstance(){
    instance=nullptr;
}

void VariablesManager::enregistrer(QString nom,Litterale* obj){
    if(estdeType<Programme>(obj))
        nb_prog++;
    else
        nb_var++;
    var_map.insert(nom,obj);
}
void VariablesManager::supprimer(const QString& nom){
    Litterale* obj=var_map.find(nom).value();
    if(obj){
        if(estdeType<Programme>(obj))
            nb_prog--;
        else
            nb_var--;
        var_map.remove(nom);
        delete obj;
    }
}

VariablesManager::~VariablesManager(){
    for(QMap<QString, Litterale*>::iterator it = var_map.begin();it!=var_map.end();++it)
        delete it.value(); //on détruit les Variables ou programmes stockées
}

Litterale* VariablesManager::getVariable(const QString& nom){
    if(var_map.contains(nom))
    return (var_map.find(nom)).value()->getCopy();
    throw LitteraleException(nom + " ne référence pas de variable ou programme","Variable");
}

QMap<QString, Litterale*>::const_iterator VariablesManager::getVariablesBegin(){
    return var_map.begin();
}

QMap<QString, Litterale*>::const_iterator VariablesManager::getVariablesEnd(){
     return var_map.end();
}

void VariablesManager::clearVariables(){
    foreach(Litterale* l,var_map)
        delete l;
    var_map.clear();
    nb_var=0;
    nb_prog=0;
}
