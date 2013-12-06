#include "serial.h"

Serial::Serial(QObject *parent) :
    QObject(parent)
{

}


void Serial::send(int count, char *bytes)
{

}

bool Serial::connectNow(QString tty)
{


    // Abre serial para comunicação usando event driven
    serial=new QextSerialPort("/dev/ttyACM0", QextSerialPort::EventDriven);

    // Velocidade
    serial->setBaudRate(BAUD9600);

    // Numero de bits
    serial->setDataBits(DATA_8);
    serial->setParity(PAR_NONE);
    serial->setStopBits(STOP_1 );
    serial->setFlowControl(FLOW_OFF);
//    serial->waitForReadyRead(10);





    if(serial->open(QIODevice::ReadWrite) == true)
    {
        //serial->write("i",1);
        //serial->flush();
        connect(serial, SIGNAL(readyRead()), this, SLOT(receive()));

        // Envia comando para arduino iniciar a conversão e comunicação serial

        qDebug() << "Pronto para receber dados na porta " <<serial->portName();

        return true;
    }
    else
    {
        qDebug() << "Erro ao abrir:" <<serial->errorString();
        return false;
    }

}

void Serial::closeConnection()
{
     serial->close();

     disconnect(serial, SIGNAL(readyRead()), this, SLOT(receive()));

     qDebug() << "Desconectado:";

}

void Serial::decodeMsg(QByteArray msg)
{

    QString m1 (msg);

    QStringList list1 = m1.split("_",QString::SkipEmptyParts);



    // Para cada um dos campos fazer a conversão e emitir um sinal

    QString temp = list1.at(0);
    QString cooler = list1.at(1);
    QString heater = list1.at(2);

    emit temperature(temp.right(3).toDouble());




}

void Serial::receive()
{

    if (!serial->isOpen())
        return;


    QByteArray result;
    result.resize(serial->bytesAvailable());
    serial->read(result.data(), result.size());

    qDebug() <<"Recebido " << result;

    bytesReceived.append(result);

    qDebug()<<"Buffer " <<bytesReceived;

    int inicio= bytesReceived.indexOf("T");
    int fim = bytesReceived.indexOf(" ");

    qDebug()<< "Cortar" <<inicio << " " << fim;

    // Testa se existe uma Mensagem Completa
    if(inicio!=-1 && fim!=-1 && inicio < fim){

        // Copia a mensagem e encaminha para processamento
        mensagem = bytesReceived.mid(inicio,fim-inicio);


        qDebug() << "Mensagem " << mensagem;

        // Processa
        decodeMsg(mensagem);

        // Remove do Buffer, incluindo o delimitador de fim
        bytesReceived.remove(0,fim+1);


    }


}


