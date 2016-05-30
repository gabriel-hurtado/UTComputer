#include "controleur.h"

Controleur* Controleur::instanceControleur=nullptr;

std::map<unsigned int,std::string> Controleur::litterale_priority_map = std::map<unsigned int,std::string>();

Controleur& Controleur::donnerInstance(){
    if(instanceControleur==nullptr)
        instanceControleur= new Controleur;
    return *instanceControleur;
}

void Controleur::libererInstance(){
    if(instanceControleur!=nullptr)
        delete instanceControleur;
}

void Controleur::enregistrer(std::string symbole,unsigned int priorite){
    if(litterale_priority_map.find(priorite)==litterale_priority_map.end()) //Si pas déja la clé
        litterale_priority_map[priorite]=symbole;
    else
        throw LitteraleException("Une litterale avec cette priorité la existe déjà");
}

Controleur::Controleur(){}
Controleur::~Controleur(){};




void Controleur::commande(std::string s){

    std::string word;

    while((word=firstWord(s))!=""){
        s= s.erase(0,(s.find(word)+word.length())); //Enlève le mot trouvé dans firstWord de s
        std::cout << word;
        /*
            L'objectif maintenant est de détecter le type de variable
        */
        std::map<unsigned int,std::string>::iterator it_litterale_priority_map = litterale_priority_map.begin();

        while(word.find(it_litterale_priority_map->second)==std::string::npos && (it_litterale_priority_map)!=litterale_priority_map.end()){
            it_litterale_priority_map++;
        }

        if((it_litterale_priority_map)!=litterale_priority_map.end())
            std::cout<< "Detected: "<< it_litterale_priority_map->second;

    }
}

std::string Controleur::firstWord(std::string s){
    if(s=="")
        return s;

    std::string::iterator it_debut = s.begin();
    //tant qu'il y a des espaces on les vire
    while(*(it_debut)==' '){
        it_debut++;
        continue;
    }
    //On arrive ici quand il n'y a plus d'espace à gauche

    std::string::iterator it_fin = it_debut;
    it_fin++;
    bool found=false;
    //Si c'est un programme il faut trouver la fin de celui ci
    if(*it_debut=='['){
        unsigned int nb_crochet=0;
        while(!(nb_crochet==0 && *it_fin==']')){
            if(it_fin==s.end())
                throw LitteraleException("Impossible de trouver la fin du Programme");
            if(*it_fin=='[')
                nb_crochet++;
            if(*it_fin==']')
                nb_crochet--;
            it_fin++;
        }
        it_fin++; //On avance de 1 car le suivant marquera la fin
        found=true;
    }
    //Si cest une Expression il faut trouver la fin de celle ci
    if(!found && *it_debut=='"'){
        while(*it_fin!='"'){
            if(it_fin==s.end())
                throw LitteraleException("Impossible de trouver la fin de l'Expression");
            it_fin++;
       }
       it_fin++; //On avance de 1 car le suivant marquera la fin
       found=true;
    }

    //Dans les autres cas il faut chercher le prochain espace ou la fin de la string
    if(!found){
       while(*it_fin != ' '&& it_fin != s.end()){
           it_fin++;
       }
   }
   //Maintenant notre premier mot est borné entre it_debut et it_fin
   std::string ret;

   for(;it_debut!=it_fin;it_debut++)
       ret+=*it_debut;
   return ret;

}

