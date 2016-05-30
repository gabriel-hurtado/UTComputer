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
    QStringList liste;
    for(unsigned int i= 10; i>0; i--){
        QString str = QString::number(i);
        str+=" :";
        liste<<str;
    }
    ui->vuePile->setVerticalHeaderLabels(liste);

    //Allocation des éléments du QtableWIdget
    for(unsigned int i=10;i>0;i--)
        ui->vuePile->setItem(i,0,new QTableWidgetItem(""));

}

MainWindow::~MainWindow()
{
    delete ui;
}
