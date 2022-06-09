#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QDialog>
#include <QString>

namespace Ui {
class Parametres;
}

class Parametres : public QDialog
{
    Q_OBJECT

public:
    explicit Parametres(QWidget *parent = nullptr);
    ~Parametres();
    //getters
    QString getLineEditNomJoueur(); // Retourne le contenu du line edit eNomJoueur
    int getLineEditObjectifScore(); // Retourne le contenu du line edit eObjectifScore
    int getLineEditDureePartie(); // Retourne le contenu du line edit eDureePartie

private:
    Ui::Parametres *ui;
};

#endif // PARAMETRES_H
