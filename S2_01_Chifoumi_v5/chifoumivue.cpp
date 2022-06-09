#include "chifoumivue.h"
#include "ui_chifoumivue.h"

ChifoumiVue::ChifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);
}

ChifoumiVue::~ChifoumiVue()
{
    delete ui;
}

void ChifoumiVue::addConnexion(QObject *c)
{
    //pour se connecter avec la presentation
    QObject::connect(ui->bPierre,SIGNAL(clicked()),c,SLOT(jouerCoupPierre()));
    QObject::connect(ui->bPapier,SIGNAL(clicked()),c,SLOT(jouerCoupPapier()));
    QObject::connect(ui->bCiseau,SIGNAL(clicked()),c,SLOT(jouerCoupCiseau()));
    QObject::connect(ui->bNouvellePartie,SIGNAL(clicked()),c,SLOT(nouvellePartie()));
    QObject::connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));
    QObject::connect(ui->actionA_propos_de_l_application,SIGNAL(triggered()),c,SLOT(APropos()));
    QObject::connect(ui->bPause,SIGNAL(clicked()),c,SLOT(gererPause()));

}

void ChifoumiVue::delConnexion(QObject *c)
{
    //pour se déconnecter de c
    QObject::disconnect(ui->bPierre,SIGNAL(clicked()),c,SLOT(jouerCoupPierre()));
    QObject::disconnect(ui->bPapier,SIGNAL(clicked()),c,SLOT(jouerCoupPapier()));
    QObject::disconnect(ui->bCiseau,SIGNAL(clicked()),c,SLOT(jouerCoupCiseau()));
    QObject::disconnect(ui->bNouvellePartie,SIGNAL(clicked()),c,SLOT(nouvellePartie()));
    QObject::disconnect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));
    QObject::disconnect(ui->actionA_propos_de_l_application,SIGNAL(triggered()),c,SLOT(APropos()));
    QObject::disconnect(ui->bPause,SIGNAL(clicked()),c,SLOT(gererPause()));
}

void ChifoumiVue::majInterfaceScores(unsigned int p_scoreJoueur, unsigned int p_scoreMachine)
{
    ui->lScoreJoueur->setText(QString::number(p_scoreJoueur));
    ui->lScoreMachine->setText(QString::number(p_scoreMachine));
}

void ChifoumiVue::majInterfaceCoups(ChifoumiModele::UnCoup p_coupJoueur, ChifoumiModele::UnCoup p_coupMachine)
{
    switch (p_coupJoueur)
    {
    case ChifoumiModele::pierre :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/pierre_115.png"));
        break;
    case ChifoumiModele::papier :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/papier_115.png"));
        break;
    case ChifoumiModele::ciseau :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/ciseau_115.png"));
        break;
    case ChifoumiModele::rien :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/rien_115.png"));
        break;
    }
    switch (p_coupMachine)
    {
    case ChifoumiModele::pierre :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/pierre_115.png"));
        break;
    case ChifoumiModele::papier :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/papier_115.png"));
        break;
    case ChifoumiModele::ciseau :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/ciseau_115.png"));
        break;
    case ChifoumiModele::rien :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/rien_115.png"));
        break;
    }
}

void ChifoumiVue::activerBoutons()
{
    ui->bPierre->setEnabled(true);
    ui->bPapier->setEnabled(true);
    ui->bCiseau->setEnabled(true);
}

void ChifoumiVue::desactiverBoutons()
{
    ui->bPierre->setEnabled(false);
    ui->bPapier->setEnabled(false);
    ui->bCiseau->setEnabled(false);
}

void ChifoumiVue::changerCouleurJoueur(char couleur)
{
    if (couleur == 'B')
    {
        ui->lNomJoueur->setStyleSheet("QLabel { color : blue; }");
        ui->lScoreJoueur->setStyleSheet("QLabel { color : blue; }");
    }
    else if (couleur == 'N')
    {
        ui->lNomJoueur->setStyleSheet("QLabel { color : black; }");
        ui->lScoreJoueur->setStyleSheet("QLabel { color : black; }");
    }
}

void ChifoumiVue::afficherMsBAPropos()
{
    QMessageBox *MsBAPropos=new QMessageBox;
    MsBAPropos->setWindowTitle("A propos de cette application");
    MsBAPropos->setText("S2.01 Chifoumi V5 par DUSSIN Nicolas et GAIGNE Lilian");
    MsBAPropos->setStandardButtons(QMessageBox::Ok);
    MsBAPropos->exec();
}

void ChifoumiVue::afficherMsBFinDePartieScore(QString p_nomGagnant, unsigned int p_scoreGagnant,unsigned int p_temps)
{
    QMessageBox *MsBFinDePartie=new QMessageBox;
    MsBFinDePartie->setWindowTitle("Fin de partie gagnant");
    MsBFinDePartie->setIcon(QMessageBox::Information);
    MsBFinDePartie->setText("Bravo " + p_nomGagnant + " ! Vous gagnez avec " + QString::number(p_scoreGagnant) + " points en " + QString::number(p_temps) + " secondes.");
    MsBFinDePartie->setStandardButtons(QMessageBox::Ok);
    MsBFinDePartie->exec();
}

void ChifoumiVue::afficherMsBFinDePartieTemps(char resultat)
{
    QMessageBox *MsBFinDePartie=new QMessageBox;
    if (resultat == 'E')
    {
        MsBFinDePartie->setWindowTitle("Fin de partie temps fini : egalite");
        MsBFinDePartie->setText("Helas chers joueurs, temps de jeu fini ! Vous terminez tous deux a egalite avec " + ui->lScoreJoueur->text() + " points.");
    }
    else if (resultat == 'J')
    {
        MsBFinDePartie->setWindowTitle("Fin de partie temps fini : 1 avantage");
        MsBFinDePartie->setText("Helas chers joueurs, temps de jeu fini ! " + ui->lNomJoueur->text() + " termine toutefois mieux avec " + ui->lScoreJoueur->text() + " points.");
    }
    else if (resultat == 'M')
    {
        MsBFinDePartie->setWindowTitle("Fin de partie temps fini : 1 avantage");
        MsBFinDePartie->setText("Helas chers joueurs, temps de jeu fini ! " + ui->lNomMachine->text() + " termine toutefois mieux avec " + ui->lScoreMachine->text() + " points.");
    }
    MsBFinDePartie->setIcon(QMessageBox::Information);
    MsBFinDePartie->setStandardButtons(QMessageBox::Ok);
    MsBFinDePartie->exec();
}

void ChifoumiVue::majInterfaceScoreObjectif(unsigned int p_scoreObjectif)
{
    ui->lScoreObjectif->setText(QString::number(p_scoreObjectif));
}

void ChifoumiVue::majBoutonPause(ChifoumiModele::UnEtat e)
{
    if (e==ChifoumiModele::enPause)
    {
        ui->bPause->setText("Reprise Jeu");
        ui->bPause->setEnabled(true);
    }
    else if (e==ChifoumiModele::enCours)
    {
        ui->bPause->setText("Pause");
        ui->bPause->setEnabled(true);
    }
    else if (e==ChifoumiModele::init)
    {
        ui->bPause->setText("Pause");
        ui->bPause->setEnabled(false);
    }
}

void ChifoumiVue::majTempsRestant(unsigned int p_tempsRestant)
{
    ui->lTempsRestant->setText("Temps restant (s) : " + QString::number(p_tempsRestant));
}

void ChifoumiVue::majInterfaceGlobale(ChifoumiModele::UnEtat e,
                                      ChifoumiModele::UnCoup p_coupJoueur,
                                      ChifoumiModele::UnCoup p_coupMachine,
                                      unsigned int p_scoreJoueur,
                                      unsigned int p_scoreMachine)
{
    switch (e) {
    case ChifoumiModele::init:
        desactiverBoutons();
        majInterfaceScores(p_scoreJoueur,p_scoreMachine);
        majInterfaceCoups(p_coupJoueur,p_coupMachine);
        break;

    case ChifoumiModele::enCours:
        activerBoutons();
        majInterfaceScores(p_scoreJoueur,p_scoreMachine);
        majInterfaceCoups(p_coupJoueur,p_coupMachine);
        break;

    case ChifoumiModele::enPause:
        desactiverBoutons();
        majInterfaceScores(p_scoreJoueur,p_scoreMachine);
        majInterfaceCoups(p_coupJoueur,p_coupMachine);
    }
    majBoutonPause(e);
}
