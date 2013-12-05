#include "serial.h"

Serial::Serial(QObject *parent) :
    QObject(parent)
{
    time = new QTimer(this);
    num = 0.0;
    connect(time,SIGNAL(timeout()),this,SLOT(teste()));
            time->start(1000);
}


void Serial::send(int count, char *bytes)
{

}

bool Serial::connectNow(QString tty="/dev/ttyUSB0")
{


    // Abre serial para comunicação usando event driven
    serial=new QextSerialPort(tty, QextSerialPort::EventDriven);

    // Velocidade
    serial->setBaudRate(BAUD57600);

    // Numero de bits
    serial->setDataBits(DATA_8);
    serial->setParity(PAR_NONE);
    serial->setStopBits(STOP_1 );
    serial->setFlowControl(FLOW_OFF );


    if(serial->open(QIODevice::ReadWrite) == true)
    {
        connect(serial, SIGNAL(readyRead()), this, SLOT(receive()));

        qDebug() << "Pronto para receber dados na porta " <<serial->portName();
        return true;
    }
    else
    {
        qDebug() << "Erro ao abrir:" <<serial->errorString();
        return false;
    }

}

bool Serial::closeConnection()
{
    return serial->close();
}

void Serial::receive()
{
    QByteArray bytes;
   // int a =serial->bytesAvailable();
    //bytes.resize(a);
    //serial->read(bytes.data(), bytes.size());

    bytes = serial->readAll();

//    qDebug() << "bytes read:" << bytes.size();
   // qDebug() << "bytes:" << bytes;

//    char buffer[256];

//    int rec= serial->read(buffer,255);
//    buffer[rec]='\0';

//    char end = 13;

//    qDebug() << "new";

    //qDebug()<< QString::fromLocal8Bit(buffer,rec) <<rec;

    //QByteArray bytes;
    //int a = serial->bytesAvailable();
   // bytes.resize(a);
   // //serial->read(bytes.data(), bytes.size());
    //qDebug() << "bytes read:" << bytes.size();

    bytesReceived.append(bytes);

    // only do input if all of it has been received.
    // without this the serial port transports line of messages
    // with only 3 or 4 bytes at a time
    // Recebeu mensagem completa
//    if(bytes.lastIndexOf())
//    {
//        qDebug() << QString::fromAscii(bytesReceived);
//        bytesReceived.clear();
    //    }
}

void Serial::teste()
{
    num++;
    emit newRead(num);
}
