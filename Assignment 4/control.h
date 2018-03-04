#ifndef CONTROL_H
#define CONTROL_H
#include "graph.h"
#include "cube.h"
#include <QWidget>
#include<QLabel>
#include<QDial>
#include<QLCDNumber>
#include<QHBoxLayout>
#include<QSlider>
#include<QProgressBar>
#include<QComboBox>
#include<QRadioButton>
#include<QButtonGroup>
#include<QPushButton>
#include<QMainWindow>
#include<QTextEdit>
#include<QGroupBox>
#include<QSpinBox>
#include<QAction>
#include<QActionGroup>
#include<QMenu>
#include<QPlainTextEdit>
#include<QPushButton>

class control : public QMainWindow
{
    Q_OBJECT
private slots:

    void toggleView();
    void toggleView_sz(int val);
    void toggleView_rs(int val);

    void toggleView_A(int val);
    void toggleView_phi(int val);
    void toggleView_r1(int val);
    void toggleView_r2(int val);
private:
    void createActions();
    void createMenus();

    QMenu *quitMenu;
    QAction *quitAct;

public slots:
    void settext_io(QAbstractButton*);
public:
    control();

    Cube *cube;
    Graph *g;

    QGroupBox *main_gbox;
    QVBoxLayout *main_lay;

    //window1

    QGroupBox *gbox;
    QVBoxLayout *vlayout;

    QLabel *label_rs;
    QDial *dial_rs;
    QLCDNumber *lcd_rs;

    QHBoxLayout *hlayout_rs;

    //size
    QLabel *label_sz;
    QSlider *slider_sz;
    QLCDNumber *lcd_sz;

    QHBoxLayout *hlayout_sz;

    //imageorientation
    QLabel *label_io;
    QButtonGroup *buttongroup_io;
    QRadioButton *pushbutton1_io;
    QRadioButton *pushbutton2_io;
    QLineEdit *lineedit_io;
    QHBoxLayout *hlayout_io;
    QVBoxLayout *vlayout_io;


    //window2

    QLabel *label_A;
    QSlider *slider_A;
    QLCDNumber *lcd_A;
    QHBoxLayout *hlayout_A;

    QLabel *label_phi;
    QSpinBox *spinbox_phi;
    QLabel *label_op_phi;
    QHBoxLayout *hlayout_phi;

    QLabel *label_x;
    QDial *d1_x;
    QDial *d2_x;
    QLabel *label_x_r1;
    QLabel *middle_x;
    QLabel *label_x_r2;
    QHBoxLayout *hlayout_x;

    QVBoxLayout *vlayout_graph;
    QGroupBox *gbox_graph;


    ~control();
};

#endif // CONTROL_H
