#include "principal.h"
#include "ui_principal.h"




Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);

    // Ref{http://qt-project.org/doc/qt-4.8/qt.html#WindowType-enum}
    //this->setWindowFlags(Qt::SplashScreen);
    this->setWindowFlags(Qt::CustomizeWindowHint);

    serialConnect = new Serial(this);

    connect(serialConnect,SIGNAL(newRead(double)),ui->widget,SLOT(updateValues(double)));





}

Principal::~Principal()
{
    delete ui;
}

void Principal::on_Led_toggled(bool checked)
{
    if(checked){
        ui->Led->setIcon(QIcon(":/icons/led-on"));
        // Envia Comando Para Ligar Led

    }else{
        ui->Led->setIcon(QIcon(":/icons/led-off"));
        // Envia Comando Para Ligar Led

    }

}

void Principal::on_Led_2_toggled(bool checked)
{

    if(checked){
        ui->Led_2->setIcon(QIcon(":/icons/led-on"));
        // Envia Comando Para Ligar Led
    }
    else{
        ui->Led_2->setIcon(QIcon(":/icons/led-off"));
        // Envia Comando Para Ligar Led

    }


}




void Principal::on_serial_toggled(bool checked)
{
//    QPalette *palette1 = new QPalette();
//    qDebug("certo");
//    if(checked){
//        palette1->setColor(QPalette::Button,Qt::green);
//        ui->serial->setPalette(*palette1);
//        // Envia Comando Para Ligar Led
//    }
//    else{
//        palette1->setColor(QPalette::Button,Qt::red);
//        ui->serial->setPalette(*palette1);
//        // Envia Comando Para Ligar Led

//    }

    if(checked){
        // Conecta na Serial

        if(serialConnect->connectNow()){
            ui->serial->setIcon(QIcon(":/icons/serial-on"));
        }else{
            ui->serial->setIcon(QIcon(":/icons/serial-error"));
        }

    }
    else{
        if(serialConnect->closeConnection()){
            ui->serial->setIcon(QIcon(":/icons/serial-off"));
        }else{
            ui->serial->setIcon(QIcon(":/icons/serial-error"));
        }

    }


}
