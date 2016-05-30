#include "operateurfactory.h"

OperateurFactory* OperateurFactory::instanceOperateurFactory = nullptr;

std::map<std::string, Operateur*> OperateurFactory::of_map = std::map<std::string, Operateur*>();


OperateurFactory& OperateurFactory::donnerInstance(){
    if(instanceOperateurFactory==nullptr)
        instanceOperateurFactory=new OperateurFactory;
    return *instanceOperateurFactory;
}
/*Le constructeur par défaut suffit, par contre le destructeur non*/

OperateurFactory::OperateurFactory(){}

OperateurFactory::~OperateurFactory(){
    for(std::map<std::string, Operateur*>::iterator it = of_map.begin();it!=of_map.end();++it)
        delete it->second; //on détruit les Operateurs* qui servaient de patron
}

void OperateurFactory::enregistrer(const std::string& cle, Operateur* l){
    if(of_map.find(cle)==of_map.end()) //Si pas déja la clé
        of_map[cle]=l;
}

Operateur* OperateurFactory::creer(const std::string& cle){
    std::map<std::string, Operateur*>::const_iterator it = of_map.find(cle);
    Operateur* tmp = nullptr;
    if(it!=of_map.end())
        tmp = it->second->getCopy();
    else
        throw OperateurException("'L'opérateur "+cle+" n'existe pas !");
    return tmp;
}
