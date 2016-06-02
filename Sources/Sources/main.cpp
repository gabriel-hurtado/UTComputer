
#include "litteralefactory.h"
#include "operateurfactory.h"
#include "controleur.h"
#include "mainwindow.h"
#include "operateurslogiques.h"


int main(int argc,char* argv[]) {



    Entier* e = new Entier(3);
    Entier* e2 = new Entier(4);
    Pile::donnerInstance()<<*e;
    Pile::donnerInstance()<<*e2;

    LitteraleFactory::enregistrer(0,"[",new Programme(""));
    LitteraleFactory::enregistrer(1,"\"",new Expression(""));
    LitteraleFactory::enregistrerInfix(2,"$",new Complexe(*dynamic_cast<LitteraleNumerique*>(new Entier(1)),*dynamic_cast<LitteraleNumerique*>(new Entier(1))));
    LitteraleFactory::enregistrer(4,".",new Reelle(1,1));
    LitteraleFactory::enregistrerInfix(3,"/",new Rationnel(2,1));

    OperateurFactory::enregistrer("NEG",new numerique::OperateurNEG);
    OperateurFactory::enregistrer("+",new numerique::OperateurAddition);
    OperateurFactory::enregistrer("-",new numerique::OperateurSoustraction);
    OperateurFactory::enregistrer("/",new numerique::OperateurDivision);
    OperateurFactory::enregistrer("DIV",new numerique::OperateurDIV);
    OperateurFactory::enregistrer("*",new numerique::OperateurMultiplication);


    OperateurFactory::enregistrer("IM",new numerique::OperateurIM);
    OperateurFactory::enregistrer("RE",new numerique::OperateurRE);
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
