#ifndef DELETENEURONDIALOG_H
#define DELETENEURONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>

/**@class deleteNeuronDialog
 *@brief this class inherits from QDialog. It is a dialog window
 * intended to ask the user for verification that they want to delete
 * the currently selected neuron whenever the "Delete neuron" button is
 * clicked.
 *
 */


class deleteNeuronDialog : public QDialog
{
    Q_OBJECT

    // whether user clicks yes or no determines which slot
    // is activate/ whether neuron is deleted
signals:
    void saysNo();
    void saysYes();
public slots:
    void slot_no();
    void slot_yes();

public:

    /** This is the window's 'no' button, and will close the window taking no further action */
    QPushButton* no_button;
    /** This is the window's 'yes' button, and will delete the selected neuron */
    QPushButton* yes_button;


    deleteNeuronDialog();
    ~deleteNeuronDialog();

private:

    /** @var This label determines the dialog's text. Ask's if the user really wishes to
     * delete the currently selected neuron. */
    QLabel* askUser;
};

#endif // DELETENEURONDIALOG_H
