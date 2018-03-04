#ifndef CONTROL_H
#define CONTROL_H

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

#include<QAction>
#include<QActionGroup>
#include<QMenu>
#include<QPlainTextEdit>

class control : public QMainWindow
{
    Q_OBJECT
private slots:
    void open();
    bool save();
    void help();
    void documentWasModified();

    void toggleView();
    void toggleView_sz(int val);
    void toggleView_rs(int val);
private:
    void createActions();
    void createMenus();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QPlainTextEdit *textEdit;
    QString curFile;

    QMenu *fileMenu;
    QMenu *quitMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *quitAct;
    QAction *helpAct;

public slots:
    void settext_cp(QAbstractButton*);
    void settext_io(QAbstractButton*);
public:
    control();

    Cube *cube;

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

    //brightness
    QLabel *label_b;
    QSlider *slider_b;
    QProgressBar *progressbar_b;

    QHBoxLayout *hlayout_b;

    //imageorientation
    QLabel *label_io;
    QButtonGroup *buttongroup_io;
    QRadioButton *pushbutton1_io;
    QRadioButton *pushbutton2_io;
    QLineEdit *lineedit_io;
    QHBoxLayout *hlayout_io;
    QVBoxLayout *vlayout_io;


    //colorparameter
    QLabel *label_cp;
    QComboBox *combobox_cp_color;
    QComboBox *combobox_cp_side;

    QHBoxLayout *hlayout_cp;

    //colorrepresentation
    QLabel *label_cr;
    QButtonGroup *buttongroup_cr;
    QRadioButton *button_R;
    QRadioButton *button_S;
    QRadioButton *button_T;
    QRadioButton *button_U;

    QLineEdit *lineedit_cr;

    QHBoxLayout *hlayout_cr;
    QVBoxLayout *vlayout_cr;


    ~control();
};

#endif // CONTROL_H
