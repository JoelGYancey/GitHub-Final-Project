#ifndef NEURON_H
#define NEURON_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include "deleteneurondialog.h"
#include "gameboard.h"


/**@class neuron
 *@brief this class inherits from QWidget. It contains all of the properties
 *of each neuron on the gameboard, regardless of whether the location contains
 * a neuron.
 *
 */

class neuron : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief this constructor is used because the neuron must know what size it is.
     * @param parent
     * @param size_input
     */
    explicit neuron(QWidget *parent=0,int size_input=60);

    //these should be private, but currently need to be accessed by other classes. fix when have time
    /** @var width of neuron */
    int* WIDTH;
    /** @var height of neuron */
    int* HEIGHT;

    /** "setter" and "getter" helper functions function */
    void set_neuronNum(int num){ neuronNum=num; }
    int get_neuronNum(){ return neuronNum; }
    int get_isCurr(){ return isCurr; }
    void set_neuronState(int state){ neuronState=state; }
    int get_neuronState(){ return neuronState; }

    /** functions for making the neuron current or not current.
     * a neuron becomes current if and only if it is selected by the user */
    void makeCurrent(){ isCurr=1;}
    void makeNotCurrent(){ isCurr=0;}

protected:
    /** overloads paint event to show the neuron as off, excitatory, or inhibitory */
    void paintEvent(QPaintEvent*);
    /** when the neuron is clicked, it becomes the current neuron and emits the
     * 'void tell_board_Im_curr(neuron*)' signal. */
    void mousePressEvent(QMouseEvent* e);

    ~neuron();

signals:
    /** signal informs the gameboard that is has been selected and is tehrefore current */
    void tell_board_Im_curr(neuron*);

public slots:

    /** This slot is connected to a signal of the gameboard that lets all neurons except
     * for the newly selected neuron know when ANY other neuron is selected. If another
     * neuron is selected, this slot will then turn this neuron off. */
    void turnOff(){ neuronState=0; }

private:

    /** @var size of the neuron */
    int size;

    /** @var a unique identifying number for each neuron */
    int neuronNum;
    /** @var state of the neuron. 0 if off, 1 if excitatory, 2 if inhibitory */
    int neuronState;
    /** @var current state of the neuron. 1 if current, else 0 */
    int isCurr;
    /** true or false depending on whether the neuron has an axon */
    bool hasAxon;

    /** @var text on the neuron to indicate whether inhibitory or excitatory */
    QLabel* text;
    /** @var exact location of where the text for the neurons label should be located */
    QPoint* neuronPos;


};

#endif // NEURON_H
