/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe métier (= modèle) Chifoumi-v1
 **************************************************************/
#include "chifoumi.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MODèLE ---------------------------

Chifoumi::Chifoumi() :
scoreMachine(0),
scoreJoueur(0),
coupMachine(rien),
coupJoueur(rien)
{
    //ctor
    // partie modèle
}

Chifoumi::~Chifoumi()
{
    //dtor
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
    switch (determinerGagnant())
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
