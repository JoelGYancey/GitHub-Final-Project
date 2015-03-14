#ifndef CANTADDAXON_H
#define CANTADDAXON_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

/**@class cantAddAxon
 * @brief this class inherits from QDialog. It is a dialog window
 * intended to inform the user that they are attempting to add
 * an axon at a grid location that does not contain a neuron.
 *
 */

class cantAddAxon : public QDialog
{
    Q_OBJECT

public:
    cantAddAxon();
    ~cantAddAxon();

private:
    /** @var This label sets the text that the dialog will display */
    QLabel* cant_add_axon_label;

    /** @var This is the only button that the window contains */
    QPushButton* okay_button;
};

#endif // ADDNEURONDIALOG_H
