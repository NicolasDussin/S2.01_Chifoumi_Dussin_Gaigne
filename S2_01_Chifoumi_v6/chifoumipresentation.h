#ifndef CHIFOUMIPRESENTATION_H
#define CHIFOUMIPRESENTATION_H

#include <QObject>
#include "chifoumimodele.h"
#include <QTimer>

class ChifoumiVue;


class ChifoumiPresentation : public QObject
{
    Q_OBJECT
public:
    explicit ChifoumiPresentation(ChifoumiModele *m, QObject *parent = nullptr);
public:
    ChifoumiModele* getModele();
    ChifoumiVue* getVue();
    void setModele(ChifoumiModele *m);
    void setVue(ChifoumiVue *v);

public slots :
    void nouvellePartie(); // démarre une nouvelle partie
    void jouerCoupPierre(); // le joueur joue la pierre
    void jouerCoupPapier(); // le joueur joue le papier
    void jouerCoupCiseau(); // le joueur joue le ciseau
    void APropos(); // demande a afficher la QMessageBox décrivant l'application
    void VerifierFinDePartieScore(char p_gagnant); // verifie si le score fixé est atteint et si c'est le cas demande a afficher la QMessageBox décrivant la fin de partie par score atteint
    void finDePartieTemps(); // demande a afficher la QMessageBox décrivant la fin de partie par temps écoulé
    void gererPause(); // s'occuper des élements liés à la pause
    void lancerTimer(); // lance le timer pour une durée de 1s
    void stopperTimer(); // arrete le timer
    void gererTimer(); // s'occuper des élements liés au timer
    void ouvrirParametres();//

private :
    void jouerTour(); // joue un tour complet

private:
    ChifoumiModele *_leModele;
    ChifoumiVue *_laVue;
    QTimer *timer;
};

#endif // CHIFOUMIPRESENTATION_H
