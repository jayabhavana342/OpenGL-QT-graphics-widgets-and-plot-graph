#ifndef CONTROL_H
#define CONTROL_H

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
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void open();
    bool save();
    void help();
    void documentWasModified();
private:
    void createActions();
    void createMenus();
    void readSettings();
    void writeSettings();
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
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *quitAct;
    QAction *helpAct;

public:
    control();

    QGroupBox *gbox_rs;
    QLabel *label_rs;
    QDial *dial_rs;
    QLCDNumber *lcd_rs;

    QHBoxLayout *hlayout_rs;

    void layout_rs();
    void connection_rs();

    QGroupBox *gbox_sz_b_io;
    //size
    QLabel *label_sz;
    QSlider *slider_sz;
    QLCDNumber *lcd_sz;


    QHBoxLayout *hlayout_sz;

    void layout_sz();
    void connection_sz();

    //brightness
    QLabel *label_b;
    QSlider *slider_b;
    QProgressBar *progressbar_b;


    QHBoxLayout *hlayout_b;

    void layout_b();
    void connection_b();

    //imageorientation
    QLabel *label_io;
    QPushButton *pushbutton1_io;
    QPushButton *pushbutton2_io;


    QHBoxLayout *hlayout_io;

    void layout_io();

    QVBoxLayout *vlayout_sz_b_io;

    QGroupBox *gbox_cp_cr;

    //colorparameter
    QLabel *label_cp;
    QComboBox *combobox_cp_color;
    QComboBox *combobox_cp_side;


    QHBoxLayout *hlayout_cp;

    void layout_cp();

    //colorrepresentation
    QLabel *label_cr;
    QButtonGroup *buttongroup_cr;
    QRadioButton *button_R;
    QRadioButton *button_S;
    QRadioButton *button_T;
    QRadioButton *button_U;


    QHBoxLayout *hlayout_cr;

    void layout_cr();

    QVBoxLayout *vlayout_cp_cr;

    ~control();
};

#endif // CONTROL_H
