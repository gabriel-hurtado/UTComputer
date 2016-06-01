
#include "litteralefactory.h"
#include "operateurfactory.h"
#include "controleur.h"
#include "mainwindow.h"
#include "operateurslogiques.h"


int main(int argc,char* argv[]) {


    /*
    std::cout<<"\n";

    Entier e(3);
    Entier e2(4);
    Reelle r(7.3);
    Complexe c(e,r);
    OperateurDivision ad= OperateurDivision(&e,&e2);
    try{
    Litterale* l2= ad.traitementOperateur();
    l2->afficher();}
    catch(LitteraleException err){

    }

    //system("pause");
    */
    /*
        Tests pour la pile

    try{

    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<r;
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<r;
    p.voirPile();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<e;
    p.voirPile();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<f;
    p.voirPile();
    std::cout<<"On recharge l'ancienne pile"<<std::endl;
    p.UNDO();
    p.voirPile();
    std::cout<<"On recharge l'ancienne pile"<<std::endl;
    p.UNDO();
    p.voirPile();
    std::cout<<"On recharge la pile stockée 2"<<std::endl;
    p.REDO();
    p.voirPile();
    std::cout<<"On recharge la pile stockée 1 on revient donc à l'état courant de la pile"<<std::endl;
    p.REDO();
    p.voirPile();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<r;
    p.voirPile();
    /*std::cout<<"On essaye de REDO après insertion, mais cela est interdit car cela n'a pas de sens"<<std::endl;
    p.REDO();
        //pour récuperer un élément de la pile
    Litterale* k;

    p>>k;
    p.UNDO();
    p>>k;
    std::cout<<k->toString();
    }



    catch(LitteraleException& e){
        std::cout<<e.getMessage();
    }
    */

    /*
    Pile& p = Pile::donnerInstance();
    p<<e;
    p<<c;
    std::cout<<std::endl;

    Controleur::enregistrer("$",1);
    Controleur::enregistrer(".",2);
    Controleur::enregistrer("[",0);

    Controleur::donnerInstance().firstWord("4 5 +");
    */
    //Construction de l'interface

    //try{
    Entier* e = new Entier(3);
    Entier* e2 = new Entier(4);
    Pile::donnerInstance()<<*e;
    Pile::donnerInstance()<<*e2;
    LitteraleFactory::enregistrer(2,".",new Reelle(1,1));

    OperateurFactory::enregistrer("$",new numerique::Operateur$);

    //}
    //catch(LitteraleException& e){
    //    std::cout<<e.getInfo().toStdString();
    //}

    QApplication app(argc, argv);

    MainWindow fenetre;
    fenetre.show();

    return app.exec();

    return 0;
}
