#include "chifoumipresentation.h"
#include "chifoumivue.h"
#include "parametres.h"

#include <QDebug>

ChifoumiPresentation::ChifoumiPresentation(ChifoumiModele *m, QObject *parent)
    : QObject{parent},
      _leModele(m),
      timer(new QTimer(this))
{
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(gererTimer()));
    _leModele->setScoreObjectif();
    _leModele->setDureePartie();
    _leModele->setNomJoueur();
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
    _leModele->setTempsRestant(_leModele->getDureePartie());
    _laVue->majnomJoueur(_leModele->getNomJoueur());
    _laVue->majTempsRestant(_leModele->getDureePartie());
    _laVue->majInterfaceScoreObjectif(_leModele->getScoreObjectif());
    _laVue->changerCouleurJoueur('B');
    _leModele->setEtat(ChifoumiModele::enCours);
    lancerTimer();
    _laVue->majInterfaceGlobale(_leModele->getEtat(),
                                _leModele->getCoupJoueur(),
                                _leModele->getCoupMachine(),
                                _leModele->getScoreJoueur(),
                                _leModele->getScoreMachine());
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

void ChifoumiPresentation::VerifierFinDePartieScore(char p_gagnant)
{
    unsigned int scoreGagnant = _leModele->getScoreObjectif();
    if (p_gagnant=='J')
    {
        _leModele->setEtat(ChifoumiModele::init);
        _laVue->afficherMsBFinDePartieScore("Vous",scoreGagnant,_leModele->getDureePartie() - _leModele->getTempsRestant());
    }

    if (p_gagnant=='M')
    {
        _leModele->setEtat(ChifoumiModele::init);
        _laVue->afficherMsBFinDePartieScore("Machine",scoreGagnant,_leModele->getDureePartie() - _leModele->getTempsRestant());
    }
    _laVue->majInterfaceGlobale(_leModele->getEtat(),
                                _leModele->getCoupJoueur(),
                                _leModele->getCoupMachine(),
                                _leModele->getScoreJoueur(),
                                _leModele->getScoreMachine());
}

void ChifoumiPresentation::finDePartieTemps()
{
    _leModele->setEtat(ChifoumiModele::init);
    _laVue->afficherMsBFinDePartieTemps(_leModele->determinerMeneur());
    _laVue->majInterfaceGlobale(_leModele->getEtat(),
                                _leModele->getCoupJoueur(),
                                _leModele->getCoupMachine(),
                                _leModele->getScoreJoueur(),
                                _leModele->getScoreMachine());

}

void ChifoumiPresentation::gererPause()
{
    if (_leModele->getEtat()==ChifoumiModele::enCours)
    {
        _leModele->setEtat(ChifoumiModele::enPause);
    }
    else if (_leModele->getEtat()==ChifoumiModele::enPause)
    {
        _leModele->setEtat(ChifoumiModele::enCours);
    }
    _laVue->majInterfaceGlobale(_leModele->getEtat(),
                                _leModele->getCoupJoueur(),
                                _leModele->getCoupMachine(),
                                _leModele->getScoreJoueur(),
                                _leModele->getScoreMachine());
}

void ChifoumiPresentation::lancerTimer()
{
    timer->start(1000);
}

void ChifoumiPresentation::stopperTimer()
{
    timer->stop();
}

void ChifoumiPresentation::gererTimer()
{
    lancerTimer();
    if (_leModele->getEtat()==ChifoumiModele::enCours)
    { 
        _leModele->setTempsRestant(_leModele->getTempsRestant()-1);
        _laVue->majTempsRestant(_leModele->getTempsRestant());
    }
    if (_leModele->getTempsRestant()==0)
    {
        stopperTimer();
        finDePartieTemps();
    }
}

void ChifoumiPresentation::ouvrirParametres()
{
    Parametres *mesParams= new Parametres;
    int retourExec = mesParams->exec();
    if (retourExec==Parametres::Accepted)
    {
        _leModele->setNomJoueur(mesParams->getLineEditNomJoueur());
        _leModele->setScoreObjectif(mesParams->getLineEditObjectifScore());
        _leModele->setDureePartie(mesParams->getLineEditDureePartie());
    }
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
    VerifierFinDePartieScore(_leModele->determinerObjectifAtteint());
}
