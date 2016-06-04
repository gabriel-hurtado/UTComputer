#include "litteralefactory.h"
#include "controleur.h"

LitteraleFactory* LitteraleFactory::instanceLitteraleFactory = nullptr;

QMap<unsigned int , QString> LitteraleFactory::priority_map_basic = (QMap<unsigned int , QString>());
QMap<unsigned int , QString> LitteraleFactory::priority_map_infix = (QMap<unsigned int , QString>());
QMap<QString, Litterale*> LitteraleFactory::litterale_map = (QMap<QString, Litterale*>());

LitteraleFactory& LitteraleFactory::donnerInstance(){
    if(instanceLitteraleFactory==nullptr)
        instanceLitteraleFactory=new LitteraleFactory;
    return *instanceLitteraleFactory;
}
/*Le constructeur par défaut suffit, par contre le destructeur non*/

LitteraleFactory::LitteraleFactory(){}

LitteraleFactory::~LitteraleFactory(){}

void LitteraleFactory::enregistrer(unsigned int prio,QString ltok, Litterale* l,QString rtok){
    QMap<unsigned int,QString>::iterator it_prio = priority_map_infix.find(prio);
    if(it_prio==priority_map_infix.end()){            //Si la priorité n'est pas déja prise
        if(litterale_map.find(ltok)==litterale_map.end()){//Si le token n'est pas déja pris
            priority_map_basic[prio]=ltok;       //On enregistre le token dans la priority_map
            priority_map_basic[prio]=ltok;
            litterale_map[ltok]=l;               //On enregistre le pointeur sur litterale dans la base
            Controleur::enregistrerSymbole(ltok,rtok);
        }
        else
            throw LitteraleException("Token déja pris");
    }
    else
        throw LitteraleException("Priorité déja prise");

}

void LitteraleFactory::enregistrerInfix(unsigned int prio,QString ltok, Litterale* l,QString rtok){
    QMap<unsigned int,QString>::iterator it_prio = priority_map_infix.find(prio);
    if(it_prio==priority_map_infix.end()){            //Si la priorité n'est pas déja prise
        if(litterale_map.find(ltok)==litterale_map.end()){//Si le token n'est pas déja pris
            priority_map_infix[prio]=ltok;             //On enregistre le token dans la priority_map
            litterale_map[ltok]=l;               //On enregistre le pointeur sur litterale dans la base
            Controleur::enregistrerSymbole(ltok,rtok);
        }
        else
            throw LitteraleException("Token déja pris");
    }
    else
        throw LitteraleException("Priorité déja prise");

}
/*
    Check if there if he can detect a known infix symbol and do what he can with it
    Useful for the parser.

*/
Litterale* LitteraleFactory::creerInfixLitterale(QString litt_str){
    QMap<unsigned int,QString>::iterator it_prio = priority_map_infix.begin();
    while(it_prio!=priority_map_infix.end() && !litt_str.contains(it_prio.value())){//On cherche le token dans la chaine de caractère par ordre de priorité
        it_prio++;
    }
    if(it_prio!=priority_map_infix.end()){
        return litterale_map.find(it_prio.value()).value()->getFromString(litt_str);
    }
    //Cela peut encore etre un Entier ou un Atome

    else{
        bool ok;
        int tmp = litt_str.toInt(&ok); //On tente de convertir en entier
        if(ok) return new Entier(tmp);

        if(Atome::isValidAtomeName(litt_str)){
            return new Atome(litt_str);
        }
    }
    return nullptr;
}


Litterale* LitteraleFactory::creerRPNLitterale(QString litt_str){
    QMap<unsigned int,QString>::iterator it_prio = priority_map_basic.begin();
    while(it_prio!=priority_map_basic.end() && !litt_str.contains(it_prio.value())){//On cherche le token dans la chaine de caractère par ordre de priorité
        it_prio++;
    }
    if(it_prio!=priority_map_basic.end()){
        return litterale_map.find(it_prio.value()).value()->getFromString(litt_str);
    }
    //Cela peut encore etre un Entier ou un Atome

    else{
        bool ok;
        int tmp = litt_str.toInt(&ok); //On tente de convertir en entier
        if(ok) return new Entier(tmp);

        if(Atome::isValidAtomeName(litt_str)){
            return new Atome(litt_str);
        }
    }
    return nullptr;
}

