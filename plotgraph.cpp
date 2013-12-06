#include "plotgraph.h"

class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw( const QTime &base ):
        baseTime( base )
    {
    }
    virtual QwtText label( double v ) const
    {
        QTime upTime = baseTime.addSecs( static_cast<int>( v ) );
        return upTime.toString();
    }
private:
    QTime baseTime;
};






PlotGraph::PlotGraph(QWidget *parent ) :
    QwtPlot(parent) ,dataCount( 0 )
{


    initGraph();

}

void PlotGraph::initGraph()
{

    canvas = new QwtPlotCanvas();
    curve = new QwtPlotCurve("");
    symbol = new QwtSymbol( QwtSymbol::Diamond,
                            QBrush( Qt::yellow ), QPen( Qt::red, 1 ), QSize( 2, 2 ) );
    grid = new QwtPlotGrid();
    QwtScaleWidget *scaleWidget = axisWidget( QwtPlot::xBottom );


    curve->setRenderHint( QwtPlotItem::RenderAntialiased );
//    curve->setRenderThreadCount(2);
    setCanvas( canvas );


    // Ajusta Borda Minima para aparecer corretamente os labels de x
    const int fmh = QFontMetrics( scaleWidget->font() ).height();
    scaleWidget->setMinBorderDist( 0, fmh / 2 );

    curve->attach( this );
    curve->setSymbol( symbol );
    grid->attach( this );

    setAutoReplot( false );

    canvas->setBorderRadius( 5 );

    plotLayout()->setAlignCanvasToScales( true );

    setAxisTitle( QwtPlot::xBottom, " [h:m:s]" );

    setAxisScaleDraw( QwtPlot::xBottom,
        new TimeScaleDraw( QTime().currentTime()) );

    // Quantodade de pontos no eixo X aserem mostrados
    setAxisScale( QwtPlot::xBottom, 0, HISTORY );

    // Rotaciona os labels do eixo X
    setAxisLabelRotation( QwtPlot::xBottom, -10.0 );
    setAxisFont(QwtPlot::xBottom, QFont("Times", 9, QFont::Cursive));

    // Alinha eixo X ao canto esquerdo inferior
    setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );

    // Nome eixo Y
    setAxisTitle( QwtPlot::yLeft, "Celsius [C]" );

    // Escala eixo Y
    setAxisScale( QwtPlot::yLeft, 0, 100 );

    QColor c (Qt::red);
    c.setAlpha( 200 );
    curve->setPen(c);
    c.setAlpha( 80 );
    curve->setBrush(c);

    curve->setVisible(true );
    replot();

    for ( int i = 0; i < HISTORY; i++ )
        timeData[HISTORY - 1 - i] = i;
}

void PlotGraph::updateValues(double num)
{

    for ( int i = dataCount; i > 0; i-- )
    {
            if ( i < HISTORY )
                data[i] = data[i-1];
    }

        data[0] = num;


    if ( dataCount < HISTORY )
        dataCount++;

    for ( int j = 0; j < HISTORY; j++ )
        timeData[j]++;

    setAxisScale( QwtPlot::xBottom,
        timeData[HISTORY - 1], timeData[0] );

       curve->setRawSamples(
            timeData, data, dataCount );

    replot();

}
