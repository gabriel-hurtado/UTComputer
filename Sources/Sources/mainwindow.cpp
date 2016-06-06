#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow* MainWindow::InstanceMainWindow = nullptr;
/*
    Constructeur de la MAINWINDOW
        Initialisation de la vuePile
        Initialisation du Player de Son
        Création des connections entres signaux et slots

*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pile(Pile::donnerInstance()),
    controleur(Controleur::donnerInstance()),
    ui(new Ui::MainWindow),
    soundBell(new QMediaPlayer)

{
    //On initialise la fenetre dans une ref static pour la connaitre dans les fenetres filles;
    InstanceMainWindow=this;

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

    //Allocation des éléments du QtableWIdget
    for(unsigned int i=0;pile.getNbToAffiche()>i;i++)
        ui->vuePile->setItem(i,0,new QTableWidgetItem(""));

    /*
        On initialise le son
    */
    soundBell->setMedia(QUrl::fromLocalFile(QFileInfo("bell.wav").absoluteFilePath()));
    soundBell->setVolume(50);

    /*
        Création des connexions
    */
    connect(ui->commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    connect(&pile,SIGNAL(modificationEtat()),this,SLOT(refreshVuePile()));
    connect(this,SIGNAL(SendException(QString)),ui->message,SLOT(setText(QString)));
    //Pour afficher la fenetre de parametre
    connect(ui->actionEdition_des_param_tres,SIGNAL(triggered(bool)),this,SLOT(openParameterWindow()));
    //Pour regenerer la vue de la pile
    connect(&pile,SIGNAL(sendRegenerateVuePile()),this,SLOT(regenerateVuePile()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
    Méthodes
*/
   const MainWindow* MainWindow::getInstanceMainWindow(){return InstanceMainWindow;}







/*
    SLOTS
*/
void MainWindow::refreshVuePile(){
    //Rafraichir l'état de la pile

    for(unsigned int i=0; i<pile.getNbToAffiche();i++)
        ui->vuePile->item(i,0)->setText("");
    unsigned int nb = 0;

    for(Pile::iterator it=pile.begin();it!=pile.end() && nb<pile.getNbToAffiche();++it,++nb)
        ui->vuePile->item(nb,0)->setText((*it).toString());

    //FOR DEBUG
    pile.voirPile();

    std::cout<<std::endl;
    GerantPile::donnerInstance().seeUNDOList();
}

void MainWindow::getNextCommande(QString _fromButton){
    //pile->setMessage("");
    QString _fromCommand = ui->commande->text();
    try{
        QString& sent(_fromCommand);
        sent+=_fromButton;
        if(!controleur.commande(sent)){
            ui->commande->setText(Controleur::SpaceCleaner(sent));
            throw LitteraleException("Le mot "+ Controleur::donnerInstance().firstWord(sent)+" n'as pas été reconnu");
        }
        ui->commande->clear();
    }
    catch(LitteraleException& e){
        soundBell->play();
        SendException("Litterale :"+e.getInfo());
    }
    catch(OperateurException& e){
        soundBell->play();
        SendException("Operateur :"+e.getInfo());
    }
    catch(PileException & e){
        soundBell->play();
        SendException("Pile :"+e.getInfo());
    }
}

void MainWindow::openParameterWindow(){
    parameterIwindow = new ParameterWindow();
    QString s;
    parameterIwindow->show();
}

void MainWindow::closeParameterWindow(){
    parameterIwindow->close();
    delete parameterIwindow;
}

void MainWindow::regenerateVuePile(){
    for(int i=0;ui->vuePile->rowCount()>i;i++)
        delete ui->vuePile->item(i,0);


    ui->vuePile->setRowCount(pile.getNbToAffiche());
    for(unsigned int i=0;pile.getNbToAffiche()>i;i++)
        ui->vuePile->setItem(i,0,new QTableWidgetItem(""));

    refreshVuePile();
}

void MainWindow::hideKeyboard(int i){
    if(i)
        ui->clavierCliquable->setEnabled(false);
    else
        ui->clavierCliquable->setEnabled(true);
}

void MainWindow::muteError(int i){
    if(i)
        soundBell->setMuted(true);
    else
        soundBell->setMuted(false);
}



/*Linkage des boutons*/

void MainWindow::on_button_1_clicked()
{
    ui->commande->setText(ui->commande->text()+"1");
}

void MainWindow::on_button_2_clicked()
{
    ui->commande->setText(ui->commande->text()+"2");
}

void MainWindow::on_button_3_clicked()
{
    ui->commande->setText(ui->commande->text()+"3");
}

void MainWindow::on_button_4_clicked()
{
    ui->commande->setText(ui->commande->text()+"4");
}

void MainWindow::on_button_5_clicked()
{
    ui->commande->setText(ui->commande->text()+"5");
}

void MainWindow::on_button_6_clicked()
{
    ui->commande->setText(ui->commande->text()+"6");
}

void MainWindow::on_button_7_clicked()
{
    ui->commande->setText(ui->commande->text()+"7");
}

void MainWindow::on_button_8_clicked()
{
    ui->commande->setText(ui->commande->text()+"8");
}

void MainWindow::on_button_9_clicked()
{
    ui->commande->setText(ui->commande->text()+"9");
}

void MainWindow::on_button_0_clicked()
{
    ui->commande->setText(ui->commande->text()+"0");
}

void MainWindow::on_button_plus_clicked()
{
    getNextCommande(" +");
}

void MainWindow::on_button_moins_clicked()
{
    getNextCommande(" -");
}

void MainWindow::on_button_fois_clicked()
{
    getNextCommande(" *");
}


void MainWindow::on_button_diviser_clicked()
{
    getNextCommande(" -");
}

void MainWindow::on_button_space_clicked()
{
    ui->commande->setText(ui->commande->text()+" ");
}

void MainWindow::on_button_num_clicked()
{
    getNextCommande(" NUM");
}

void MainWindow::on_button_den_clicked()
{
    getNextCommande(" DEN");
}

void MainWindow::on_button_re_clicked()
{
    getNextCommande(" RE");
}

void MainWindow::on_button_im_clicked()
{
    getNextCommande(" IM");
}

void MainWindow::on_button_dollar_clicked()
{
    getNextCommande(" $");
}

void MainWindow::on_button_undo_clicked()
{
    getNextCommande(" UNDO");
}

void MainWindow::on_button_redo_clicked()
{
    getNextCommande(" REDO");
}


void MainWindow::on_button_clear_clicked()
{
    getNextCommande(" CLEAR");
}

void MainWindow::on_button_dup_clicked()
{
    getNextCommande(" DUP");
}

void MainWindow::on_button_drop_clicked()
{
    getNextCommande(" DROP");
}

void MainWindow::on_button_swap_clicked()
{
    getNextCommande(" SWAP");
}

void MainWindow::on_button_lastop_clicked()
{
    getNextCommande(" LASTOP");
}

void MainWindow::on_button_sin_clicked()
{
    getNextCommande(" SIN");
}

void MainWindow::on_button_cos_clicked()
{
    getNextCommande(" COS");
}

void MainWindow::on_button_tan_clicked()
{
    getNextCommande(" TAN");
}

void MainWindow::on_button_div_clicked()
{
    getNextCommande(" DIV");
}

void MainWindow::on_button_lastargs_clicked()
{
    getNextCommande(" LASTARGS");
}

void MainWindow::on_button_neg_clicked()
{
    getNextCommande(" NEG");
}
