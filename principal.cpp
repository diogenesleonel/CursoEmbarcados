#include "principal.h"
#include "ui_principal.h"




Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);

    // Ref{http://qt-project.org/doc/qt-4.8/qt.html#WindowType-enum}
    this->setWindowFlags(Qt::SplashScreen);



}

Principal::~Principal()
{
    delete ui;
}
