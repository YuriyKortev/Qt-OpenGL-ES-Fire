#include "fire.h"

Fire::Fire():nump(400000)
{
    GLuint a=nump*0.8f;
    GLuint b=nump-a;

    for(GLuint i=0;i<nump;i++){
        points.append(QVector3D(randFloat(-2.0,2.0f),-0.7f,0.0f));
    }
    for(GLuint i=0;i<b;i++){
        veloc.append(QVector3D(0.0f,randFloat(0.1f,1.4f),0.0f));
    }

    for(GLuint i=0;i<a;i++){
        veloc.append(QVector3D(0.0f,randFloat(0.3f,1.0f),0.0f));
    }

    for(GLuint i=0;i<nump;i++){
        w.append(randFloat());
    }
}

void Fire::drawFire(QOpenGLShaderProgram *m_program, float time)
{
    initializeOpenGLFunctions();

    m_program->bind();
    m_program->setUniformValue("time",time);

    GLuint m_posAttr = m_program->attributeLocation( "vertexAttr" );
    GLuint m_veloc = m_program->attributeLocation( "veloc" );
    GLuint m_w=m_program->attributeLocation("w");
    m_program->setAttributeArray( m_posAttr, points.data());
    m_program->setAttributeArray( m_veloc, veloc.data());
    m_program->setAttributeArray(m_w,w.data(),1);
    m_program->enableAttributeArray(m_w);
    m_program->enableAttributeArray( m_posAttr );
    m_program->enableAttributeArray( m_veloc );


    glEnable ( GL_ALPHA_TEST );
    glEnable(GL_BLEND);

     glDisable ( GL_DEPTH_TEST );
 //   glBlendFunc(GL_ONE,GL_ONE);
    glAlphaFunc(GL_LESS,0.9);
    glDrawArrays(GL_POINTS,0,points.size());
    glDisable ( GL_BLEND );



    m_program->disableAttributeArray( m_posAttr);
    m_program->disableAttributeArray( m_veloc );
    m_program->disableAttributeArray(m_w);
    m_program->release();
}

float Fire::randFloat()
{
    return rand () / (float) RAND_MAX;
}

float Fire::randFloat(float a, float b)
{
    return a + randFloat() * (b - a);
}
