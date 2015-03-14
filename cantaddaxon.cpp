#include "cantaddaxon.h"

cantAddAxon::cantAddAxon()
{

    okay_button = new QPushButton("okay");
    cant_add_axon_label = new QLabel("Can't add axon there!");

    // LAYOUT STUFF
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(cant_add_axon_label,1);
    layout->addWidget(okay_button,2);
    this->setLayout(layout);

    // SIGNALS AND SLOTS are activated in the constructor
    QObject::connect(okay_button,SIGNAL(clicked()),this,SLOT(close()));

}



cantAddAxon::~cantAddAxon()
{

}
