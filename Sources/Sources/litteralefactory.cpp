#include "litteralefactory.h"

LitteraleFactory* LitteraleFactory::instanceLitteraleFactory = nullptr;

std::map<QString, Litterale*> LitteraleFactory::lf_map = std::map<QString, Litterale*>();


LitteraleFactory& LitteraleFactory::donnerInstance(){
    if(instanceLitteraleFactory==nullptr)
        instanceLitteraleFactory=new LitteraleFactory;
    return *instanceLitteraleFactory;
}
/*Le constructeur par défaut suffit, par contre le destructeur non*/

LitteraleFactory::LitteraleFactory(){}

LitteraleFactory::~LitteraleFactory(){
    for(std::map<QString, Litterale*>::iterator it = lf_map.begin();it!=lf_map.end();++it)
        delete it->second; //on détruit les Litterales* qui servaient de patron
}

void LitteraleFactory::enregistrer(const QString& cle, Litterale* l){
    if(lf_map.find(cle)==lf_map.end()) //Si pas déja la clé
        lf_map[cle]=l;
}

Litterale* LitteraleFactory::creer(const QString &cle){
    std::map<QString, Litterale*>::const_iterator it = lf_map.find(cle);
    Litterale* tmp = nullptr;
    if(it!=lf_map.end())
        tmp = it->second->getCopy();
    else
        throw LitteraleException("La littérale "+cle+" n'existe pas !");
    return tmp;
}
