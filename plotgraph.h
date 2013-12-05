#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H


#include <qlayout.h>
#include <qlabel.h>
#include <qpainter.h>
#include <QTime>
#include <qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>



#define HISTORY 60

class PlotGraph : public QwtPlot
{
    Q_OBJECT
public:
    explicit PlotGraph(QWidget * = 0 );
    void initGraph();

private:

    QwtPlotCurve *curve;
     QwtPlotCanvas *canvas;
     QwtSymbol *symbol;
     QwtPlotGrid *grid;

    double data[HISTORY];
    double timeData[HISTORY];
    int dataCount;
    char HistorySize;

signals:
    
public slots:
    void updateValues(double num);
    
};

#endif // PLOTGRAPH_H
