#ifndef SCENE_H
#define SCENE_H

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <vector>
#include <QMatrix4x4>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QtMath>

#include "fire.h"

struct Light{
    QVector4D light_pos;
    QVector3D la;
    QVector3D ld;
    QVector3D ls;
};

struct Material{
    QVector3D ka;
    QVector3D kd;
    QVector3D ks;
    float Shininess;
};

class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    Scene(QWidget* parent=0);


private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    QOpenGLShaderProgram* axes_shader;
    QOpenGLShaderProgram* fire_shader;


    GLuint m_frame;

    Fire* fire;

    GLfloat cam_angle;
    GLfloat cam_y;
    GLfloat cam_r;
    QPointF start;


};


#endif // SCENE_H
