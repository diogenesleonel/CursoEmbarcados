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

void Serial::decodeMsg(QString msg)
{

}

void Serial::receive()
{

    if (!serial->isOpen())
            return;
//    QByteArray bytes;
//    int a =serial->bytesAvailable();
//    bytes.resize(a);
//    serial->read(bytes.data(), bytes.size());

//    bytes = serial->readAll();

//    qDebug() << "bytes read:" << bytes.size();
   // qDebug() << "bytes:" << bytes;

//    char buffer[256];

//    int rec= serial->read(buffer,255);
//    buffer[rec]='\0';

//    char end = 13;

//    qDebug() << "new";

//    qDebug()<< QString::fromLocal8Bit(buffer,rec) <<rec;

    //QByteArray bytes;
    //int a = serial->bytesAvailable();
   // bytes.resize(a);
//    serial->read(bytes.data(), bytes.size());
//    qDebug() << "bytes read:" << bytes;

    //bytesReceived.append(bytes);

    // only do input if all of it has been received.
    // without this the serial port transports line of messages
    // with only 3 or 4 bytes at a time
    // Recebeu mensagem completa
//    if(bytes.contains(13))
//    {
//        qDebug() << QString::fromAscii(bytesReceived);
//        bytesReceived.clear();
//        }


    // Espera chegar o caracter \n no buffer, copia o conteudo antes do \n e adiciona o restante ao inicio do buffer

    //qDebug(QString(bytesReceived.indexOf("\n")).toAscii());

//    decodeMsg(QString.fromAscii(bytesReceived::data()));

       QByteArray result;
       int bytesAvailable = serial->bytesAvailable();
       result.resize(bytesAvailable);
       serial->read(result.data(), result.size());
       qDebug() <<"Recebido " << result;

       bytesReceived.append(result);

       qDebug()<<"Buffer " <<bytesReceived;

       // Verifica a posição do delimitador espaço e T, se não existir, esperar proxima conversão
        // Caso contrario encontar Posição do T e encontrar posição do espaço
            // Copiar mensagem e passaar para outra função
            // Apagar do bytesRecived tudo para tras do delimitador espaço, inclusive ele

//       bytesReceived.remove()
        int inicio= bytesReceived.indexOf("T");
        int fim = bytesReceived.indexOf(" ");

        qDebug()<< "Cortar" <<inicio << " " << fim;

        // Temos uma Mensagem Completa
        if(inicio!=-1 && fim!=-1 && inicio < fim){

        // Copia a mensagem e encaminha para processamento

        mensagem = bytesReceived.mid(inicio,fim-inicio);
        qDebug() << "Mensagem " << mensagem;

        // Remove do Buffer, incluindo o delimitador de fim

        bytesReceived.remove(0,fim+1);


       }


}

void Serial::teste()
{
//    num++;
    emit temperature(10);
}
