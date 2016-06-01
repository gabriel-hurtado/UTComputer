#include "variable.h"


QMap<QString, Variable*> VariablesManager::var_map= QMap<QString,Variable*>();
VariablesManager* VariablesManager::instance=nullptr;
VariablesManager& VariablesManager::donnerInstance(){
    if(instance==nullptr)
        instance= new VariablesManager;
    return *instance;
}
void VariablesManager::libererInstance(){
    instance=nullptr;
}

void VariablesManager::enregistrer(const QString& nom,Variable* obj){
    var_map.insert(nom,obj);
}
void VariablesManager::supprimer(const QString& nom){
    var_map.remove(nom);
}

VariablesManager::~VariablesManager(){
    for(QMap<QString, Variable*>::iterator it = var_map.begin();it!=var_map.end();++it)
        delete it.value(); //on détruit les Variables stockées
}

Variable& VariablesManager::getVariable(const QString& nom){
    if(var_map.contains(nom))
    return *(var_map.find(nom)).value();
    throw VariableException("Var does not exist");
}
