#include "control.h"

control::control()
{
    this->setWindowTitle("Assignment Application");

    g = new Graph(this);
    cube = new Cube(this);

    main_gbox = new QGroupBox();
    main_lay = new QVBoxLayout();

    main_lay->addWidget(cube);
    main_lay->addWidget(g);

    main_gbox->setLayout(main_lay);

    setCentralWidget(main_gbox);

    createActions();
    createMenus();

    QDockWidget *dock = new QDockWidget("Window 1-User Control's",this);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea|Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea,dock);

    //rotation speed
    gbox = new QGroupBox(dock);
    label_rs = new QLabel(dock);
    label_rs->setText("<font color='blue'><center><u><b>Rotation Speed</b></u><br><small>(rotation's per second)</small></center></font>");

    dial_rs = new QDial(dock);
    dial_rs->setPalette(Qt::blue);

    lcd_rs = new QLCDNumber(dock);
    lcd_rs->setPalette(Qt::blue);

    hlayout_rs = new QHBoxLayout;
    hlayout_rs->addWidget(label_rs);
    hlayout_rs->addWidget(dial_rs);
    hlayout_rs->addWidget(lcd_rs);

    connect(dial_rs,SIGNAL(valueChanged(int)),lcd_rs,SLOT(display(int)));
    connect(dial_rs,SIGNAL(valueChanged(int)),this,SLOT(toggleView_rs(int)));
    //size
    label_sz = new QLabel(dock);
    label_sz->setText("<font color='blue'><center><u><b>Image Size</b></u><br><small>(50% - 150%)</small></center></font>");

    slider_sz = new QSlider(dock);
    slider_sz->setOrientation(Qt::Horizontal);
    slider_sz->setRange(0,20);
    slider_sz->setPalette(Qt::blue);

    lcd_sz = new QLCDNumber(dock);
    lcd_sz->setPalette(Qt::blue);

    hlayout_sz = new QHBoxLayout;
    hlayout_sz->addWidget(label_sz);
    hlayout_sz->addWidget(slider_sz);
    hlayout_sz->addWidget(lcd_sz);

    connect(slider_sz,SIGNAL(valueChanged(int)),lcd_sz,SLOT(display(int)));
    connect(slider_sz,SIGNAL(valueChanged(int)),this,SLOT(toggleView_sz(int)));

    //imageorientation
    label_io = new QLabel(dock);
    label_io->setText("<font color='blue'><center><u><b>Image Orientation</b></u></center></font>");

    pushbutton1_io = new QRadioButton(dock);
    pushbutton1_io->setText("Potrait");
    pushbutton2_io = new QRadioButton(dock);
    pushbutton2_io->setText("Landscape");

    buttongroup_io = new QButtonGroup(dock);
    buttongroup_io->addButton(pushbutton1_io);
    buttongroup_io->addButton(pushbutton2_io);
    lineedit_io = new QLineEdit("Potrait mode Activated!!");
    connect(buttongroup_io,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(settext_io(QAbstractButton*)));
    pushbutton1_io->setChecked(true);
    hlayout_io = new QHBoxLayout;
    vlayout_io = new QVBoxLayout;
    hlayout_io->addWidget(label_io);
    hlayout_io->addWidget(pushbutton1_io);
    hlayout_io->addWidget(pushbutton2_io);
    vlayout_io->addLayout(hlayout_io);
    vlayout_io->addWidget(lineedit_io,Qt::RightToLeft);

    connect(pushbutton1_io,SIGNAL(clicked()),this,SLOT(toggleView()));
    connect(pushbutton2_io,SIGNAL(clicked()),this,SLOT(toggleView()));
    pushbutton1_io->click();
    cube->orient('p');

    vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout_rs);
    vlayout->addLayout(hlayout_sz);
    vlayout->addLayout(vlayout_io);

    gbox->setLayout(vlayout);
    dock->setWidget(gbox);

    //window2
    QDockWidget *dock1 =new QDockWidget("Window 2-Parameter's",this);
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea,dock1);

    label_A = new QLabel(dock1);
    label_A->setText("<font color = 'blue'><b><u>A value:</u></b></font>");
    label_A->setPalette(Qt::blue);

    slider_A = new QSlider(dock1);
    slider_A->setOrientation(Qt::Horizontal);
    slider_A->setRange(0,10);

    lcd_A = new QLCDNumber(dock);
    lcd_A->setPalette(Qt::blue);

    hlayout_A = new QHBoxLayout;
    hlayout_A->addWidget(label_A);
    hlayout_A->addWidget(slider_A);
    hlayout_A->addWidget(lcd_A);

    connect(slider_A,SIGNAL(valueChanged(int)),lcd_A,SLOT(display(int)));
    connect(slider_A,SIGNAL(valueChanged(int)),this,SLOT(toggleView_A(int)));

    label_phi = new QLabel(dock1);
    label_phi->setText("<font color = 'blue'><b><u>Phi value in degree's</u></b></font>");
    label_phi->setPalette(Qt::blue);

    spinbox_phi = new QSpinBox(dock1);
    spinbox_phi->setPalette(Qt::blue);
    spinbox_phi->setRange(0,360);

    label_op_phi = new QLabel(dock1);
    label_op_phi->setPalette(Qt::blue);

    hlayout_phi = new QHBoxLayout;
    hlayout_phi->addWidget(label_phi);
    hlayout_phi->addWidget(spinbox_phi);
    hlayout_phi->addWidget(label_op_phi);

    connect(spinbox_phi,SIGNAL(valueChanged(int)),label_op_phi,SLOT(setNum(int)));
    connect(spinbox_phi,SIGNAL(valueChanged(int)),this,SLOT(toggleView_phi(int)));

    label_x = new QLabel(dock1);
    label_x->setText("<font color = 'blue'><u><b>Range for x:</b></u></font>");
    d1_x = new QDial(dock1);
    d1_x->setRange(-10,0);
    d1_x->setPalette(Qt::blue);
    d2_x = new QDial(dock1);
    d2_x->setRange(0,10);
    d2_x->setPalette(Qt::blue);

    label_x_r1 = new QLabel(dock1);
    middle_x = new QLabel(dock1);
    middle_x->setText(" to ");
    label_x_r2 = new QLabel(dock1);

    connect(d1_x,SIGNAL(valueChanged(int)),label_x_r1,SLOT(setNum(int)));
    connect(d2_x,SIGNAL(valueChanged(int)),label_x_r2,SLOT(setNum(int)));

    connect(d1_x,SIGNAL(valueChanged(int)),this,SLOT(toggleView_r1(int)));
    connect(d2_x,SIGNAL(valueChanged(int)),this,SLOT(toggleView_r2(int)));

    hlayout_x = new QHBoxLayout;

    hlayout_x->addWidget(label_x);
    hlayout_x->addWidget(d1_x);
    hlayout_x->addWidget(d2_x);
    hlayout_x->addWidget(label_x_r1);
    hlayout_x->addWidget(middle_x);
    hlayout_x->addWidget(label_x_r2);

    vlayout_graph = new QVBoxLayout;

    vlayout_graph->addLayout(hlayout_x);
    vlayout_graph->addLayout(hlayout_A);
    vlayout_graph->addLayout(hlayout_phi);

    gbox_graph = new QGroupBox;
    gbox_graph->setLayout(vlayout_graph);
    dock1->setWidget(gbox_graph);
}

control::~control()
{

}
void control::toggleView()
{
    if(pushbutton1_io->isChecked())
        cube->orient('p');
    else if(pushbutton2_io->isChecked())
        cube->orient('l');
    cube->updateGL();
}

void control::toggleView_sz(int val)
{
    cube->Scale(val);
}

void control::toggleView_rs(int val)
{

        cube->rotate(val);

}

void control::toggleView_A(int val)
{
    float x = (float)val;
    g->set_A(x);
}

void control::toggleView_phi(int val)
{
    float x = ((val*3.14159))/180.0;
    g->set_phi(x);
}

void control::toggleView_r1(int val)
{
    float x = (float)val/10.0;
    g->set_r1(x);
}

void control::toggleView_r2(int val)
{
    float x = (float)val/10.0;
    g->set_r2(x);
}

//void control::toggleView_b(bool x)
//{
//    g->display(x);
//}

void control::settext_io(QAbstractButton * b)
{
    QString s = b->text();
    s.append(" mode Activated!!");
    lineedit_io->setText(s);
}

void control::createActions()
{

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Exit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void control::createMenus()
{
    quitMenu = menuBar()->addMenu(tr("&Quit"));
    quitMenu->addAction(quitAct);
}

