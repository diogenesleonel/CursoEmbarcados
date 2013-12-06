#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <qextserialport.h>
#include <QTimer>
#include <QStringList>

// Mensagem T[0-9][0-9][0-9]_C[0-9][0-9][0-9]_H[0-9][0-9][0-9]_\n

class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = 0);
    void send(int count, char *bytes);
    bool connectNow(QString tty="/dev/ttyACM0");
    void closeConnection();
    void decodeMsg(QByteArray msg);

private:
    QextSerialPort *serial;
    QByteArray bytesReceived;
    QByteArray mensagem;

signals:
         void temperature(double celsius);
         void cooler(int cycle);
         void heater(int cycle);
    
public slots:
    void receive();

    
};

#endif // SERIAL_H
