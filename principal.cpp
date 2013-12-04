#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::SplashScreen);
}

Principal::~Principal()
{
    delete ui;
}
