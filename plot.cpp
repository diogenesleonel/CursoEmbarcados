#include "plot.h"

Plot::Plot(QWidget *parent) :
    QWidget(parent)
{

    QwtPlot *plot = new QwtPlot(this);
    plot->setTitle( "Temperatura" );
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, 0.0, 100.0);
    plot->setAxisScale(QwtPlot::xBottom, 0.0, 20.0);
    plot->insertLegend( new QwtLegend() );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( plot );

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle( "Celsius" );
    curve->setPen( Qt::blue, 4 ),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 2, 2 ) );
    curve->setSymbol( symbol );

    QPolygonF points;
    points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
    << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
    << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 ) << QPointF( 6.0, 1.1 )<<QPointF( 7.0, 1.1 );
    curve->setSamples( points );

    curve->attach( plot );

    plot->resize( 480, 200 );
    plot->show();

    qDebug("ola");




}
