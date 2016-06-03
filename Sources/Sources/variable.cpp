#include "variable.h"


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

void VariablesManager::enregistrer(const QString& nom,Litterale* obj){
    var_map.insert(nom,obj);
}
void VariablesManager::supprimer(const QString& nom){
    var_map.remove(nom);
}

VariablesManager::~VariablesManager(){
    for(QMap<QString, Litterale*>::iterator it = var_map.begin();it!=var_map.end();++it)
        delete it.value(); //on détruit les Variables ou programmes stockées
}

Litterale* VariablesManager::getVariable(const QString& nom){
    if(var_map.contains(nom))
    return (var_map.find(nom)).value()->getCopy();
    throw LitteraleException("Variable or program does not exist");
}
