#include "chifoumivue.h"
#include "chifoumipresentation.h"
#include "chifoumimodele.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // créer le modèle
    ChifoumiModele *m = new ChifoumiModele();
    // créer la présentation et lui associer le modèle
    ChifoumiPresentation *p = new ChifoumiPresentation(m);
    // créer la vue
    ChifoumiVue w;
    // associer la vue à la présentation
    p->setVue(&w);
    // initialiser la vue en conformité avec l'état initial du modèle
    p->getVue()->majInterfaceGlobale(m->getEtat(),
                                     m->getCoupJoueur(),
                                     m->getCoupMachine(),
                                     m->getScoreJoueur(),
                                     m->getScoreMachine());
    // connexion des signaux de la vue avec les slots de la présentation
    w.addConnexion(p);

    w.show();
    return a.exec();
}
