#include "chifoumi.h"
#include "ui_chifoumi.h"
#include <cstdlib>
#include <ctime>

///* ---- PARTIE MODèLE ---------------------------

Chifoumi::Chifoumi(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Chifoumi),
      scoreJoueur(0),
      scoreMachine(0),
      coupJoueur(rien),
      coupMachine(rien)
{
    ui->setupUi(this);
    connect(ui->bPierre,SIGNAL(clicked()),this,SLOT(jouerCoupPierre()));
    connect(ui->bPapier,SIGNAL(clicked()),this,SLOT(jouerCoupPapier()));
    connect(ui->bCiseau,SIGNAL(clicked()),this,SLOT(jouerCoupCiseau()));
    connect(ui->bNouvellePartie,SIGNAL(clicked()),this,SLOT(nouvellePartie()));
    desactiverBoutons();
}

Chifoumi::~Chifoumi()
{
    delete ui;
}

/// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
    return coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';

    // il sera modifié dans l'un des cas suivants
    switch (coupJoueur)
    {
    case ciseau://Le joueur a choisi ciseau et va etre comparer avec le choix de l'ordinateur
        switch(coupMachine)
        {
        case papier:
            gagnantARetourner = 'J';
            break;
        case pierre:
            gagnantARetourner = 'M';
            break;
        default :break;
        }
        break;
    case pierre://Le joueur a choisi pierre et va etre comparer avec le choix de l'ordinateur

        switch(coupMachine)
        {
        case ciseau:
            gagnantARetourner = 'J';
            break;
        case papier:
            gagnantARetourner = 'M';
            break;
        default :break;
        }
        break;

    case papier ://Le joueur a choisi papier et va etre comparer avec le choix de l'ordinateur
        switch(coupMachine)
        {
        case pierre:
            gagnantARetourner = 'J';
            break;
        case ciseau:
            gagnantARetourner = 'M';
            break;
        default :break;
        }
        break;
    }
    return gagnantARetourner;
}

///* Méthodes utilitaires du Modèle

int randMinMax(int min, int max)
{
    /* pré-condition : min<max ;
    Le nbre aléatoire est compris entre [min, max[ */
    return rand()%(max-min) + min;
}



Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner

    switch (randMinMax(1,4))
    {
    case 1 :
        valeurGeneree=pierre;
        break;
    case 2 :
        valeurGeneree=papier;
        break;
    case 3 :
        valeurGeneree=ciseau;
        break;
    }

    return valeurGeneree;
}

/// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
    coupJoueur=p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
    coupMachine=p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
    scoreJoueur=p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    scoreMachine=p_score;
}

void Chifoumi::majScores(char p_gagnant) {
    switch (p_gagnant)
    {
    case 'J':
        setScoreJoueur(scoreJoueur+1);
        break;
    case 'M':
        setScoreMachine(scoreMachine+1);
        break;
    default:
        break;
    }
}

void Chifoumi::initScores() {
    setScoreMachine(0);
    setScoreJoueur(0);
}

void Chifoumi::initCoups() {
    setCoupJoueur(rien);
    setCoupMachine(rien);
}

///* ---- PARTIE VUE ---------------------------

void Chifoumi::majInterfaceScores()
{
    ui->lScoreJoueur->setText(QString::number(getScoreJoueur()));
    ui->lScoreMachine->setText(QString::number(getScoreMachine()));
}

void Chifoumi::majInterfaceCoups()
{
    switch (getCoupJoueur())
    {
    case Chifoumi::pierre :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/pierre_115.png"));
        break;
    case Chifoumi::papier :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/papier_115.png"));
        break;
    case Chifoumi::ciseau :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/ciseau_115.png"));
        break;
    case Chifoumi::rien :
        ui->lCoupJoueur->setPixmap(QPixmap(":/ImagesChifoumi/images/rien_115.png"));
        break;
    }
    switch (getCoupMachine())
    {
    case Chifoumi::pierre :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/pierre_115.png"));
        break;
    case Chifoumi::papier :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/papier_115.png"));
        break;
    case Chifoumi::ciseau :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/ciseau_115.png"));
        break;
    case Chifoumi::rien :
        ui->lCoupMachine->setPixmap(QPixmap(":/ImagesChifoumi/images/rien_115.png"));
        break;
    }
}

void Chifoumi::activerBoutons()
{
    ui->bPierre->setEnabled(true);
    ui->bPapier->setEnabled(true);
    ui->bCiseau->setEnabled(true);
}

void Chifoumi::desactiverBoutons()
{
    ui->bPierre->setEnabled(false);
    ui->bPapier->setEnabled(false);
    ui->bCiseau->setEnabled(false);
}

void Chifoumi::changerCouleurJoueur(char couleur)
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

void Chifoumi::majInterfaceGlobale()
{
    majInterfaceScores();
    majInterfaceCoups();
}

///* ---- PARTIE PRéSENTATION  ---------------------------

void Chifoumi::nouvellePartie()
{
    initCoups();
    initScores();
    majInterfaceGlobale();
    activerBoutons();
    changerCouleurJoueur('B');
}

void Chifoumi::jouerCoupPierre()
{
    setCoupJoueur(pierre);
    jouerTour();
}

void Chifoumi::jouerCoupPapier()
{
    setCoupJoueur(papier);
    jouerTour();
}

void Chifoumi::jouerCoupCiseau()
{
    setCoupJoueur(ciseau);
    jouerTour();
}

void Chifoumi::jouerTour()
{
    changerCouleurJoueur('N');
    setCoupMachine(genererUnCoup());
    majScores(determinerGagnant());
    majInterfaceGlobale();
    changerCouleurJoueur('B');
}
