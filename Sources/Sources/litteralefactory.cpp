#include "litteralefactory.h"
#include "controleur.h"
#include "variable.h"
#include "litteraleexception.h"


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

void LitteraleFactory::enregistrer(unsigned int prio,QString ltok, Litterale* l,QString rtok, WordIdentifier* W){
    QMap<unsigned int,QString>::iterator it_prio = priority_map_infix.find(prio);
    if(it_prio==priority_map_infix.end()){            //Si la priorité n'est pas déja prise
        if(litterale_map.find(ltok)==litterale_map.end()){//Si le token n'est pas déja pris
            priority_map_basic[prio]=ltok;       //On enregistre le token dans la priority_map des litterales interpretables
            priority_map_infix[prio]=ltok;       //On enregistre le token dans la priority_map des littérales infixe utilisables
            litterale_map[ltok]=l;               //On enregistre le pointeur sur litterale dans la base
            Controleur::enregistrerSymbole(ltok,rtok,W);
        }
        else
            throw LitteraleException("Token déja pris","Enregistrement");
    }
    else
        throw LitteraleException("Priorité déja prise","Enregistrement");

}

void LitteraleFactory::enregistrerInfix(unsigned int prio,QString ltok, Litterale* l,QString rtok,WordIdentifier* W){
    QMap<unsigned int,QString>::iterator it_prio = priority_map_infix.find(prio);
    if(it_prio==priority_map_infix.end()){            //Si la priorité n'est pas déja prise
        if(litterale_map.find(ltok)==litterale_map.end()){//Si le token n'est pas déja pris
            priority_map_infix[prio]=ltok;

            litterale_map[ltok]=l;               //On enregistre le pointeur sur litterale dans la base
            Controleur::enregistrerSymbole(ltok,rtok,W);
        }
        else
            throw LitteraleException("Token déja pris","Enregistrement");
    }
    else
        throw LitteraleException("Priorité déja prise","Enregistrement");

}
/*
    Check if there if he can detect a known infix symbol and do what he can with it
    Useful for the parser.

*/


Litterale* LitteraleFactory::getRPNExampleOf(QString litt_str) const{

    QMap<unsigned int,QString>::iterator it_prio = priority_map_basic.begin();
    while(it_prio!=priority_map_basic.end() && !litt_str.contains(it_prio.value())){//On cherche le token dans la chaine de caractère par ordre de priorité
        it_prio++;
    }
    if(it_prio!=priority_map_basic.end()){
        Litterale* stored_example = litterale_map.find(it_prio.value()).value();
        return stored_example;
    }
    else{
        bool ok;
        litt_str.toInt(&ok); //On tente de convertir en entier
        if(ok) return litterale_map.find("Entier").value();

        if(Atome::isValidAtomeName(litt_str)){
            return litterale_map.find("Atome").value();
        }
    }
    return nullptr;
}

Litterale* LitteraleFactory::getInfixExampleOf(QString litt_str) const{

    QMap<unsigned int,QString>::iterator it_prio = priority_map_infix.begin();
    while(it_prio!=priority_map_infix.end() && !litt_str.contains(it_prio.value())){//On cherche le token dans la chaine de caractère par ordre de priorité
        it_prio++;
    }
    if(it_prio!=priority_map_infix.end()){
        Litterale* stored_example = litterale_map.find(it_prio.value()).value();
        return stored_example;
    }
    else{
        bool ok;
        litt_str.toInt(&ok); //On tente de convertir en entier
        if(ok) return litterale_map.find("Entier").value();

        if(Atome::isValidAtomeName(litt_str)){
            return litterale_map.find("Atome").value();
        }
    }
    return nullptr;
}

Litterale* LitteraleFactory::creerRPNLitterale(QString litt_str){
       Litterale* l1 = getRPNExampleOf(litt_str);
       if(l1)
           return l1->getFromString(litt_str);
       return nullptr;

}

Litterale* LitteraleFactory::creerInfixLitterale(QString litt_str){
       Litterale* l1 = getInfixExampleOf(litt_str);
       if(l1)
           return l1->getFromString(litt_str);
       return nullptr;

}
