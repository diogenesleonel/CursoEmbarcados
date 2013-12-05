#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

class Plot : public QWidget
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PLOT_H
