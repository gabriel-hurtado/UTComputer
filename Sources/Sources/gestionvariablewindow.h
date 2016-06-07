#ifndef GESTIONVARIABLEWINDOW_H
#define GESTIONVARIABLEWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include "variable.h"
#include "mainwindow.h"

class VariablesManager;

namespace Ui {
class gestionvariableWindow;
}

class gestionvariableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit gestionvariableWindow(QWidget *parent = 0);
    ~gestionvariableWindow();

private:
    Ui::gestionvariableWindow *ui;
    VariablesManager * varMan;

public slots:
    void refreshVueVariable();
    void regenerateVueVariable();
    void modifierVariable(int,int);
};

#endif // GESTIONVARIABLEWINDOW_H
