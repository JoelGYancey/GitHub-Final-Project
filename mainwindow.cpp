#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("Neuroscience Model Builder by Joel Yancey");
    this->setFixedSize(700,350);
    this->setStyleSheet("QMainWindow {background: 'white';}");

    // central widget of the control window
    widget1 = new QWidget;

    // label for title of control window
    label_title = new QLabel("<center>Neuroscience Model Builder</center>");
    label_subtitle = new QLabel("<font size = 4><center>Select a model to begin with, or choose 'custom build' to start from scratch.</center></font>");
    label_title->setStyleSheet("QLabel {color : black;}");
    //QFont* font_main_title = new QFont("Courier New");
    QFont* font_main_title = new QFont("Times");
    font_main_title->setBold(true);
    font_main_title->setPointSize(38);
    label_title->setFont(*font_main_title);


    // "start" button that switch to the game board and begin game
    button_start = new QPushButton("Start");
    QFont* font_start_button = new QFont;
    font_start_button->setPointSize(26);
    button_start->setFont(*font_start_button);
    button_start->setMinimumWidth(600);
    button_start->setMinimumHeight(70);


    button_quit = new QPushButton("Quit");
    button_quit->setFont(*font_start_button);
    button_quit->setMinimumWidth(600);
    button_quit->setMinimumHeight(70);

    QObject::connect(button_quit, SIGNAL(clicked()), qApp, SLOT(quit()));


    /*
    QFont* font_start_button = new QFont;
    font_start_button->setPointSize(26);
    button_start->setFont(*font_start_button);
    button_start->setMinimumWidth(600);
    button_start->setMinimumHeight(70);
    */


    // radio buttons for level selection
    smallBoard = new QRadioButton("[Example] Half-Center Model for a Central Pattern Generator (CPG)");
    mediumBoard = new QRadioButton("Custom build");
    //largeBoard = new QRadioButton("Start from scratch");


    // place radio buttons in vertical layout
    QVBoxLayout* radio_lay = new QVBoxLayout;
    radio_lay->addWidget(smallBoard);
    radio_lay->addWidget(mediumBoard);
    //radio_lay->addWidget(largeBoard);


    // add everything to the grid layout
    QGridLayout* grid_lay = new QGridLayout; //this will be the main layout for widget1
    grid_lay->addWidget(label_title,1,1,1,1,Qt::AlignCenter);
    grid_lay->addWidget(label_subtitle,2,1,1,1,Qt::AlignCenter);
    //grid_lay->addLayout(radio_lay,3,1,1,1,Qt::AlignCenter);
    grid_lay->addLayout(radio_lay,3,1,1,1,Qt::AlignCenter);
    grid_lay->addWidget(button_start,4,1,1,1,Qt::AlignCenter);
    grid_lay->addWidget(button_quit,5,1,1,1,Qt::AlignCenter);
    widget1->setLayout(grid_lay); // TRANSFERS OWNERSHIP OF THE WIDGETS IN 'gridLayout1' TO 'wid'

    this->setCentralWidget(widget1);

}


void MainWindow::setGameBoard(gameboard* game_board) {
    //QObject::connect(button_start, SIGNAL(clicked()), game_board, SLOT(clear_board()));
    QObject::connect( this->smallBoard, SIGNAL( clicked() ), game_board, SLOT(smallSlot()) );
    QObject::connect( this->mediumBoard, SIGNAL( clicked() ), game_board, SLOT(medSlot()) );
    //QObject::connect( this->largeBoard, SIGNAL( clicked() ), game_board, SLOT(largeSlot()) );
    QObject::connect(button_start, SIGNAL(clicked()), game_board, SLOT(show()));
}



MainWindow::~MainWindow()
{
    //delete ui;
}





