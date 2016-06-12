#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gestionvariablewindow.h"
#include "parameterwindow.h"
#include "litterales.h"
#include "litteraleexception.h"
#include "variable.h"
#include "pile.h"
#include "operateur.h"
#include "controleur.h"
#include "litteralefactory.h"
#include "gestionprogrammes.h"

bool MainWindow::keyboard=true;
bool MainWindow::sound=true;

MainWindow* MainWindow::InstanceMainWindow = nullptr;


/**
 * @brief  Constructeur de la MAINWINDOW
 *  Initialisation de la vuePile
 *   Initialisation du Player de Son
 *  Création des connections entres signaux et slots
 *   Restauration des paramètres, de la pile, des programmes et des variables
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pile(Pile::donnerInstance()),
    controleur(Controleur::donnerInstance()),
    lf(LitteraleFactory::donnerInstance()),
    soundBell(new QMediaPlayer),
    ui(new Ui::MainWindow),
    parameterIwindow(nullptr),
    variableIwindow(nullptr),
    programmeIwindow(nullptr)



{
    //Pour capter le clavier
    //this->installEventFilter();

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
    soundBell->setMedia(QUrl("qrc:/sound/bell.wav"));
    soundBell->setVolume(100);

    /*
        Création des connexions
    */
    connect(ui->commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    connect(&pile,SIGNAL(modificationEtat()),this,SLOT(refreshVuePile()));
    connect(this,SIGNAL(SendException(QString)),ui->message,SLOT(setText(QString)));
    //Pour afficher la fenetre de parametre
    connect(ui->actionEdition_des_param_tres,SIGNAL(triggered(bool)),this,SLOT(openParameterWindow()));
    //Pour afficher la fenetre de gestion des variables
    connect(ui->actionGestion_des_variables,SIGNAL(triggered(bool)),this,SLOT(openVariableWindow()));
    //Pour afficher la fenetre de gestion des programmes
    connect(ui->actionGestion_des_programmes,SIGNAL(triggered(bool)),this,SLOT(openProgramWindow()));
    //Pour regenerer la vue de la pile
    connect(&pile,SIGNAL(sendRegenerateVuePile()),this,SLOT(regenerateVuePile()));


   //Chargement des options
        QSettings settings("CosteHurtado", "UTComputer");

        int nb_items = settings.value("nb_item_affiche", 10).toInt();
        pile.setNbToAffiche(nb_items);

        //restaurer pile
        int sizePile = settings.value("nb_item_pile",0).toInt();


        bool keyboardRestore= settings.value("keyboard", true).toBool();
         bool soundRestore= settings.value("sound", true).toBool();

         if(!keyboardRestore){
             hideKeyboard(1);

         }

         if(!soundRestore){
             muteError(1);
         }

        settings.beginGroup( "Pile" );
        QStringList groupPile = settings.childKeys();
        int nb=0;

        foreach (const QString &pileNb, groupPile)
           {
            if(nb!=sizePile){
                QString pValue = settings.value(pileNb).toString();
                controleur.commande(pValue,"INFIX");
                nb++;
            }
            else
                break;
        }

        settings.endGroup();

        //restaurer programmes et variables
        settings.beginGroup( "Programme" );
        QStringList groupProgs = settings.childKeys();

        foreach (const QString &progName, groupProgs)
           {
              QString progInst = settings.value(progName).toString();
              Programme* p=new Programme(progInst);
              if(p)
               VariablesManager::enregistrer(progName,p);

           }

        settings.endGroup();
        settings.beginGroup( "Variable" );
        QStringList groupVars = settings.childKeys();

        foreach (const QString &varName, groupVars)
           {
              QString varValue = settings.value(varName).toString();
              Litterale* val=  lf.creerRPNLitterale(varValue);
              if(val)
               VariablesManager::enregistrer(varName,val);
              else{
                  val = lf.creerInfixLitterale(varValue);

                  if(val)
                      VariablesManager::enregistrer(varName,val);
              }

           }
        settings.endGroup();


}

/**
 * @brief Destructeur de mainWindow
 * Ferme les fenêtres filles éventuellement ouvertes,
 * sauvegarde contexte, pile et paramètre
 */
MainWindow::~MainWindow()
{
    delete ui;
}
/*
    Méthodes
*/
   MainWindow* MainWindow::getInstanceMainWindow(){return InstanceMainWindow;}

   //Settings saver

void MainWindow::closeEvent(QCloseEvent *event)
{
    //sauvegarde du contexte
    QSettings settings("CosteHurtado", "UTComputer");
    settings.clear();

    settings.setValue("nb_item_affiche", pile.getNbToAffiche());

     settings.setValue("keyboard", keyboard );
     settings.setValue("sound", sound);
    QMap<QString, Litterale*>::const_iterator begin;
    QMap<QString, Litterale*>::const_iterator end=VariablesManager::getVariablesEnd();
    for(begin=VariablesManager::getVariablesBegin();begin!=end;begin++){
        const QString name=begin.key();
        Programme* p =estdeType<Programme>(begin.value());
        if(p){
            settings.setValue("Programme/"+name, p->getProgramme());
        }
        else{
            settings.setValue("Variable/"+name, begin.value()->toString());
        }
    }
    Pile::iterator beginP;
    int nb=0;
    for(beginP=pile.begin();beginP!=pile.end();){
        settings.setValue("Pile/"+QString::number(nb), (*beginP).toString());
        ++beginP;
        ++nb;
    }
    settings.setValue("nb_item_pile",QString::number(nb));

    //Fermer les autres fenetres
    if(parameterIwindow){
        parameterIwindow->close();
    }
    if(variableIwindow)
        variableIwindow->close();

    if(programmeIwindow)
        programmeIwindow->close();

    event->accept();


}


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
    //pile.voirPile();

    //std::cout<<std::endl;
    //GerantPile::donnerInstance().seeUNDOList();
}

void MainWindow::getNextCommande(QString _fromButton,QString litterale_mode){
    QString _fromCommand = ui->commande->text();
    ui->commande->clear();
    QString& sent(_fromCommand);
    sent+=_fromButton;
    try{
        if(!controleur.commande(sent,litterale_mode)){
            throw LitteraleException("Le mot "+ controleur.firstWord(sent)+" n'as pas été reconnu","Inconnu");
        }

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
    if(sent!=""){
        ui->commande->setText(Controleur::SpaceCleaner(sent));
    }

}

void MainWindow::openVariableWindow(){
   if(!variableIwindow){
    variableIwindow = new gestionvariableWindow;
    variableIwindow->show();
   }
}

void MainWindow::closeVariableWindow(){
   if(variableIwindow){
    variableIwindow->close();
    delete variableIwindow;
    variableIwindow = nullptr;
   }
}

void MainWindow::openParameterWindow(){
   if(!parameterIwindow){
    parameterIwindow = new ParameterWindow();
    parameterIwindow->show();
   }

}

void MainWindow::closeParameterWindow(){
   if(parameterIwindow){
    parameterIwindow->close();
    delete parameterIwindow;
    parameterIwindow = nullptr;
   }
}

void MainWindow::openProgramWindow(){
   if(!programmeIwindow){
    programmeIwindow = new gestionprogrammes();
    programmeIwindow->show();
   }

}

void MainWindow::closeProgramWindow(){
   if(programmeIwindow){
    programmeIwindow->close();
    delete programmeIwindow;
    programmeIwindow = nullptr;
   }
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
    if(i){

        ui->clavierCliquable->setEnabled(false);
        keyboard=false;
    }
    else
    {
        ui->clavierCliquable->setEnabled(true);
        keyboard=true;
       }
}

void MainWindow::muteError(int i){
    if(i){
        soundBell->setMuted(true);
        sound=false;}
    else{
        soundBell->setMuted(false);
        sound=true;}
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
    getNextCommande(" /");
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

void MainWindow::on_button_egal_clicked()
{
    getNextCommande(" +");
}

void MainWindow::on_button_diff_clicked()
{
    getNextCommande(" !=");
}

void MainWindow::on_button_infegal_clicked()
{
    getNextCommande(" <=");
}

void MainWindow::on_button_supegal_clicked()
{
    getNextCommande(" >=");
}

void MainWindow::on_button_inf_clicked()
{
    getNextCommande(" <");
}

void MainWindow::on_button_sup_clicked()
{
    getNextCommande(" >");
}

void MainWindow::on_button_suppr_clicked()
{
   QString tmp = ui->commande->text();
   tmp.chop(1);
   ui->commande->setText(tmp);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Plus)
        on_button_plus_clicked();
}
