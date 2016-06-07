#include "litteraleexception.h"
#include "wordidentifier.h"

void WordIdentifier::WordPosition(QString& s, SelectedPosition& select){
    while(*select.it_fin != ' ' && select.it_fin != s.end()){
        select.it_fin++;
    }
}

bool WordIdentifier::WordGuesser(QString s){return true;}

void EncapsulatorIdentifier::WordPosition(QString& s,SelectedPosition& select){
    while(*select.it_fin!='"'){
        if(select.it_fin==s.end())
            throw LitteraleException("Impossible de trouver la fin de l'Expression");
        select.it_fin++;
    }
    select.it_fin++; //On avance de 1 car le suivant marquera la fin
}

bool EncapsulatorIdentifier::WordGuesser(QString s){
    if(*s.begin()==leftDelimiter)
        return true;
    return false;
}

void RecursiveEncapsulatorIdentifier::WordPosition(QString& s, SelectedPosition& select){

    unsigned int _nbLDelimitor = 0;
    while(!(_nbLDelimitor==0 && *select.it_fin==rightDelimiter)){
        if(select.it_fin==s.end())
            throw LitteraleException("Impossible de trouver la fin du Programme");
        if(*select.it_fin==leftDelimiter)
            _nbLDelimitor++;
        if(*select.it_fin==rightDelimiter)
            _nbLDelimitor--;
        select.it_fin++;
   }
        select.it_fin++; //On avance de 1 car le suivant marquera la fin

}

bool RecursiveEncapsulatorIdentifier::WordGuesser(QString s){
    if(*s.begin()==leftDelimiter)
        return true;
    return false;
}
