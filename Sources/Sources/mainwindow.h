#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include <QLabel>
#include <QSound>
#include <QMediaPlayer>
#include "pile.h"
#include "controleur.h"
#include "operateur.h"
#include "variable.h"
#include "parameterwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Pile& pile;
    Controleur& controleur;
    static MainWindow* InstanceMainWindow;
    QMediaPlayer* soundBell;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static const MainWindow* getInstanceMainWindow();
public slots:

    /*
        Rafraichie la vue de la pile dans le GUI quand celle-ci est modifiée
    */
    void refreshVuePile();

    /*
        Informe du traitement de la commande contenue dans le QLineEdit commande.
        En supplément de la commande, on peut rajouter q (utile pour les boutons)
    */
    void getNextCommande(QString q="");
    /*
        Pour ouvrir la fenetre de parametre
    */
    void openParameterWindow();
    /*
        Pour fermer la fenetre de parametre
    */
    void closeParameterWindow();
    /*
        Pour regenerer la vue de la Pile
        Quand le nombre d'éléménts visibles est modifié
    */
    void regenerateVuePile();
    /*
        Pour afficher/chacher le clavier
    */
    void hideKeyboard(int);
    /*
        Pour couper le son de la musique
    */
    void muteError(int);
signals:
    /*
        pour envoyer des messages d'exception à la QLineEdit message du GUI.
    */
    void SendException(QString s);

private slots:
    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_0_clicked();

    void on_button_plus_clicked();

    void on_button_moins_clicked();

    void on_button_fois_clicked();

    void on_button_diviser_clicked();

    void on_button_space_clicked();

    void on_button_num_clicked();

    void on_button_clear_clicked();

    void on_button_den_clicked();

    void on_button_re_clicked();

    void on_button_im_clicked();

    void on_button_dollar_clicked();

    void on_button_undo_clicked();

    void on_button_redo_clicked();

    void on_button_dup_clicked();

    void on_button_drop_clicked();

    void on_button_swap_clicked();

    void on_button_lastop_clicked();

    void on_button_sin_clicked();

    void on_button_cos_clicked();

    void on_button_tan_clicked();

    void on_button_div_clicked();

    void on_button_lastargs_clicked();

    void on_button_neg_clicked();

private:
    Ui::MainWindow *ui;
    ParameterWindow* parameterIwindow; //I stand for instansciated


};

#endif // MAINWINDOW_H
