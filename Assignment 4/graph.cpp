#include "graph.h"
#include"math.h"

Graph::Graph(QWidget *parent)
    : QGLWidget(parent)
{
    A=0.0;
    phi=0.0;
    r1=-1.0;
    r2=1.0;
}

Graph::~Graph()
{

}

void Graph::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Graph::resizeGL( int w, int h )
{
    if(w>h)
        glViewport((w-h)/2, 3, h, h);
    else
        glViewport(3, (h-w)/2, w, w);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(-1.0,0.0);
    glVertex2f(1.0,0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(0.0,-1.0);
    glVertex2f(0.0,1.0);
    glEnd();

    drawgraph();
    glFlush();
}
void Graph::drawgraph()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,1.0,0.0);
    glLineWidth(0.8);
    for(GLfloat x = r1;x<r2;x+=0.1)
    {
          glVertex2f(x,A*(cos((2*3.14159*x)+phi)));
    }
    glEnd();

}

void Graph::set_A(float val)
{
    A=val/10.0;
    paintGL();
    updateGL();
}

void Graph::set_phi(float val)
{
    phi = val;
    paintGL();
    updateGL();
}

void Graph::set_r1(float val)
{
    r1=val;
    paintGL();
    updateGL();
}

void Graph::set_r2(float val)
{
    r2=val;
    paintGL();
    updateGL();
}
