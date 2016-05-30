#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pile(Pile::donnerInstance())
{
    ui->setupUi(this);
    setWindowTitle("UTComputer");
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
    int k = ui->vuePile->rowCount();
    int l = ui->vuePile->columnCount();
    refreshVuePile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshVuePile(){
    //Rafraichir l'état de la pile
    int k = ui->vuePile->rowCount();
    for(unsigned int i=pile.getNbToAffiche()-1;i>0;i--)
        ui->vuePile->item(i,0)->setText("");
    unsigned int nb = 0;

    for(Pile::iterator it=pile.begin();it!=pile.end();++it,++nb)
        ui->vuePile->item(pile.getNbToAffiche()-nb-1,0)->setText(QString((*it).toString().c_str()));
}
