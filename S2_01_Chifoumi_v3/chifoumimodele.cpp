#include "chifoumimodele.h"

ChifoumiModele::ChifoumiModele(UnEtat e, QObject *parent)
    : QObject{parent},
      scoreJoueur(0),
      scoreMachine(0),
      coupJoueur(rien),
      coupMachine(rien),
      _etat(e)
{
}

/// Getters

ChifoumiModele::UnCoup ChifoumiModele::getCoupJoueur() {
    return coupJoueur;
}

ChifoumiModele::UnCoup ChifoumiModele::getCoupMachine() {
    return coupMachine;
}

unsigned int ChifoumiModele::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int ChifoumiModele::getScoreMachine() {
    return scoreMachine;
}

char ChifoumiModele::determinerGagnant()
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

ChifoumiModele::UnEtat ChifoumiModele::getEtat()
{
    return _etat;
}

///* Méthodes utilitaires du Modèle

int randMinMax(int min, int max)
{
    /* pré-condition : min<max ;
    Le nbre aléatoire est compris entre [min, max[ */
    return rand()%(max-min) + min;
}



ChifoumiModele::UnCoup ChifoumiModele::genererUnCoup()
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

void ChifoumiModele::setCoupJoueur(UnCoup p_coup) {
    coupJoueur=p_coup;
}

void ChifoumiModele::setCoupMachine(UnCoup p_coup) {
    coupMachine=p_coup;
}

void ChifoumiModele::setScoreJoueur(unsigned int p_score) {
    scoreJoueur=p_score;
}

void ChifoumiModele::setScoreMachine(unsigned int p_score) {
    scoreMachine=p_score;
}

void ChifoumiModele::setEtat(ChifoumiModele::UnEtat p_etat)
{
    _etat=p_etat;
}

void ChifoumiModele::genererCoupMachine()
{
    setCoupMachine(genererUnCoup());
}

void ChifoumiModele::majScores(char p_gagnant) {
    switch (p_gagnant)
    {
    case 'J':
        setScoreJoueur(getScoreJoueur()+1);
        break;
    case 'M':
        setScoreMachine(getScoreMachine()+1);
        break;
    default:
        break;
    }
}

void ChifoumiModele::initScores() {
    setScoreMachine(0);
    setScoreJoueur(0);
}

void ChifoumiModele::initCoups() {
    setCoupJoueur(rien);
    setCoupMachine(rien);
}
