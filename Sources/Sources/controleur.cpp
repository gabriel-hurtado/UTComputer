#include "controleur.h"



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
    /*if(word=="EVAL"){
        Litterale* e;
        Pile::donnerInstance()>>e;
        e->traitement();
        return true;
    }
    */
    else{
        try{
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
        //Dans le cas ou la commande précédente
        catch(LitteraleException& e){
           // Pile::donnerInstance().UNDO();
            throw e;
        }
        catch(OperateurException& e){
           // Pile::donnerInstance().UNDO();
            throw e;
        }
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


    //On nettoie les espaces à gauche
    while(*(s.begin())==' '){
        s=s.remove(0,1);
        continue;
    }

    //On arrive ici quand il n'y a plus d'espace à gauche


    //Dans le cas ou c'est la fin on renvoie la vide
    if(s.begin()==s.end())
        return "";

    //Dans les autres cas il faut savoir ou on s'arrete
    //On initialise pour cela notre curseur
    SelectedPosition _cursor(s.begin(),s.begin());
    _cursor.it_fin++;

    //On initialise aussi un booleén quand on a trouvé
    bool found = false;

    //Il faut commencer dans l'ordre de priorité des opérateurs
    const QMap<unsigned int, QString>& prioMap = LitteraleFactory::getPriorityMap();
    QMap<unsigned int, QString>::const_iterator it_map = prioMap.begin();
    while(it_map!=prioMap.end() && !found){
        WordIdentifier* _currentWordIdentifier = interpretationMap.find(it_map.value()).value();
        if(_currentWordIdentifier->WordGuesser(s)){
            _currentWordIdentifier->WordPosition(s,_cursor);
            found=true;
        }
        it_map++;
    }

    //Maintenant notre premier mot est borné entre it_debut et it_fin
    QString ret("");

    for(;_cursor.it_debut!=_cursor.it_fin;_cursor.it_debut++)
       ret+=*_cursor.it_debut;
    return ret;

}



