#include "scene.h"
#include <QtMath>

Scene::Scene(QWidget* parent)
    :QOpenGLWidget(parent)
{
    fire=new Fire;

    cam_y=0.0f;
    cam_angle=90.0f;
    cam_r=1.0f;
}


void Scene::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.9f,0.9f,0.9f,0.3f);

    glEnable(GL_PROGRAM_POINT_SIZE);


    axes_shader=new QOpenGLShaderProgram;
    axes_shader->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader.glsl");
    axes_shader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader.glsl");
    axes_shader->link();

    fire_shader=new QOpenGLShaderProgram;
    fire_shader->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader_spline.glsl");
    fire_shader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader_spline.glsl");
    fire_shader->link();
}

void Scene::resizeGL(int w, int h){
    glViewport(0,0,w,h);

}

void Scene::paintGL(){

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_COLOR_BUFFER_BIT);


    QMatrix4x4 matrix, projection;
    QVector3D cam={this->cam_r*cosf(qDegreesToRadians(this->cam_angle)),this->cam_y,this->cam_r*sinf(qDegreesToRadians(this->cam_angle))};



    projection.perspective(70.0f, 2300.0f/1080.0f, 0.1f, 100.0f);


    matrix.lookAt(cam,{0.0f,0.0f,0.0f},{0,1,0});



    fire_shader->bind();
    fire_shader->setUniformValue("modelview",matrix);
    fire_shader->setUniformValue("matrix",projection*matrix);
    fire_shader->release();

    fire->drawFire(fire_shader, m_frame/2);




    ++m_frame;
    update();

}


