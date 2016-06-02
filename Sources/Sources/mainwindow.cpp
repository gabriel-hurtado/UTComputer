#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pile(Pile::donnerInstance()),
    controleur(Controleur::donnerInstance()),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setWindowTitle("UTComputer");
    //Pour rendre la page des messages plus swag
    ui->message->setStyleSheet("background: black; color: red");
    ui->message->setReadOnly(true);

    //Pour rendre plus swag la vue de la pile
    ui->vuePile->horizontalHeader()->setVisible(false);
    ui->vuePile->horizontalHeader()->setStretchLastSection(true);
    ui->vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Pour initialiser la pile
    ui->vuePile->setRowCount(pile.getNbToAffiche());//initialise le nombre de ligne de la vue
    ui->vuePile->setColumnCount(1);// Idem avec les colonnes

    QStringList liste;
    for(unsigned int i=1; pile.getNbToAffiche()>=i; i++){
        QString str = QString::number(i);
        str+=" :";
        liste<<str;
    }
    ui->vuePile->setVerticalHeaderLabels(liste);

    //Allocation des éléments du QtableWIdget
    for(unsigned int i=0;pile.getNbToAffiche()>i;i++)
        ui->vuePile->setItem(i,0,new QTableWidgetItem(""));

    connect(ui->commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    connect(&pile,SIGNAL(modificationEtat()),this,SLOT(refreshVuePile()));
    connect(this,SIGNAL(SendException(QString)),ui->message,SLOT(setText(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshVuePile(){
    //Rafraichir l'état de la pile

    for(unsigned int i=0; i<pile.getNbToAffiche();i++)
        ui->vuePile->item(i,0)->setText("");
    unsigned int nb = 0;

    for(Pile::iterator it=pile.begin();it!=pile.end() && nb<pile.getNbToAffiche();++it,++nb)
        ui->vuePile->item(nb,0)->setText((*it).toString());
    pile.voirPile();
    std::cout<<std::endl;
}

void MainWindow::getNextCommande(){
    //pile->setMessage("");
    QString g = ui->commande->text();
    try{
        controleur.commande(g);
        ui->commande->clear();
    }
    catch(LitteraleException& e){
        SendException("Litterale :"+e.getInfo());
    }
    catch(OperateurException& e){
        SendException("Operateur :"+e.getInfo());
    }
    catch(PileException & e){
        SendException("Pile :"+e.getInfo());
    }

    catch(VariableException & e){
        SendException("Variable :"+e.getInfo());
    }

}
