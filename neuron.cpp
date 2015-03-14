#include "neuron.h"

class gameboard;

neuron::neuron(QWidget *parent,int size_input) : QWidget(parent),size(size_input)
{
    emit tell_board_Im_curr(this);

    WIDTH= new int(size_input); HEIGHT= new int(size_input);
    this->setFixedSize(*WIDTH,*HEIGHT);

    neuronState=0;

    neuronPos = new QPoint(mapToParent(QPoint(0,0)));

    hasAxon=false;

}


// PAINT A NEURON
void neuron::paintEvent(QPaintEvent*)
{

    QPainter painter(this);
    QRect rec(0,0,*WIDTH,*HEIGHT);
    //QBrush brush(Qt::gray);
    //painter.fillRect(rec,brush);

    if (isCurr==1) {
    QRect rect(0, 0, *WIDTH, *HEIGHT);
    painter.setPen(QPen(Qt::black, 3, Qt::DotLine, Qt::RoundCap));
    painter.drawRect(rect);
    }


    if (neuronState==0) {
        painter.drawText(neuronPos->x(),neuronPos->y(),60,60,Qt::AlignCenter, tr("[insert]"));
    }
    // excitatory neuron
    else if (neuronState==1){

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        painter.drawEllipse(10, 10, *WIDTH-20, *HEIGHT-20);
        painter.drawText(0, 0,*WIDTH,*HEIGHT,Qt::AlignCenter, tr("Exc"));

    }
    else if (neuronState==2){
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        painter.drawEllipse(10, 10, *WIDTH-20, *HEIGHT-20);
        painter.drawText(0, 0,*WIDTH,*HEIGHT,Qt::AlignCenter, tr("Inh"));
    }

}



// WHEN A NEURON IS CLICKED
void neuron::mousePressEvent(QMouseEvent*)
{
    emit tell_board_Im_curr(this);

    repaint();
}


neuron::~neuron()
{

}

