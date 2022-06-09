#ifndef CHIFOUMIPRESENTATION_H
#define CHIFOUMIPRESENTATION_H

#include <QObject>
#include "chifoumimodele.h"

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
    void FinDePartie(char p_gagnant); // demande a afficher la QMessageBox décrivant la fin de partie

private :
    void jouerTour(); // joue un tour complet

private:
    ChifoumiModele *_leModele;
    ChifoumiVue *_laVue;

};

#endif // CHIFOUMIPRESENTATION_H
