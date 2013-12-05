#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include "plotgraph.h"

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

private:
    Ui::Principal *ui;
    PlotGraph *grafico;

};

#endif // PRINCIPAL_H
