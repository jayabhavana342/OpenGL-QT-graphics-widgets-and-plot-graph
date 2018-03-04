#include "control.h"

control::control()
{
    this->setWindowTitle("Assignment Application");

    textEdit = new QPlainTextEdit;
    glWidget =new glwidget;
    setCentralWidget(glWidget);

    createActions();
    createMenus();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);


    QDockWidget *dock = new QDockWidget("User Control's",this);
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

    //connect(dial_rs,SIGNAL(valueChanged(int)),
    //size
    label_sz = new QLabel(dock);
    label_sz->setText("<font color='blue'><center><u><b>Image Size</b></u><br><small>(50% - 150%)</small></center></font>");

    slider_sz = new QSlider(dock);
    slider_sz->setOrientation(Qt::Horizontal);
    slider_sz->setRange(50,150);
    slider_sz->setPalette(Qt::blue);

    lcd_sz = new QLCDNumber(dock);
    lcd_sz->setPalette(Qt::blue);

    hlayout_sz = new QHBoxLayout;
    hlayout_sz->addWidget(label_sz);
    hlayout_sz->addWidget(slider_sz);
    hlayout_sz->addWidget(lcd_sz);

    connect(slider_sz,SIGNAL(valueChanged(int)),lcd_sz,SLOT(display(int)));

    //Brightness
    label_b = new QLabel(dock);
    label_b->setText("<font color='blue'><center><u><b>Image Brightness</b></u><br><small>(0 - 255)</small></center></font>");

    slider_b = new QSlider(dock);
    slider_b->setOrientation(Qt::Horizontal);
    slider_b->setRange(0,255);
    slider_b->setPalette(Qt::blue);

    progressbar_b= new QProgressBar(dock);
    progressbar_b->setRange(0,255);
    progressbar_b->setPalette(Qt::blue);

    hlayout_b = new QHBoxLayout;
    hlayout_b->addWidget(label_b);
    hlayout_b->addWidget(slider_b);
    hlayout_b->addWidget(progressbar_b);

    connect(slider_b,SIGNAL(valueChanged(int)),progressbar_b,SLOT(setValue(int)));

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
    glWidget->scene='p';

    //color parameter

    label_cp= new QLabel(dock);
    label_cp->setText("<font color='blue'><center><u><b>Color Parameter</b></u></center></font>");
    combobox_cp_side = new QComboBox(dock);
    combobox_cp_side->addItem("Choose Side");
    combobox_cp_side->addItem("Side1");
    combobox_cp_side->addItem("Side2");
    combobox_cp_side->addItem("Side3");
    combobox_cp_side->addItem("Side4");
    combobox_cp_side->addItem("Side5");
    combobox_cp_side->addItem("Side6");

    combobox_cp_color = new QComboBox(dock);
    combobox_cp_color->addItem("Choose Color");
    combobox_cp_color->addItem("Red");
    combobox_cp_color->addItem("Green");
    combobox_cp_color->addItem("Blue");
    combobox_cp_color->addItem("Yellow");
    combobox_cp_color->addItem("White");
    combobox_cp_color->addItem("Pink");

    hlayout_cp = new QHBoxLayout;
    hlayout_cp->addWidget(label_cp);
    hlayout_cp->addWidget(combobox_cp_side);
    hlayout_cp->addWidget(combobox_cp_color);

    //colorrepresentation
    label_cr = new QLabel(dock);
    label_cr->setText("<font color='blue'><center><u><b>Color Representation</b></u></center></font>");
    buttongroup_cr = new QButtonGroup(dock);
    button_R= new QRadioButton();
    button_R->setText("R");
    button_S= new QRadioButton();
    button_S->setText("S");
    button_T= new QRadioButton();
    button_T->setText("T");
    button_U= new QRadioButton();
    button_U->setText("U");

    button_R->setChecked(true);

    lineedit_cr = new QLineEdit("R is selected!");
    connect(buttongroup_cr,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(settext_cp(QAbstractButton*)));


    buttongroup_cr->addButton(button_R);
    buttongroup_cr->addButton(button_S);
    buttongroup_cr->addButton(button_T);
    buttongroup_cr->addButton(button_U);

    hlayout_cr = new QHBoxLayout;
    hlayout_cr->addWidget(label_cr);
    hlayout_cr->addWidget(button_R);
    hlayout_cr->addWidget(button_S);
    hlayout_cr->addWidget(button_T);
    hlayout_cr->addWidget(button_U);

    vlayout_cr = new QVBoxLayout;
    vlayout_cr->addLayout(hlayout_cr);
    vlayout_cr->addWidget(lineedit_cr);

    vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout_rs);
    vlayout->addLayout(hlayout_sz);
    vlayout->addLayout(hlayout_b);
    vlayout->addLayout(vlayout_cr);
    vlayout->addLayout(hlayout_cp);
    vlayout->addLayout(vlayout_io);

    gbox->setLayout(vlayout);
    dock->setWidget(gbox);
}

control::~control()
{

}
void control::toggleView()
{
    if(pushbutton1_io->isChecked())
        glWidget->scene='p';
    else if(pushbutton2_io->isChecked())
        glWidget->scene='l';
    glWidget->updateGL();
}

void control::settext_cp(QAbstractButton * b)
{
    QString s = b->text();
    s.append(" is selected!");
    lineedit_cr->setText(s);
}

void control::settext_io(QAbstractButton * b)
{
    QString s = b->text();
    s.append(" mode Activated!!");
    lineedit_io->setText(s);

//    if(pushbutton1_io->isChecked())
//        glWidget->scene='p';
//    else if(pushbutton2_io->isChecked())
//        glWidget->scene='l';
//    glWidget->updateGL();

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
