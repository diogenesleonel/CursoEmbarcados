#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include <QTimer>
#include "plotgraph.h"
#include "serial.h"

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT
    
public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();
    
private slots:

    void on_Led_toggled(bool checked);
    void on_Led_2_toggled(bool checked);
    void on_serial_toggled(bool checked);
    void on_Cooler_toggled(bool checked);
    void on_Heater_toggled(bool checked);

    void piscarLed();

private:
    Ui::Principal *ui;
    PlotGraph *grafico;
    Serial *serialConnect;
    QTimer piscar;
    bool ok;

};

#endif // PRINCIPAL_H
