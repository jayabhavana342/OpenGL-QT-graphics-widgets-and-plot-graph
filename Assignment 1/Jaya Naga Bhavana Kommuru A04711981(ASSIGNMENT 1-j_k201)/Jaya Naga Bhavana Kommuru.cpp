//Jaya Naga Bhavana Kommuru (A04711981) ,NetID:j_k201
#include<QtGui>
#include<QApplication>
#include<QRadioButton>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QApplication>
#include<QDial>
#include<QSlider>
#include<QLineEdit>
#include<QSpinBox>
#include<QComboBox>
#include<QButtonGroup>
#include<QLabel>
#include<QLCDNumber>
#include<QPalette>
#include<QProgressBar>
#include<QAbstractButton>
#include<QPushButton>
#include<QFont>

int main(int argc,char *argv[])
{

    QApplication app(argc,argv);

    QWidget *window = new QWidget;
    window->setWindowTitle("Image Control's");

	//labels for each ANIMATION CONTROL COMPONENT.
	//"rotate_label" for ROTATION SPEED.
	//"size_label" for IMAGE SIZE.
	//"brightness_label" for IMAGE BRIGHTNESS.
	//"colorParameter_label" for COLOR.
	//"colorRepresentation_label" for COLOR REPRESENTATION METHOD.
	//"imageOrientation_label" for IMAGE ORIENTATION.
    QLabel *rotate_label= new QLabel("<center><u><b>Rotation Speed</b></u><br><small>(rotation's per second)</small></center>");
    QLabel *size_label= new QLabel("<center><u><b>Image Size</b></u><br><small>(50% - 150%)</small></center>");
    QLabel *brightness_label= new QLabel("<center><u><b>Image Brightness</b></u><br><small>(0 - 255)</small></center>");
    QLabel *colorParameter_label= new QLabel("<center><u><b>Color Parameter</b></u></center>");
    QLabel *colorRepresentation_label= new QLabel("<center><u><b>Color Representation</b></u></center>");
    QLabel *imageOrientation_label= new QLabel("<center><u><b>Image Orientation</b></u></center>");

    //INPUT WIDGETS
	QDial *dial = new QDial;
    dial->setFocusPolicy(Qt::StrongFocus);
	 
    QSpinBox *spinbox = new QSpinBox;
    spinbox->setRange(50,150);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0,255);

    QComboBox *combobox = new QComboBox;
    combobox->insertItem(0,"Potrait");
    combobox->insertItem(2,"Landscape");

    QButtonGroup *buttongroup = new QButtonGroup();
    QRadioButton *button_R= new QRadioButton();
    button_R->setText("R");
    QRadioButton *button_S= new QRadioButton();
    button_S->setText("S");
    QRadioButton *button_T= new QRadioButton();
    button_T->setText("T");
    QRadioButton *button_U= new QRadioButton();
    button_U->setText("U");

    buttongroup->addButton(button_R);
    buttongroup->addButton(button_S);
    buttongroup->addButton(button_T);
    buttongroup->addButton(button_U);

    QLineEdit *lineedit = new QLineEdit;


    //OUTPUT WIDGETS
    QLCDNumber *lcd = new QLCDNumber();
    lcd->setSegmentStyle(QLCDNumber::Flat);

    QProgressBar *progressbar = new QProgressBar;
    progressbar->setRange(50,150);

    QLabel *new_brightness_label = new QLabel;

    QLabel *text = new QLabel;
    QPalette *new_text = new QPalette;
    new_text->setColor(QPalette::WindowText,Qt::red);
    text->setPalette(*new_text);

    QLabel *label_colorrep = new QLabel("R is Selected");
    QPushButton *button = new QPushButton("ok");

    QLabel *combo_label = new QLabel;
    QFont *font1 = new QFont("Courier New");
    font1->setItalic(true);
    combo_label->setFont(*font1);
    combo_label->setAlignment(Qt::AlignCenter);
    QPalette *p = new QPalette;
    p->setColor(QPalette::Background,Qt::yellow);
    combo_label->setPalette(*p);

	//The QDial widget is connected to QLCDNumber widget.
	//Here when the value of QDial is changed simultaniously the number is displayed on the QLCDNumber widget.
    QGridLayout *rotate_layout = new QGridLayout;
    rotate_layout->addWidget(rotate_label);
    rotate_layout->addWidget(dial);
    rotate_layout->addWidget(lcd);
    QObject::connect(dial,SIGNAL(valueChanged(int)),lcd,SLOT(display(int)));

	//The QSpinBox widget is connected to QProgressBar widget.
	//Here as the value of spinbox is increased or decreased simultaneously the value of the progressbar changes.
    QGridLayout *size_layout = new QGridLayout;
    size_layout->addWidget(size_label);
    size_layout->addWidget(spinbox);
    size_layout->addWidget(progressbar);
    QObject::connect(spinbox,SIGNAL(valueChanged(int)),progressbar,SLOT(setValue(int)));

	//The QSlider widget is connected to QLabel widget.
	//Here as the value of slider is changed the value is displayed on the label.
    QGridLayout *brightness_layout = new QGridLayout;
    brightness_layout->addWidget(brightness_label);
    brightness_layout->addWidget(slider);
    brightness_layout->addWidget(new_brightness_label);
    QObject::connect(slider,SIGNAL(valueChanged(int)),new_brightness_label,SLOT(setNum(int)));

	//The QLineEdit widget is connected to the QLabel widget.
	//Here as the text in the lineedit is changed by the user simultaneously it is displayed on the label with font color as red.
    QGridLayout *colorparameter_layout = new QGridLayout;
    colorparameter_layout->addWidget(colorParameter_label);
    colorparameter_layout->addWidget(lineedit);
    colorparameter_layout->addWidget(text);
    QObject::connect(lineedit,SIGNAL(textChanged(QString)),text,SLOT(setText(QString)));

	//The QButtonGroup widgets are displayed so as to represent various color representation methods.
    QVBoxLayout *colorrepresentation_layout = new QVBoxLayout;
    colorrepresentation_layout->addWidget(colorRepresentation_label);
    QHBoxLayout *colorrepresentation_layout_buttons = new QHBoxLayout;
    colorrepresentation_layout_buttons ->addWidget(button_R);
    colorrepresentation_layout_buttons ->addWidget(button_S);
    colorrepresentation_layout_buttons ->addWidget(button_T);
    colorrepresentation_layout_buttons ->addWidget(button_U);
    colorrepresentation_layout->addLayout(colorrepresentation_layout_buttons);
    colorrepresentation_layout->addWidget(label_colorrep);
//    QObject::connect(button_R,SIGNAL(clicked()),button,SLOT(showtext()));

	//The QComboBox is used so as to show the various options for the image orientation such as "Potrait" and "Landscape".
    //Here the combobox is connected to combo_label to display the text in Italic.
    QGridLayout *imageorientation_layout = new QGridLayout;
    imageorientation_layout->addWidget(imageOrientation_label);
    imageorientation_layout->addWidget(combobox);
    imageorientation_layout->addWidget(combo_label);
    QObject::connect(combobox,SIGNAL(currentIndexChanged(QString)),combo_label,SLOT(setText(QString)));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(rotate_layout);
    layout->addLayout(size_layout);
    layout->addLayout(brightness_layout);
    layout->addLayout(colorparameter_layout);
    layout->addLayout(colorrepresentation_layout);
    layout->addLayout(imageorientation_layout);

    window->setLayout(layout);

    window->show();
    return app.exec();

}
