#include "parametres.h"
#include "ui_parametres.h"

Parametres::Parametres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametres)
{
    ui->setupUi(this);
}

Parametres::~Parametres()
{
    delete ui;
}

QString Parametres::getLineEditNomJoueur()
{
    return ui->eNomJoueur->text();
}

int Parametres::getLineEditObjectifScore()
{
    return ui->eObjectifScore->text().toInt();
}

int Parametres::getLineEditDureePartie()
{
    return ui->eDureePartie->text().toInt();
}
