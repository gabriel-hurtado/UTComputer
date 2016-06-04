
#include "litteralefactory.h"
#include "operateurfactory.h"
#include "controleur.h"
#include "mainwindow.h"
#include "operateurslogiques.h"
#include "variable.h"
#include "operateurspile.h"

int main(int argc,char* argv[]) {

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

    OperateurFactory::enregistrer("!=",new logique::OperateurDiff);
    OperateurFactory::enregistrer("LASTARGS",new op_pile::OperateurLASTARGS);
    OperateurFactory::enregistrer("DROP",new op_pile::OperateurDROP);
    OperateurFactory::enregistrer("UNDO",new op_pile::OperateurUNDO);
    OperateurFactory::enregistrer("REDO",new op_pile::OperateurREDO);
    QApplication app(argc, argv);

    MainWindow fenetre;
    fenetre.show();

    return app.exec();

    return 0;
}
