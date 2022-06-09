#include "chifoumipresentation.h"
#include "chifoumivue.h"
#include <QDebug>

ChifoumiPresentation::ChifoumiPresentation(ChifoumiModele *m, QObject *parent)
    : QObject{parent}, _leModele(m)
{
}

ChifoumiModele *ChifoumiPresentation::getModele()
{
    return _leModele;
}

ChifoumiVue *ChifoumiPresentation::getVue()
{
    return _laVue;
}

void ChifoumiPresentation::setModele(ChifoumiModele *m)
{
    _leModele = m;
}

void ChifoumiPresentation::setVue(ChifoumiVue *v)
{
    _laVue = v;
}

void ChifoumiPresentation::nouvellePartie()
{
    _leModele->initCoups();
    _leModele->initScores();
    _laVue->majInterfaceGlobale(_leModele->getEtat(),
                                _leModele->getCoupJoueur(),
                                _leModele->getCoupMachine(),
                                _leModele->getScoreJoueur(),
                                _leModele->getScoreMachine());
    _laVue->activerBoutons();
    _laVue->changerCouleurJoueur('B');
    _leModele->setEtat(ChifoumiModele::enCours);
}

void ChifoumiPresentation::jouerCoupPierre()
{
    _leModele->setCoupJoueur(ChifoumiModele::pierre);
    jouerTour();
}

void ChifoumiPresentation::jouerCoupPapier()
{
    _leModele->setCoupJoueur(ChifoumiModele::papier);
    jouerTour();
}

void ChifoumiPresentation::jouerCoupCiseau()
{
    _leModele->setCoupJoueur(ChifoumiModele::ciseau);
    jouerTour();
}

void ChifoumiPresentation::APropos()
{
    _laVue->afficherMsBAPropos();
}

void ChifoumiPresentation::jouerTour()
{
    _laVue->changerCouleurJoueur('N');
    _leModele->genererCoupMachine();
    _leModele->majScores(_leModele->determinerGagnant());
    _laVue->majInterfaceGlobale(_leModele->getEtat(),
                                _leModele->getCoupJoueur(),
                                _leModele->getCoupMachine(),
                                _leModele->getScoreJoueur(),
                                _leModele->getScoreMachine());
    _laVue->changerCouleurJoueur('B');
}
