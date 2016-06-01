#include "litteralefactory.h"

LitteraleFactory* LitteraleFactory::instanceLitteraleFactory = nullptr;

QMap<unsigned int , QString> LitteraleFactory::priority_map = (QMap<unsigned int , QString>());
QMap<QString, Litterale*> LitteraleFactory::litterale_map = (QMap<QString, Litterale*>());

LitteraleFactory& LitteraleFactory::donnerInstance(){
    if(instanceLitteraleFactory==nullptr)
        instanceLitteraleFactory=new LitteraleFactory;
    return *instanceLitteraleFactory;
}
/*Le constructeur par défaut suffit, par contre le destructeur non*/

LitteraleFactory::LitteraleFactory(){}

LitteraleFactory::~LitteraleFactory(){}

void LitteraleFactory::enregistrer(unsigned int prio,QString tok, Litterale* l){
    QMap<unsigned int,QString>::iterator it_prio = priority_map.find(prio);
    if(it_prio==priority_map.end()){            //Si la priorité n'est pas déja prise
        if(litterale_map.find(tok)==litterale_map.end()){//Si le token n'est pas déja pris
            priority_map[prio]=tok;             //On enregistre le token dans la priority_map
            litterale_map[tok]=l;               //On enregistre le pointeur sur litterale dans la base
        }
        else
            throw LitteraleException("Token déja pris");
    }
    else
        throw LitteraleException("Priorité déja prise");

}



Litterale* LitteraleFactory::creer(QString litt_str){
    QMap<unsigned int,QString>::iterator it_prio = priority_map.begin();
    while(it_prio!=priority_map.end() && !litt_str.contains(it_prio.value())){//On cherche le token dans la chaine de caractère par ordre de priorité
        it_prio++;
    }
    if(it_prio!=priority_map.end()){
        return litterale_map.find(it_prio.value()).value()->getFromString(litt_str);
    }
    //Cela peut encore etre un Entier

    else{
        bool ok;
        int tmp = litt_str.toInt(&ok); //On tente de convertir en entier
        if(ok) return new Entier(tmp);

    }
    return nullptr;
}

