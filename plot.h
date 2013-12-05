#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QTimer>
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
    QPolygonF points;
    QwtPlot *plot;
    QTimer *time;
    xx
    QwtPlotCurve *curve ;

    float t,tt;

signals:
    
public slots:
    void atualiza();
    
};

#endif // PLOT_H
