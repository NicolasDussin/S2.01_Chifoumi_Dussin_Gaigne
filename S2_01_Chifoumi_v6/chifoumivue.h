#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "chifoumimodele.h"
#include <QMessageBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    ChifoumiVue(QWidget *parent = nullptr);
    ~ChifoumiVue();


public:
    void addConnexion(QObject *c);
    void delConnexion(QObject *c);

private :
    void majInterfaceScores(unsigned int p_scoreJoueur, unsigned int p_scoreMachine); //actualise les scores affichés dans l'ui
    void majInterfaceCoups(ChifoumiModele::UnCoup p_coupJoueur, ChifoumiModele::UnCoup p_scoreMachine); //actualise les icones affichées dans l'ui pour qu'elles correspondent à la figure choisie par le joueur durant ce tour

public :
    void majInterfaceGlobale(ChifoumiModele::UnEtat e,
                             ChifoumiModele::UnCoup p_coupJoueur,
                             ChifoumiModele::UnCoup p_coupMachine,
                             unsigned int p_scoreJoueur,
                             unsigned int p_scoreMachine); //actualise toute l'interface
    void activerBoutons(); //active les boutons pierre papier et ciseau
    void desactiverBoutons(); //desactive les boutons pierre papier et ciseau
    void changerCouleurJoueur(char couleur); //change la couleur du score et du nom du joueur en bleu si couleur = B et en noir si couleur = N
    void afficherMsBAPropos(); //créer et affiche la QMessageBox MsgBAPropos contenant les information sur l'application
    void afficherMsBFinDePartieScore(QString p_nomGagnant, unsigned int p_scoreGagnant,unsigned int p_temps); //créer et affiche la QMessageBox MsBFinDePartie contenant le message final
    void afficherMsBFinDePartieTemps(char resultat); //créer et affiche la QMessageBox MsBFinDePartie contenant le message final
    void majInterfaceScoreObjectif(unsigned int p_scoreObjectif); //actualise l'objectif de point dans l'ui
    void majBoutonPause(ChifoumiModele::UnEtat e); //actualise le bouton de pause
    void majTempsRestant(unsigned int p_tempsRestant); //actualise le temps restant dans l'ui
    void majnomJoueur(QString p_nom);

private:
    Ui::ChifoumiVue *ui;
};
#endif // CHIFOUMIVUE_H
