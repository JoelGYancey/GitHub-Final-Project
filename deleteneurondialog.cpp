#include "deleteneurondialog.h"

deleteNeuronDialog::deleteNeuronDialog()
{
    // initiate necessary objects on the heap
    askUser = new QLabel("Delete this neuron and its axons?");
    no_button = new QPushButton("No"); no_button->setAutoDefault( false );
    yes_button = new QPushButton("Yes"); yes_button->setAutoDefault( true );


    // LAYOUT STUFF
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(askUser,1,1,1,2);
    layout->addWidget(no_button,2,1,1,1);
    layout->addWidget(yes_button,2,2,1,1);


    this->setLayout(layout);

    // SIGNALS AND SLOTS are activated in the constructor
    QObject::connect(no_button,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(no_button,SIGNAL(clicked()),this,SLOT(slot_no()));
    QObject::connect(yes_button,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(yes_button,SIGNAL(clicked()),this,SLOT(slot_yes()));

}

void deleteNeuronDialog::slot_no(){ emit saysNo(); }
void deleteNeuronDialog::slot_yes(){ emit saysYes(); }


deleteNeuronDialog::~deleteNeuronDialog()
{

}

