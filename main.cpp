#include "mainwindow.h"
#include "gameboard.h"
#include "neuron.h"
#include "deleteneurondialog.h"
#include "cantaddaxon.h"
#include <QApplication>
#include <QDebug>

/**@mainpage Neuroscience Model Builder Application
 * @author Joel Yancey
 * @date March 13, 2015
 * @brief This application allows the generation of custom neuroscience models (schematics).
 * Functionality includes the ability to add excitatory and inhibitory neurons. Also, axons
 * can be made between neurons. This application may prove useful for thinking through
 * the connectivity of known or proposed neural circuits, which can take a great many forms in
 * order for the nervous system to accomplish its many diverse tasks.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    gameboard* b = new gameboard;

    w->setGameBoard(b);
    b->setMainWindow(w);



    w->show(); // BY DEFAULT, ALL WIDGETS ARE INVISIBLE. MUST ISSUE SHOW() COMMAND



    return a.exec(); // PASSES CONTROL OF THE PROGRAM TO Qt'S EVENT HANDLER
}
