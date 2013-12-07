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
    ok=false;




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

    if(checked && serialConnect->getSerial()->isOpen()){

        connect(&piscar,SIGNAL(timeout()),this,SLOT(piscarLed()));
//        ui->Led_2->setIcon(QIcon(":/icons/led-on"));
        piscar.start(500);
        // Liga led
            serialConnect->send(QByteArray("c"));

    }
    else{
        disconnect(&piscar,SIGNAL(timeout()),this,SLOT(piscarLed()));

        ui->Led_2->setIcon(QIcon(":/icons/led-off"));

        if(serialConnect->getSerial()->isOpen())
            serialConnect->send(QByteArray("c"));
    }


}




void Principal::on_serial_toggled(bool checked)
{

    if(checked){
        // Conecta na Serial

        if(serialConnect->connectNow()){
            ui->serial->setIcon(QIcon(":/icons/serial-on"));
            connect(serialConnect,SIGNAL(temperature(double)),ui->
                    widget,SLOT(updateValues(double)));

        }else{
            ui->serial->setIcon(QIcon(":/icons/serial-error"));
            disconnect(serialConnect,SIGNAL(temperature(double)),ui->
                       widget,SLOT(updateValues(double)));
            ui->widget->initGraph();

        }

    }
    else{
        // Desconecta da Serial

        serialConnect->closeConnection();
        ui->serial->setIcon(QIcon(":/icons/serial-off"));

        disconnect(serialConnect,SIGNAL(temperature(double)),ui->
                   widget,SLOT(updateValues(double)));
        ui->widget->detachItems();
        ui->widget->initGraph();



    }


}

void Principal::on_Cooler_toggled(bool checked)
{
    if(checked){
        ui->Cooler->setIcon(QIcon(":/icons/cooler-on"));

        // Liga led
        if(serialConnect->getSerial()->isOpen())
            serialConnect->send(QByteArray("c"));

    }
    else{
        ui->Cooler->setIcon(QIcon(":/icons/cooler-off"));

        if(serialConnect->getSerial()->isOpen())
            serialConnect->send(QByteArray("c"));
    }
}

void Principal::on_Heater_toggled(bool checked)
{
    if(checked){
        ui->Heater->setIcon(QIcon(":/icons/cooler-on"));

        // Liga led
        if(serialConnect->getSerial()->isOpen())
            serialConnect->send(QByteArray("c"));

    }
    else{
        ui->Heater->setIcon(QIcon(":/icons/cooler-off"));

        if(serialConnect->getSerial()->isOpen())
            serialConnect->send(QByteArray("c"));
    }
}

void Principal::piscarLed()
{

    QString status = (ok)?"on":"off";
    ui->Led_2->setIcon(QIcon(":/icons/led-"+status));
    ok^=true;

}
