#ifndef GRAPH_H
#define GRAPH_H

#include <QGLWidget>

class Graph : public QGLWidget
{

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public:
    Graph(QWidget *parent = 0);
    float A;
    float phi;
    float r1;
    float r2;
    void drawgraph();
    void set_A(float val);
    void set_phi(float val);
    void set_r1(float val);
    void set_r2(float val);
    ~Graph();
};

#endif // GRAPH_H
