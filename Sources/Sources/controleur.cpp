#include "controleur.h"

void WordIdentifier::WordPosition(QString s, const SelectedPosition& Select){

}
void EncapsulatorIdentifier::WordPosition(QString s, const SelectedPosition& Select){

}
void RecursiveEncapsulatorIdentifier::WordPosition(QString s, const SelectedPosition& Select){

}




Controleur* Controleur::instanceControleur=nullptr;

//Map qui contient les symboles des opérateurs
QMap<QString,QString> Controleur::symbolMap = QMap<QString,QString>();
QMap<QString,WordIdentifier*> Controleur::interpretationMap = QMap<QString,WordIdentifier*>();


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




bool Controleur::commande(QString& s){
    // On extraie le mot que l'on veut
    QString word = firstWord(s);

    if(word==""){return true;} //On a bien terminé tous les mots
    else{

        //Il reste du bouleau chef !
        s=s.remove(0,(s.indexOf(word)+word.length())); // On enlève notre mot juste prélevé de la string
        Litterale* l = LitteraleFactory::donnerInstance().creerRPNLitterale(word);
        if(l){Pile::donnerInstance()<<*l;}
        Operateur* op = OperateurFactory::donnerInstance().creer(word);
        if(op){op->operation();}
        if(!op && !l){s=word;return false;}
        if(commande(s))//Si la commande suivante est valide on valide la notre
            return true;
        else            //Si la commande suivante n'est pas valide alors il faut nettoyer la notre aussi
            Pile::donnerInstance().UNDO();
        return false;
   }
}
void Controleur::enregistrerSymbole(QString ltok, QString rtok){
    QMap<QString,QString>::iterator it_map = symbolMap.find(ltok);
    if(it_map==symbolMap.end()){
        symbolMap[ltok]=rtok;
        interpretationMap[ltok]= new WordIdentifier;
    }
}


void Controleur::enregistrerSymbole(QString ltok, QString rtok, WordIdentifier* W){
    QMap<QString,QString>::iterator it_map = symbolMap.find(ltok);
    if(it_map==symbolMap.end()){
        symbolMap[ltok]=rtok;
        interpretationMap[ltok]=W;
    }
}


QString Controleur::firstWord(QString s){

    QString::iterator it_debut = s.begin();
    //tant qu'il y a des espaces on les vire
    while(*(it_debut)==' '){
        it_debut++;
        continue;
    }
    //On arrive ici quand il n'y a plus d'espace à gauche

    //Dans le cas ou c'est la fin on renvoie la vide
    if(it_debut==s.end())
        return "";

    //Dans les autres cas il faut savoir ou on s'arrete

    //On prépare pour celà un début et une fin à notre chaine à extraire.
    QString::iterator it_fin = it_debut;
    it_fin++;//La fin sera au minimum le prochain caractère (qui existe forcément)

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
       while(*it_fin != ' ' && it_fin != s.end()){
           it_fin++;
       }
   }
   //Maintenant notre premier mot est borné entre it_debut et it_fin
   QString ret("");

   for(;it_debut!=it_fin;it_debut++)
       ret+=*it_debut;
   return ret;

}



