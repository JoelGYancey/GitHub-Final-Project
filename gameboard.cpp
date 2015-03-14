#include "gameboard.h"




gameboard::gameboard(QWidget *parent, int size) :
    QWidget(parent)
{
    board_size=size;



    //------------ SETTINGS ------------//
    this->setWindowTitle("Neuroscience Model Builder by Joel Yancey");
    this->setStyleSheet("background-color:white;");
    neuron_size=60;


    //------------ INITIALIZE ------------//
    myNeurons = new neuron*[board_size*board_size]; // initialize an array of label pointers for each grid position
    currNeuron = new neuron;
    prevNeuron = new neuron;
    axon_store = new std::list<QPair<int,int>>;
    level = 0;


    //------------------------------- CREATE NEURONS & ADD TO GRID -------------------------------//
    QGridLayout* grid_lay = new QGridLayout;
    for(int i=0;i<board_size;++i) {
        for(int j=0;j<board_size;++j) {

            myNeurons[i*board_size+j] = new neuron(this,neuron_size);
            myNeurons[i*board_size+j]->set_neuronNum(i*board_size+j);
            myNeurons[i*board_size+j]->makeNotCurrent();

            grid_lay->addWidget(myNeurons[i*board_size+j],i+1,j+1);
            QObject::connect(myNeurons[i*board_size+j], SIGNAL(tell_board_Im_curr(neuron*)), this, SLOT(update_board_whos_curr(neuron*)));

        }
    }


    //------------------------------- CONTROL BOARD STUFF -------------------------------//

    levelLabel = new QLabel("You forgot to select a radiobox on the main window!");

    levelLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    levelLabel->setContentsMargins(0,0,0,0);
    levelLabel->setStyleSheet("color:black");
    levelLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    levelLabel->setAlignment(Qt::AlignCenter);
    QFont* font = new QFont("Times");
    font->setPointSize(24); font->setBold(true);
    levelLabel->setFont(*font);


    instructLabel_default = new QString("To add or delete a neuron, click on a grid location and then choose the option below.\n"
                                        "To add an axon to a neuron, select a grid location that contains a neuron, click\n"
                                        "'Add axon', and then click on a second neuron to form a synapse with.");
    instructLabel = new QLabel(*instructLabel_default);
    instructLabel->setAlignment(Qt::AlignCenter);

    // USER CONTROLS: ADD AXONS
    add_axon = new QPushButton("Add axon");
    connect(add_axon,SIGNAL(clicked()),this,SLOT(slot_add_axon()));
    cantAddAxon* cant_axon_dialog = new cantAddAxon;
    connect(this,SIGNAL(sig_cant_axon()),cant_axon_dialog,SLOT(show()));


    // USER CONTROLS: ADD NEURON BUTTON & DIALOG
    //add_neuron_buttons = new QPushButton("Add neuron");
    //addNeuronDialog* addDialog = new addNeuronDialog;
    //connect(add_neuron_button,SIGNAL(clicked()),addDialog,SLOT(show()));
    //connect(addDialog,SIGNAL(saysExc()),this,SLOT(slot_add_exc()));
    //connect(addDialog,SIGNAL(saysInh()),this,SLOT(slot_add_inh()));
    QHBoxLayout* add_neuron_lay = new QHBoxLayout;
    add_exc_button = new QPushButton("Add excitatory neuron"); add_neuron_lay->insertWidget(1,add_exc_button);
    add_inh_button = new QPushButton("Add inhibitory neuron"); add_neuron_lay->insertWidget(2,add_inh_button);
    connect(add_exc_button,SIGNAL(clicked()),this,SLOT(slot_add_exc()));
    connect(add_inh_button,SIGNAL(clicked()),this,SLOT(slot_add_inh()));


    // USER CONTROLS: DELETE NEURON BUTTON & DIALOG
    delete_neuron_button = new QPushButton("Delete neuron");
    deleteNeuronDialog* deleteDialog = new deleteNeuronDialog;
    connect(delete_neuron_button,SIGNAL(clicked()),deleteDialog,SLOT(show()));
    connect(deleteDialog,SIGNAL(saysYes()),this,SLOT(slot_delete_curr()));


    //------------------------------- OVERALL LAYOUT -------------------------------//
    QVBoxLayout* vert_lay = new QVBoxLayout;
    vert_lay->insertWidget(1,levelLabel);
    vert_lay->insertWidget(2,instructLabel);
    vert_lay->insertLayout(3,grid_lay);
    //vert_lay->insertWidget(4,add_neuron_button);
    vert_lay->insertLayout(4,add_neuron_lay);
    vert_lay->insertWidget(5,delete_neuron_button);
    vert_lay->insertWidget(6,add_axon);
    this->setLayout(vert_lay);


}



void gameboard::paintEvent(QPaintEvent*) {

    std::list<QPair<int,int>>::iterator it = axon_store->begin();
    for (it;it!=axon_store->end();++it){

        ////// EXCITATORY AXON PAINT //////

        if (myNeurons[it->first]->get_neuronState()==1) {

            QPoint temp_hillock = QPoint(myNeurons[it->second]->mapTo(this,QPoint( (*myNeurons[it->second]->WIDTH)/2 , (*myNeurons[it->second]->HEIGHT)/2) ));
            QPoint temp_terminal = QPoint(myNeurons[it->first]->mapTo(this,QPoint( (*myNeurons[it->first]->WIDTH)/2 , (*myNeurons[it->first]->HEIGHT)/2) ));

            // SET CONSTANTS
            double const1=.15; // CONSTANT FOR SIZE OF TERMINAL TRIANGLE
            double const2=.22; // CONSTANT FOR SYNAPSE DISTANCE

            // axon shaft
            QLineF axonLine(temp_hillock,temp_terminal);
            qreal L = axonLine.length();
            L=L/120;

            // axon shaft
            axonLine.setP1(axonLine.pointAt(const2/L));
            //axonLine.setP2(axonLine.pointAt(1-const2/(2*L)));
            axonLine.setP2(axonLine.pointAt(1));

            // perp synapse line
            QLineF perp = axonLine.normalVector();
            perp.setLength(((const1/L)*axonLine.length())/(2));
            perp.setP1(QPointF(perp.x1(),perp.y1())-QPointF(perp.dx(),perp.dy()));
            // draw terminal triangle
            QPointF pTemp = axonLine.pointAt(const1/L);
            axonLine.setP1(pTemp);
            QLineF side1(axonLine.p1(),perp.p1());
            QLineF side2(axonLine.p1(),perp.p2());

            QPainter painter(this);
            QPen pen(QColor(Qt::black),2);
            painter.setPen(pen);
            painter.drawLine(axonLine); painter.drawLine(perp); painter.drawLine(side1); painter.drawLine(side2);
        }

        ////// INHIBITORY AXON PAINT //////

        if (myNeurons[it->first]->get_neuronState()==2) {

            QPoint temp_hillock = QPoint(myNeurons[it->second]->mapTo(this,QPoint( (*myNeurons[it->second]->WIDTH)/2 , (*myNeurons[it->second]->HEIGHT)/2) ));
            QPoint temp_terminal = QPoint(myNeurons[it->first]->mapTo(this,QPoint( (*myNeurons[it->first]->WIDTH)/2 , (*myNeurons[it->first]->HEIGHT)/2) ));

            // SET CONSTANTS
            double const1=.12; // CONSTANT FOR SIZE OF TERMINAL
            double const2=.22; // CONSTANT FOR SYNAPSE DISTANCE

            QLineF axonLine(temp_hillock,temp_terminal);
            qreal L = axonLine.length();
            L=L/120;

            // axon shaft
            axonLine.setP1(axonLine.pointAt(const2/L));
            //axonLine.setP2(axonLine.pointAt(1-const2/2));
            axonLine.setP2(axonLine.pointAt(1));
            // perp synapse line
            //QPointF pTemp = axonLine.pointAt(const1/L);
            QLineF perp = axonLine.normalVector();
            perp.setLength(((const1/L)*axonLine.length())/2);
            perp.setP1(QPointF(perp.x1(),perp.y1())-QPointF(perp.dx(),perp.dy()));

            QPainter painter(this);
            QPen pen(QColor(Qt::black),2);
            painter.setPen(pen);
            painter.drawLine(axonLine); painter.drawLine(perp);

        }

    }
}




void gameboard::smallSlot(){
    clear_board();

    level = 1;
    levelLabel->setText("Half-Center Model (Brown Model)");

    myNeurons[2]->set_neuronState(1); myNeurons[6]->set_neuronState(1); myNeurons[10]->set_neuronState(1);
    myNeurons[13]->set_neuronState(2); myNeurons[15]->set_neuronState(2); myNeurons[24]->set_neuronState(1);
    myNeurons[28]->set_neuronState(1);

    axon_store->push_back(QPair<int,int>(2,6)); axon_store->push_back(QPair<int,int>(2,10)); axon_store->push_back(QPair<int,int>(6,13));
    axon_store->push_back(QPair<int,int>(13,10)); axon_store->push_back(QPair<int,int>(10,15)); axon_store->push_back(QPair<int,int>(15,6));
    axon_store->push_back(QPair<int,int>(6,24)); axon_store->push_back(QPair<int,int>(10,28));

    repaint();

}

void gameboard::medSlot(){
    clear_board();
    level = 2;
    levelLabel->setText("Custom build");
    repaint();
}

void gameboard::largeSlot(){
    clear_board();
    level = 3;
    levelLabel->setText("Tonic Excitation [neuroscientist]");
    repaint();
}



void gameboard::slot_delete_curr(){
    std::list<QPair<int,int>>::iterator it = axon_store->begin();
    for (it;it!=axon_store->end();++it){
        if (it->first==currNeuron->get_neuronNum()){ axon_store->erase(it); }
    }
    currNeuron->set_neuronState(0);
}



void gameboard::slot_add_exc(){ currNeuron->set_neuronState(1); repaint(); }
void gameboard::slot_add_inh(){ currNeuron->set_neuronState(2); repaint(); }


void gameboard::update_board_whos_curr(neuron* n){
    prevNeuron=currNeuron;
    currNeuron=n;

    for(int i=0;i<board_size;++i) {
        for(int j=0;j<board_size;++j) {
            //once code is debugged, try implementing this w/out set and get
            if (myNeurons[i*board_size+j]->get_neuronNum()==n->get_neuronNum()) myNeurons[i*board_size+j]->makeCurrent();
            else myNeurons[i*board_size+j]->makeNotCurrent();
        }
    }
    emit curr_just_changed();

    repaint();
}

void gameboard::slot_add_axon(){

    if (currNeuron->get_neuronState() != 0) {

        instructLabel->setText("Select neuron to recieve syanpse...");

        connect(this,SIGNAL(curr_just_changed()),this,SLOT(slot_pick_synapse()));
    } else {
        //try creating dialog locally!!!

        qDebug()<<"'sig_cant_axon' was called";
        emit sig_cant_axon();
    }
}


void gameboard::slot_pick_synapse(){

    instructLabel->setText(*instructLabel_default);

    if (currNeuron->get_neuronState() != 0) {
        axon_store->push_back(QPair<int,int>(prevNeuron->get_neuronNum(),currNeuron->get_neuronNum()));
    } else {
        qDebug()<<"'sig_cant_axon' was called";
        emit sig_cant_axon();
    }

    disconnect(this,SIGNAL(curr_just_changed()),this,SLOT(slot_pick_synapse()));
}


void gameboard::clear_board(){
    for(int i=0;i<board_size;++i) {
        for(int j=0;j<board_size;++j) { myNeurons[i*board_size+j]->makeNotCurrent(); myNeurons[i*board_size+j]->set_neuronState(0); }
    }
    axon_store->clear();
}



void gameboard::setMainWindow(MainWindow* main_window) { mw = main_window; }

gameboard::~gameboard()
{

}




//------------------------- FOR DEBUGGING -------------------------//

void gameboard::print_neurons(){
    qDebug()<<"---------------";
    for(int i=0;i<board_size;++i) {
        for(int j=0;j<board_size;++j) {
            qDebug()<<"neuronNum="<<myNeurons[i*board_size+j]->get_neuronNum()<<", isCurr="<<myNeurons[i*board_size+j]->get_isCurr()
                   <<", neuronState="<<myNeurons[i*board_size+j]->get_neuronState();
        }
    }
}

void gameboard::print_axons(){
    qDebug()<<"---------------";
    std::list<QPair<int,int>>::iterator it = axon_store->begin();
    for (it;it!=axon_store->end();++it){ qDebug()<<it->first<<"--->"<<it->second; }
}



