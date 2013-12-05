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


class CpuCurve: public QwtPlotCurve
{
public:
    CpuCurve( const QString &title ):
        QwtPlotCurve( title )
    {
        setRenderHint( QwtPlotItem::RenderAntialiased );
        setRenderThreadCount(3);

    }

    void setColor( const QColor &color )
    {
        QColor c = color;
        c.setAlpha( 200 );

        setPen(c);

        c.setAlpha( 80 );

        setBrush(c);
    }
};



PlotGraph::PlotGraph(QWidget *parent ) :
    QwtPlot(parent) ,dataCount( 0 )
{

    setAutoReplot( false );

    QwtPlotCanvas *canvas = new QwtPlotCanvas();

    canvas->setBorderRadius( 5 );
    setCanvas( canvas );

    plotLayout()->setAlignCanvasToScales( true );

//    setAxisTitle( QwtPlot::xBottom, " [h:m:s]" );

    setAxisScaleDraw( QwtPlot::xBottom,
        new TimeScaleDraw( QTime(0,0)) );

    // Quantodade de pontos no eixo X aserem mostrados
    setAxisScale( QwtPlot::xBottom, 0, HISTORY );

    // Rotaciona os labels do eixo X
    setAxisLabelRotation( QwtPlot::xBottom, -10.0 );
    setAxisFont(QwtPlot::xBottom, QFont("Times", 9, QFont::Cursive));

    // Alinha eixo X ao canto esquerdo inferior
    setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );

    // Ajusta Borda Minima para aparecer corretamente os labels de x
    QwtScaleWidget *scaleWidget = axisWidget( QwtPlot::xBottom );
    const int fmh = QFontMetrics( scaleWidget->font() ).height();
    scaleWidget->setMinBorderDist( 0, fmh / 2 );

    // Nome eixo Y
    setAxisTitle( QwtPlot::yLeft, "Celsius [C]" );

    // Escala eixo Y
    setAxisScale( QwtPlot::yLeft, 0, 100 );


    CpuCurve *curves;


    curves = new CpuCurve( "System" );
    curves->setColor( Qt::red );
    curves->attach( this );
    curve = curves;

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Diamond,
    QBrush( Qt::yellow ), QPen( Qt::red, 1 ), QSize( 2, 2 ) );
    curve->setSymbol( symbol );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( this );

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
