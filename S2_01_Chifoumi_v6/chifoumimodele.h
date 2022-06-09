#ifndef CHIFOUMIMODELE_H
#define CHIFOUMIMODELE_H

#include <QObject>

class ChifoumiModele : public QObject
{
    Q_OBJECT

public:
    enum UnCoup {pierre, papier, ciseau, rien};
    enum UnEtat {init, enCours, enPause};

    ///* Méthodes du Modèle
public:
    explicit ChifoumiModele(UnEtat e=init, QObject *parent = nullptr);
    // Getters
    UnCoup getCoupJoueur();
    /* retourne le dernier coup joué par le joueur */
    UnCoup getCoupMachine();
    /* retourne le dernier coup joué par le joueur */
    unsigned int getScoreJoueur();
    /* retourne le score du joueur */
    unsigned int getScoreMachine();
    /* retourne le score de la machine */
    char determinerGagnant();
    /* détermine le gagnant 'J' pour joueur, 'M' pour machine, 'N' pour match nul
        en fonction du dernier coup joué par chacun d'eux */
    char determinerMeneur();
    /* détermine le gagnant 'J' pour joueur, 'M' pour machine, 'E' egalite
        en fonction de qui possede le meilleur score */
    UnEtat getEtat();
    /* retourne l'etat actuel du jeu */
    unsigned int getScoreObjectif();
    /* retourne le score à atteindre pour gagner */
    char determinerObjectifAtteint();
    /* détermine si un participant à atteint le score pour gagner :
       'J' pour joueur, 'M' pour machine, 'N' pour non atteint */
    unsigned int getDureePartie();
    /* retourne la duree max de la partie */
    unsigned int getTempsRestant();
    /* retourne le temps restant avant la fin de la partie */
    QString getNomJoueur();
    /* retourne le nom du joueur */

    ///* Méthodes utilitaires du Modèle
private :
    UnCoup genererUnCoup();
    /* retourne une valeur aléatoire = pierre, papier ou ciseau.
     Utilisée pour faire jouer la machine */

    // Setters
public:
    void setCoupJoueur(UnCoup p_coup);
    /* initialise l'attribut coupJoueur avec la valeur
        du paramètre p_coup */
    void setCoupMachine(UnCoup p_coup);
    /* initialise l'attribut coupmachine avec la valeur
        du paramètre p_coup */
    void setScoreJoueur(unsigned int p_score);
    /* initialise l'attribut scoreJoueur avec la valeur
        du paramètre p_score */
    void setScoreMachine(unsigned int p_score);
    /* initialise l'attribut coupMachine avec la valeur
        du paramètre p_score */
    void setEtat(UnEtat p_etat);
    /* initialise l'attribut _etat avec la valeur
        du paramètre p_etat */
    void setScoreObjectif(unsigned int p_score = 5);
    /* initialise l'attribut scoreObjectif avec la valeur
        du paramètre p_score */
    void setDureePartie(unsigned int p_temps = 30);
    /* initialise l'attribut dureePartie avec la valeur
        du paramètre p_temps */
    void setTempsRestant(unsigned int p_temps);
    /* initialise l'attribut tempsRestant avec la valeur
        du paramètre p_temps */
    void setNomJoueur(QString p_nom= "Vous");
    /* initialise l'attribut nomJoueur avec la valeur
        du paramètre p_nom */

    // Autres modificateurs
    void genererCoupMachine(); //initialise coupMachine à une valeur aléatoire entre pierre, papier ou ciseau
    void majScores(char p_gagnant);
    /* Mise à jour des scores en fonction des règles de gestion actuelles :
            - 1 point pour le gagnant lorsqu'il y a un gagnant
            - 0 point en cas de match nul
                */
    void initScores();
    /* initialise à 0 les attributs scoreJoueur et scoreMachine
        NON indispensable */
    void initCoups();
    /* initialise à rien les attributs coupJoueur et coupMachine
        NON indispensable */


    ///* Attributs du Modèle

private:
    unsigned int scoreJoueur;   // score actuel du joueur
    unsigned int scoreMachine;  // score actuel de la Machine
    UnCoup coupJoueur;          // dernier coup joué par le joueur
    UnCoup coupMachine;         // dernier coup joué par la machine
    UnEtat _etat;               // etat actuel du jeu
    unsigned int scoreObjectif; // score à atteindre pour gagner
    unsigned int dureePartie;   // durée max de la partie en seconde
    unsigned int tempsRestant;  // temps restant avant la fin partie en secondes
    QString nomJoueur; //nom du joueur
};

#endif // CHIFOUMIMODELE_H
