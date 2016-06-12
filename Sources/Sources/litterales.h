

#ifndef H_LITTERALE
#define H_LITTERALE
#include "operande.h" //Pour savoir ce que sont des opérandes pour l'héritage

//Forward declarations
class LitteraleFactory;




/*------------Classes "Litterales" abstraites------------*/

class Litterale : public Operande
{
public:
    Litterale() {}
    virtual ~Litterale() {}
    /**
     * @brief Permet d'afficher une littérale sur cout
    */
    std::ostream& afficher(std::ostream& f=std::cout){f<<toString().toStdString();return f;}

    /**
     * @return La chaine de caractère représentant la littérale
    */
    virtual const QString toString() const = 0;

    /**
     * @return Une copie de l'objet \n
     * Attention à bien désallouer la copie car elle a été allouée dynamiquement
    */
    virtual Litterale* getCopy() const = 0;

    /**
     * @brief Permet de créer une copie de l'objet, avec une nouvelle valeur inclue dans la string s
     * @param s Chaine de caractère de l'objet à créer avec ses valeurs (ex 3.8).
     * @return Retourne la de la litterale avec les nouvelles valeurs
    */
    virtual Litterale* getFromString(QString s) const = 0;

    /**
     * @brief Permet de lancer le traitement de la littérale (utile uniquement pour les programmes).
    */
    virtual Litterale* traitement() const;

private:

};


class LitteraleSimple : public Litterale
{
public:
    LitteraleSimple() {}
    virtual ~LitteraleSimple() {}
private:

};

class LitteraleComplexe : public LitteraleSimple
{
public:
    LitteraleComplexe() {}
    virtual ~LitteraleComplexe() {}

    /**
     * @brief Toute littérale complexe doit pouvoir être rendue négative \n
     * @return L'opposé de la littérale
    */
    virtual LitteraleComplexe* neg() const =0;


private:

};

class LitteraleNumerique : public LitteraleComplexe
{
public:
    LitteraleNumerique() {}
    virtual ~LitteraleNumerique() {}

    /**
     * @return Une copie de la littérale
    */
    virtual LitteraleNumerique* getNumericCopy() const =0;
    Litterale* getCopy() const {return getNumericCopy();}
    virtual double getValeur() const=0;
private:

};






/*------------Classe Litterale Entier------------*/

class Entier : public LitteraleNumerique {

    int valeur;
public:
    Entier(int v=0) :valeur(v) {}
    virtual ~Entier() {}
    /**
     * @return La valeur de la littérale sous forme d'un double
    */
    double getValeur() const { return (double)valeur; }
    const QString toString() const {return QString::number(valeur);}
    LitteraleComplexe* neg() const {Entier* res =getNumericCopy(); res->valeur=-res->valeur; return res;}
    Entier* getNumericCopy() const{return new Entier(*this);}
    Litterale* getFromString(QString) const;

};



/*------------Classe Litterale Reelle------------*/

class Reelle : public LitteraleNumerique{
    double value;
public:


    /*La partie entiere dit etre le second paramêtre pour avoir une valeur par défaut*/
    Reelle(double d):value(d){}

    Reelle(const Entier& p,const Entier& m);

    Reelle(int x,int y=0):Reelle( Entier(x), Entier(y)){}

    virtual ~Reelle(){}

    /**
     * @return Retourne la valeur de la partie avant le '.' sous forme d'un Entier
    */
    Entier getPartieEntiere() const{return Entier(floor(value));}

    /**
     * @return Retourne la partie après le '.' sous forme d'un Entier
    */
    Entier getMantisse()const {
        double res=value-floor(value);
                               if(res==0)
                                   return 0;
                           while(res-floor(res)!=0){
                               res=res*10;
                           }
                           return Entier((int)res);}

    /**
     * @return Retourne une copie de l'objet ou un Entier si la mantisse est nulle\n
     * Attention : La valeur retournée est un nouvel objet alloué dynamiquement
     */
    LitteraleNumerique& Simplification();
    double  getValeur()const {return value;}
    LitteraleComplexe* neg() const{Reelle* res=getNumericCopy(); res->value=-res->value;return res;}
    Reelle* getNumericCopy() const{return new Reelle(*this);}
    const QString toString() const;
    Litterale* getFromString(QString s) const;


};

/*------------Classe Litterale Rationnel------------*/

class Rationnel : public LitteraleNumerique
{
protected:
    Entier numerateur;
    Entier denominateur;
public:
    Rationnel(int n, int d=1);
    Rationnel(const Entier& n, const Entier& d) { Rationnel(n.getValeur(), d.getValeur()); }
    virtual ~Rationnel(){}

    /**
     * @return Retourne la partie avant le '/' sous forme d'un Entier
    */
    Entier getNumerateur() const { return numerateur; }

    /**
     * @return Retourne la partie après le '/' sous forme d'un Entier
    */
    Entier getDenominator() const { return denominateur; }

    LitteraleComplexe* neg() const{Rationnel* res=getNumericCopy(); res->numerateur.neg();return res;}
    Rationnel* getNumericCopy() const{return new Rationnel(*this);}
    const QString toString() const;

    /**
     * @brief Simplifie l'objet et en renvoie une copie
     * @return Retourne une copie de l'objet ou un Entier si le dénominateur est unitaire\n
     * Attention : La valeur retournée est un nouvel objet alloué dynamiquement.
     */
    LitteraleNumerique& Simplification();
    Reelle roundValue() const;
    double getValeur() const{return roundValue().getValeur();}
    Litterale* getFromString(QString s) const;

};

/*------------Classe Litterale Complexe------------*/

class Complexe : public LitteraleComplexe{
    LitteraleNumerique& p_reelle;
    LitteraleNumerique& p_imaginaire;
public:
    /*Le comportement par défaut du constructeur est suffisant car pas de pointeur*/
    Complexe(LitteraleNumerique& pR,LitteraleNumerique& pI):p_reelle(*pR.getNumericCopy()),p_imaginaire(*pI.getNumericCopy()){}
    virtual ~Complexe(){
        delete &p_reelle;
        delete &p_imaginaire;
    }

    Complexe(Complexe& e):p_reelle(*e.getPartieReelle()),p_imaginaire(*e.getPartieImaginaire()){}
    Complexe operator=(Complexe& e);

    /**
     * @return Retourne une copie de la partie réelle du complexe\n
     * Attention : La valeur retournée est un nouvel objet alloué dynamiquement.
     */
    LitteraleNumerique* getPartieReelle() const {return p_reelle.getNumericCopy();}

    /**
     * @return Retourne une copie de la partie imaginaire du complexe\n
     * Attention : La valeur retournée est un nouvel objet alloué dynamiquement.
     */
    LitteraleNumerique* getPartieImaginaire() const {return p_imaginaire.getNumericCopy();}

    LitteraleComplexe* neg() const{
        LitteraleNumerique* tmp = estdeType<LitteraleNumerique>(p_reelle.neg());
        LitteraleComplexe* res = new Complexe(*tmp,p_imaginaire);
        delete tmp;
        return res;
    }
    Complexe* getCopy() const {return new Complexe(p_reelle,p_imaginaire);}
    const QString toString() const;
    Litterale* getFromString(QString s) const;

    /**
     * @brief Simplifie l'objet et en renvoie une copie
     * @return Retourne une copie de l'objet ou une Littérale numérique si la partie imaginaire est nulle\n
     * Attention : La valeur retournée est un nouvel objet alloué dynamiquement.
     */
    LitteraleComplexe& Simplification();

};



/*------------Classe Litterale Atome------------*/
class Atome : public LitteraleSimple{
    QString nom;
public:
    Atome(QString n);
    virtual ~Atome(){}
    QString getNom() const {return nom;}
    const QString toString() const;
    Litterale* getCopy() const;

    /**
     * @brief Permet de vérifier que la string s est valide pour identifier un objet Atome
     * @param s Chaine de caractère contenant le nom candidat.
     * @return Retourne true si le nom est valide, false sinon
     */
    static bool isValidAtomeName(QString s);
    Litterale* getFromString(QString s) const{return new Atome(s);}
};

/*------------Classe Litterale Expression------------*/

class Expression : public Litterale{
    QString value;

public:
    /**
     * @brief Permet de savoir quel opération effectuer en priorité
     * @param s1 Chaine de caractère identifiant un opérateur
     * @param s2 Chaine de caractère identifiant un opérateur
     * @return Retourne \n
     *  -1 si s1 est prioritaire par rapport à s2\n
     *  0 si ils ont la même priorité\n
     *  1 si s2 est prioriatire par rapport à s1\n
    */
    int CompareOperators(QString s1,QString s2) const;

    /**
     * @return Renvoie vrai si s identifie un opérateur, faux sinon
    */
    bool isOperator(QString s) const;

    /**
     * @return Renvoie vrai si s identifie une variable, faux sinon
    */
    bool isVariable(QString s) const ;

    Expression(QString v):value(v){}
    virtual ~Expression(){}
    QString getExpression() const {return value;}
    const QString toString() const {return getExpression();}

    /**
     * @brief Traite l'expression
    * @details Transforme l'expression en une string postfixée avec les littérales infixes, qu'elle fait traiter directement par la mainWindow en appelant getNextCommand avec le paramêtre INFIX pour permettre le traitement des littérales infixes
     * @return Renvoie nullptr
    */
    Litterale* evaluer() const;
    Litterale* getCopy() const;
    Litterale* getFromString(QString s) const;
    const QString getExpressionNoBorders() const{

                                                    QString tmp = QString(value);
                                                    tmp=tmp.remove(0,1);
                                                    tmp=tmp.remove(tmp.length()-1,tmp.length());
                                                    return tmp;
                                                }
};


/*------------Classe Litterale Programme------------*/


class Programme : public Litterale{
    QString valeur;

public:
    Programme(QString p):valeur(p){}
    virtual ~Programme(){}
    QString getProgramme() const {return valeur;}
    const QString toString() const {return getProgramme();}
    Litterale* getCopy() const;
    Litterale* getFromString(QString s) const{
        if(s[0]=='[')
            return new Programme(s);
        else
            return nullptr;
    }
    /**
     * @brief Traite le programme directement en l'envoyant au controleur.
     * @return nullptr
    */
    Litterale* traitement() const override;
};

#endif
