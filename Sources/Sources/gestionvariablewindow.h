#ifndef GESTIONVARIABLEWINDOW_H
#define GESTIONVARIABLEWINDOW_H

#include <QWidget>
#include <QStandardItemModel>

//Forward declarations
class VariablesManager;

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
    QString selectedIdentifierName;

public slots:
    void refreshVueVariable();
    void regenerateVueVariable();
    void modifierVariable(int,int);
    void saveIdentifierName(int,int);
private slots:
    void on_button_add_clicked();
};

#endif // GESTIONVARIABLEWINDOW_H
