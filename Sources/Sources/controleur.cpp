#include "controleur.h"

Controleur* Controleur::instanceControleur=nullptr;


Controleur& Controleur::donnerInstance(){
    if(instanceControleur==nullptr)
        instanceControleur= new Controleur;
    return *instanceControleur;
}

void Controleur::libererInstance(){
    if(instanceControleur!=nullptr)
        delete instanceControleur;
}


Controleur::Controleur(){}
Controleur::~Controleur(){}




void Controleur::commande(QString s){
    QString word;
    LitteraleException* EXCEPTION_LIT;
    while((word=firstWord(s))!=""){
        s=s.remove(0,(s.indexOf(word)+word.length()));
        Litterale* l = LitteraleFactory::donnerInstance().creer(word);
        if(l){Pile::donnerInstance()<<*l;}
        Operateur* op = OperateurFactory::donnerInstance().creer(word);
        if(op){op->operation();}
        if(!op && !l){throw LitteraleException("Le mot "+word+" n'as pas été reconnu");}
   }
}

QString Controleur::firstWord(QString s){
    if(s=="")
        return s;

    QString::iterator it_debut = s.begin();
    //tant qu'il y a des espaces on les vire
    while(*(it_debut)==' '){
        it_debut++;
        continue;
    }
    //On arrive ici quand il n'y a plus d'espace à gauche

    QString::iterator it_fin = it_debut;
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
   QString ret;

   for(;it_debut!=it_fin;it_debut++)
       ret+=*it_debut;
   return ret;

}

