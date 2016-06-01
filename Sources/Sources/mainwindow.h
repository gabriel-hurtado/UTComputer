#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include "pile.h"
#include "controleur.h"
#include "operateur.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Pile& pile;
    Controleur& controleur;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void refreshVuePile();
    void getNextCommande();
signals:
    void SendException(QString s);

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
