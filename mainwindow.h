#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "gameboard.h"
#include "neuron.h"

class gameboard;

/**@class MainWindow
 *@brief this class inherits from QMainWindow. This object is implemented in main.
 * It consists of a title, radiobuttons used to determine the type of board that
 * is constructed, and a start button. The start button calls an object of the
 * 'gameboard' class (which was also contructed in main), making the gameboard
 * window appear.
 */


class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    /** signals emitted based on which radio button is selected */
    void pick_small();
    void pick_med();
    void pick_large();

public slots:


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /** This function is called only in main. It sets the gameboard which is connected
     * to the main window. It is intended to be called only once, in main. */
    void setGameBoard(gameboard* game_board);

private:
    MainWindow *ui;
    /** @var central widget of the main window */
    QWidget* widget1;
    /** @var title of the main window */
    QLabel* label_title;
    /** @var sub-text of the main window */
    QLabel* label_subtitle;
    /** @var start button */
    QPushButton* button_start;
    /** @var quit button */
    QPushButton* button_quit;
    /** @var radio buttons for each board type */
    QRadioButton* smallBoard;
    QRadioButton* mediumBoard;
    QRadioButton* largeBoard;

};

#endif // MAINWINDOW_H
