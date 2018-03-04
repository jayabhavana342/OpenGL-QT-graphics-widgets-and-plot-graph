#include "control.h"
#include<QtWidgets>

control::control()
{
    this->setWindowTitle("Application");

    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);


    QDockWidget *dock1 = new QDockWidget("Rotation Speed",this);
    dock1->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea,dock1);

    //rotation speed
    gbox_rs = new QGroupBox(dock1);
    label_rs = new QLabel(dock1);
    label_rs->setText("<font color='blue'><center><u><b>Rotation Speed</b></u><br><small>(rotation's per second)</small></center></font>");

    dial_rs = new QDial(dock1);
    dial_rs->setPalette(Qt::blue);

    lcd_rs = new QLCDNumber(dock1);
    lcd_rs->setPalette(Qt::blue);

    hlayout_rs = new QHBoxLayout;

    layout_rs();
    connection_rs();

    gbox_rs->setLayout(hlayout_rs);
    dock1->setWidget(gbox_rs);

    QDockWidget *dock2 = new QDockWidget("Size and Brightness",this);
    dock2->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea,dock2);

    gbox_sz_b_io = new QGroupBox(dock2);
    //size
    label_sz = new QLabel(dock2);
    label_sz->setText("<font color='blue'><center><u><b>Image Size</b></u><br><small>(50% - 150%)</small></center></font>");

    slider_sz = new QSlider(dock2);
    slider_sz->setOrientation(Qt::Horizontal);
    slider_sz->setRange(50,150);
    slider_sz->setPalette(Qt::blue);

    lcd_sz = new QLCDNumber(dock2);
    lcd_sz->setPalette(Qt::blue);

    hlayout_sz = new QHBoxLayout;

    layout_sz();
    connection_sz();


    //Brightness
    label_b = new QLabel(dock2);
    label_b->setText("<font color='blue'><center><u><b>Image Brightness</b></u><br><small>(0 - 255)</small></center></font>");

    slider_b = new QSlider(dock2);
    slider_b->setOrientation(Qt::Horizontal);
    slider_b->setRange(0,255);
    slider_b->setPalette(Qt::blue);

    progressbar_b= new QProgressBar(dock2);
    progressbar_b->setRange(0,255);
    progressbar_b->setPalette(Qt::blue);


    hlayout_b = new QHBoxLayout;

    layout_b();
    connection_b();

    //imageorientation
    label_io = new QLabel(dock2);
    label_io->setText("<font color='blue'><center><u><b>Image Orientation</b></u></center></font>");


    pushbutton1_io = new QPushButton(dock2);
    pushbutton1_io->setText("Potrait");
    pushbutton2_io = new QPushButton(dock2);
    pushbutton2_io->setText("Landscape");


    hlayout_io = new QHBoxLayout;

    layout_io();

    vlayout_sz_b_io = new QVBoxLayout;
    vlayout_sz_b_io->addStretch(2);
    vlayout_sz_b_io->addLayout(hlayout_sz);
    vlayout_sz_b_io->addLayout(hlayout_b);
    vlayout_sz_b_io->addLayout(hlayout_io);
    vlayout_sz_b_io->addStretch(2);

    gbox_sz_b_io->setLayout(vlayout_sz_b_io);

    dock2->setWidget(gbox_sz_b_io);

    QDockWidget *dock3 = new QDockWidget("Color Parameter , Color Representation and Orientation",this);
    dock3->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dock3);


    //color parameter
    gbox_cp_cr = new QGroupBox(dock3);

    label_cp= new QLabel(dock3);
    label_cp->setText("<font color='blue'><center><u><b>Color Parameter</b></u></center></font>");
    combobox_cp_side = new QComboBox(dock3);
    combobox_cp_side->addItem("Choose Side");
    combobox_cp_side->addItem("Side1");
    combobox_cp_side->addItem("Side2");
    combobox_cp_side->addItem("Side3");
    combobox_cp_side->addItem("Side4");
    combobox_cp_side->addItem("Side5");
    combobox_cp_side->addItem("Side6");

    combobox_cp_color = new QComboBox(dock3);
    combobox_cp_color->addItem("Choose Color");
    combobox_cp_color->addItem("Red");
    combobox_cp_color->addItem("Green");
    combobox_cp_color->addItem("Blue");
    combobox_cp_color->addItem("Yellow");
    combobox_cp_color->addItem("White");
    combobox_cp_color->addItem("Pink");

    hlayout_cp = new QHBoxLayout;

    layout_cp();

    //colorrepresentation
    label_cr = new QLabel(dock3);
    label_cr->setText("<font color='blue'><center><u><b>Color Representation</b></u></center></font>");
    buttongroup_cr = new QButtonGroup(dock3);
    button_R= new QRadioButton();
    button_R->setText("R");
    button_S= new QRadioButton();
    button_S->setText("S");
    button_T= new QRadioButton();
    button_T->setText("T");
    button_U= new QRadioButton();
    button_U->setText("U");

    buttongroup_cr->addButton(button_R);
    buttongroup_cr->addButton(button_S);
    buttongroup_cr->addButton(button_T);
    buttongroup_cr->addButton(button_U);

    hlayout_cr = new QHBoxLayout;

    layout_cr();

    vlayout_cp_cr = new QVBoxLayout;
 vlayout_cp_cr->addStretch(2);
    vlayout_cp_cr->addLayout(hlayout_cp);
    vlayout_cp_cr->addLayout(hlayout_cr);
     vlayout_cp_cr->addStretch(2);
    gbox_cp_cr->setLayout(vlayout_cp_cr);
    dock3->setWidget(gbox_cp_cr);

}

control::~control()
{

}

void control::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void control::open()
{
    if (maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool control::save()
{
    if (curFile.isEmpty())
    {
        QFileDialog dialog(this);
        dialog.setWindowModality(Qt::WindowModal);
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.exec();
        QStringList files = dialog.selectedFiles();

        if (files.isEmpty())
            return false;

        return saveFile(files.at(0));
    }
    else
    {
        return saveFile(curFile);
    }
}


void control::help()
{
   QMessageBox::about(this, tr("Functionalities of Application:"),
                               tr("1.Creating 3 different Dock Wigets.\n"
                               "2.Creating Menu with File,Quit,Help items."));
}

void control::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}

void control::createActions()
{
    openAct = new QAction(QIcon("open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon("save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Exit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    helpAct = new QAction(tr("&Help"), this);
    helpAct->setStatusTip(tr("Show the application's help box"));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));
}

void control::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    quitMenu = menuBar()->addMenu(tr("&Quit"));
    quitMenu->addAction(quitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
}

void control::readSettings()
{
    QSettings settings("QtProject", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void control::writeSettings()
{
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool control::maybeSave()
{
    if (textEdit->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void control::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool control::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void control::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString control::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void control::layout_rs()
{
    hlayout_rs->addStretch(2);
    hlayout_rs->addWidget(label_rs);
    hlayout_rs->addWidget(dial_rs);
    hlayout_rs->addWidget(lcd_rs);
    hlayout_rs->addStretch(2);
}

void control::connection_rs()
{
    QObject::connect(dial_rs,SIGNAL(valueChanged(int)),lcd_rs,SLOT(display(int)));
}

void control::layout_sz()
{

    hlayout_sz->addWidget(label_sz);

    hlayout_sz->addWidget(slider_sz);
    hlayout_sz->addWidget(lcd_sz);

}

void control::connection_sz()
{
    QObject::connect(slider_sz,SIGNAL(valueChanged(int)),lcd_sz,SLOT(display(int)));
}

void control::layout_b()
{

    hlayout_b->addWidget(label_b);

    hlayout_b->addWidget(slider_b);
    hlayout_b->addWidget(progressbar_b);

}

void control::connection_b()
{
    QObject::connect(slider_b,SIGNAL(valueChanged(int)),progressbar_b,SLOT(setValue(int)));
}

void control::layout_cp()
{

    hlayout_cp->addWidget(label_cp);
    hlayout_cp->addWidget(combobox_cp_side);
    hlayout_cp->addWidget(combobox_cp_color);

}

void control::layout_cr()
{
    hlayout_cr->addWidget(label_cr);
    hlayout_cr->addWidget(button_R);
    hlayout_cr->addWidget(button_S);
    hlayout_cr->addWidget(button_T);
    hlayout_cr->addWidget(button_U);
}

void control::layout_io()
{

    hlayout_io->addWidget(label_io);

    hlayout_io->addWidget(pushbutton1_io);
    hlayout_io->addWidget(pushbutton2_io);

}
