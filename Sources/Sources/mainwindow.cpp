#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pile(Pile::donnerInstance()),
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

    //Définition des objets


    //Pour initialiser la pile

    ui->vuePile->setRowCount(pile.getNbToAffiche());//initialise le nombre de ligne de la vue
    ui->vuePile->setColumnCount(1);// Idem avec les colonnes

    QStringList liste;
    for(unsigned int i= pile.getNbToAffiche(); i>0; i--){
        QString str = QString::number(i);
        str+=" :";
        liste<<str;
    }
    ui->vuePile->setVerticalHeaderLabels(liste);

    //Allocation des éléments du QtableWIdget
    for(unsigned int i=pile.getNbToAffiche()-1;i>0;i--)
        ui->vuePile->setItem(i,0,new QTableWidgetItem(""));
    refreshVuePile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshVuePile(){
    //Rafraichir l'état de la pile
    for(unsigned int i=pile.getNbToAffiche()-1;i>0;i--)
        ui->vuePile->item(i,0)->setText("");
    unsigned int nb = 0;

    for(Pile::iterator it=pile.begin();it!=pile.end();++it,++nb)
        ui->vuePile->item(pile.getNbToAffiche()-nb-1,0)->setText((*it).toString());
}
