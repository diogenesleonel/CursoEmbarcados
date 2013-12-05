#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <qextserialport.h>
#include <QTimer>


class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = 0);
    void send(int count, char *bytes);
    bool connectNow(QString tty);

private:
    QextSerialPort *serial;
    QTimer *time;
    QByteArray bytesReceived;
    int num;

signals:
         void newRead(double temperature);
    
public slots:
    void receive();
    void teste();

    
};

#endif // SERIAL_H
