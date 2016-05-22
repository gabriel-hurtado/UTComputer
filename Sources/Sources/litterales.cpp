#include "litterales.h"
#include "utils.h"

/*Définition des méthodes de la classe Litterale*/


/*------------Définition des méthodes de la classe Réelle------------*/

    /*Simplification retourne une référence sur litterale numerique allouée dynaiquement*/
LitteraleNumerique& Reelle::Simplification(){
    LitteraleNumerique* ptr;
    if(mantisse.getValeur()==0)
         ptr = new Entier(p_entiere);
    else{ptr=this;}
    return *ptr;
}

const std::string Reelle::toString() const {
    std::stringstream s;
    if(p_entiere.getValeur()!=0)
        s<<p_entiere.toString();
    s<<".";
    if(mantisse.getValeur()!=0)
        s<<mantisse.toString();
    return s.str();
}




/*------------Définition des méthodes de la classe Rationnel------------*/


Rationnel::Rationnel(int n, int d){
    if (d == 0)
        throw LitteraleException("Le dénominateur ne peut être nul !");
    else {
        int pg = pgcd(n, d);
        n = n / pg;
        d = d / pg;
        numerateur = n;
        denominateur = d;
        }
    }

const std::string Rationnel::toString() const { std::stringstream st;
                                st << getNumerateur().getValeur() << "/" << getDenominator().getValeur();
                                return st.str();
                                }

LitteraleNumerique& Rationnel::Simplification(){
    LitteraleNumerique* ptr;
    if(denominateur.getValeur()==1)
        ptr= new Entier(numerateur.getValeur());
    else
        ptr=this;
    return *ptr;
}




/*------------Définition des méthodes de la classe Entier------------*/


/*------------Définition des méthodes de la classe Complexe------------*/
const std::string Complexe::toString() const{
    std::stringstream s;
    s<<p_reelle.toString();
    s<<'$';
    s<<p_imaginaire.toString();
    return s.str();
}



/*------------Définition des méthodes de la classe Atome------------*/
 bool Atome::isValidAtomeName(std::string s){
    std::string::iterator it=s.begin();
    //On vérifie que le premier caractère est une majuscule;
    if(s.begin()!=s.end() && *it<'Z' && *it>'A'){
        //On doit alors vérifier que tout les caractères ne sont que des lettres majuscules ou des chiffres
        while(it!=s.end()){
            if(('A'<=*it && *it<='Z') || ('0'<=*it && *it<='9'))
                continue;
            else
                return false;
        }
        return true;
    }
    //Si le premier caractère n'est pas une lettre majuscule, alors ce ne peut pas être un nom d'atome
    else
        return false;
}
