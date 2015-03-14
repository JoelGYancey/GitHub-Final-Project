#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QString>
#include <QKeyEvent>
#include <QPushButton>
#include <QPainter>
#include <QPoint>
#include <list>
#include <QDebug>
#include <QFrame>
#include <QGraphicsGridLayout>
#include "mainwindow.h"
#include "neuron.h"
#include "cantaddaxon.h"

/**@class gameboard
 *@brief this class inherits from QWidget. This object is the gameboard, which is implemented
 * in main. It consists of a title, directions for gameplay, a grid of neurons, and buttons
 * for interacting with the board.
 */

class neuron;

class MainWindow;

class gameboard : public QWidget
{
    Q_OBJECT
public:
    explicit gameboard(QWidget *parent = 0, int size = 6);
    ~gameboard();


    /** Overloads the paintevent to draw the axons that should currently be
     * shown on the gameboard */
    void paintEvent(QPaintEvent *e);

    /** Sets the main window to be the gameboard's parent.
     * The only function call is in main. */
    void setMainWindow(MainWindow* main_window);

    /** These functions are for debugging purposes */
    void print_neurons();
    void print_axons();

signals:
    /** Signals that the current neuron has changed. This signal is connected only
     * to the 'slot_pick_synapse()' slot. It is necessary because of the implementation
     * of the add axon feature, as 2 neurons must be delected by the user in order
     * to determine the beginning (hillock) and end (terminal) of the axon. */
    void curr_just_changed();

    /** Signals to the cantAddAxon dialog that it needs to be shown */
    void sig_cant_axon();

public slots:

    /** Dependent on the radio button checked, these slots will construct
     * the appropriate (user-selected) type of gameboard */
    void smallSlot();
    void medSlot();
    void largeSlot();

    /** This slot informs all neurons which neuron is current, and updates all
     * neurons to reflect any changes. */
    void update_board_whos_curr(neuron*);
    /** Deletes the selected neuron */
    void slot_delete_curr();
    /** adds excitatory neuron */
    void slot_add_exc();
    /** adds inhibitory neuron */
    void slot_add_inh();
    /** adds axon, whether excitatory or inhibitory */
    void slot_add_axon();
    /** This slot handles the interim period where the Add axon button has been clicked,
     * but the user still must select a second location on the board to complete the axon */
    void slot_pick_synapse();
    void clear_board();

private:
    MainWindow* mw;

    /** @var size of the board */
    int board_size;
    /** @var size of the neurons */
    int neuron_size;
    /** @var board type */
    int level;

    // Labels and buttons
    /** @var label of the selected level */
    QLabel* levelLabel;
    /** @var instruction label */
    QLabel* instructLabel;
    /** @var default instruction label */
    QString* instructLabel_default;
    /** @var add axon button */
    QPushButton* add_axon;
    /** @var add excitatory neuron button */
    QPushButton* add_exc_button;
    /** @var add inhibitory neuron button */
    QPushButton* add_inh_button;
    //QPushButton* add_neuron_button;
    /** @var delete neuron button */
    QPushButton* delete_neuron_button;


    // Board state variables
    /** @var this is an array of all of the neurons on the board*/
    neuron** myNeurons;
    /** @var this stores the board location of the currently selected neuron */
    neuron* currNeuron;
    /** @var this stores the board location of the previously selected neuron */
    neuron* prevNeuron;

    /** @var list of pairs of locations of hillock and terminal for all axons */
    std::list<QPair<int,int>>* axon_store;


};

#endif // GAMEBOARD_H
