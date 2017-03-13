// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#include "widgetopengl.h"
#include <iostream>
#include <QDebug>
#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions_3_3_Core()
{
    m_programme = new QOpenGLShaderProgram(this);
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject(this);
    m_angleY = 0;
    m_timer = new QTimer();
    m_angleX =(30,0,0);
    m_angleZ = (30,0,0);
    lastPos.operator *=(0);
}

WidgetOpenGL::~WidgetOpenGL()
{
    m_programme->removeAllShaders();
    delete m_programme;
    delete m_vbo;
    delete m_vao;
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.8f,0.8f,0.8f,1.0f);  //gris clair
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));//Mardi Axel
   // m_timer->start();//Idem
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initializeShader();
    initializeVAO();
}

void WidgetOpenGL::initializeShader()
{
    bool resultat;

    m_programme->create();

    //Vertex Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Fragment Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Link
    resultat = m_programme->link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(m_programme->log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    m_programme->release();
}

void WidgetOpenGL::initializeVAO()
{


    glm::vec3 A(0,0,1),
            B(1,0,1),
            C(1,1,1),
            D(0,1,1),
            E(0,0,0),
            F(1,0,0),
            G(1,1,0),
            H(0,1,0);
    glm::vec3 rouge(1,0,0),
            vert(0,1,0),
            bleu(0,0,1),
            magenta(1,0,1),
            cyan(0,1,1),
            jaune(1,1,0);


    //Tableau des données : 3 sommets puis 3 couleurs
    glm::vec3 vertex_data[] = {
        A,B,C,D,//face avanGt
        B,F,G,C,
        F,E,H,G,
        E,A,D,H,
        D,C,G,H,
        E,F,B,A,
        rouge,rouge,rouge,rouge,
        magenta,magenta,magenta,magenta,
        jaune,jaune,jaune,jaune,
        vert,vert,vert,vert,
        bleu,bleu,bleu,bleu,
        cyan,cyan,cyan,cyan
        //1.0f, 0.0f, 0.0f,//droite
        //0.0f, 1.0f, 0.0f,//haut
        //-1.0f, 0.0f, 0.0f,//gauche
        //1.0f, 0.0f, 0.0f,//rouge
        //0.0f, 1.0f, 0.0f,//vert
        //0.0f, 0.0f, 1.0f//bleu
    };

    //creation du VA0 et du VBO
    m_vao->create();
    m_vbo->create();

    //Lien du VAO
    m_vao->bind();

        //lien du VBO
        m_vbo->bind();

        //Ecriture des données dans le VBO
        m_vbo->allocate(vertex_data,sizeof(vertex_data));
        m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

        //Lien entre VBO et les variables d'attribut du vertex shader
        m_programme->bind();
            m_programme->setAttributeArray(0, GL_FLOAT, BUFFER_OFFSET(0),3);
            m_programme->setAttributeArray(1, GL_FLOAT, BUFFER_OFFSET(24*sizeof(glm::vec3)),3);

            //Activation des attributs
            m_programme->enableAttributeArray(0);
            m_programme->enableAttributeArray(1);
        m_programme->release();

        //Liberation
        m_vbo->release();
    m_vao->release();

}



void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glm::mat4 proj = glm::perspective(glm::radians(fov), 1.33f, 0.1f, 100.0f);
    glm::mat4 vue = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -4));
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, 0.2f, glm::vec3(1,0,0));
    //model = glm::rotate(model, 0.4f, glm::vec3(0,1,0));
    model = glm::rotate(model, m_angleY, glm::vec3(0,1,0)); //Test
    model = glm::rotate(model, m_angleX, glm::vec3(1,0,0));

    model = glm::translate(model,glm::vec3(-0.5f,-0.5f,-0.5f));
    m_matrix = proj * vue * model;
    m_matrix = glm::transpose(m_matrix);

    m_programme->bind();
   // u_opacity = 0.5;
    m_programme->setUniformValue("u_opacity",u_opacity);
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", QMatrix4x4(glm::value_ptr(m_matrix)));

    m_vao->bind();

        //glDrawArrays(GL_TRIANGLES, 0, 24);
    for(int i = 0; i < 6; i++)
    {
       glDrawArrays(GL_TRIANGLE_FAN,4*i,4);
    }


    m_vao->release();
    m_programme->release();
}


void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

void WidgetOpenGL::update(){
    m_angleY = m_angleY + 0.008;
    m_angleX = m_angleX + 0.002;
    QOpenGLWidget::update();
}

void WidgetOpenGL::mousePressEvent(QMouseEvent *event){
    qDebug() << "Presse";
     QPoint currentPos = event->pos();
     lastPos = currentPos;
     //qDebug() << lastPos.x();
    // printf(currentPos.x());
}

void WidgetOpenGL::mouseMoveEvent(QMouseEvent *event){
    float dx = ((float)event->x() - lastPos.x())/width();
    float dy =  ((float)event->y() - lastPos.y())/height();
    //printf("Souris qui bouge");
    if (event->buttons() & Qt::LeftButton) {

        qDebug() << "Souris qui bouge" ;
        m_angleX += dy * 10;
        m_angleY += dx * 10;
        qDebug() << m_angleX;
        qDebug() << m_angleY;
        QOpenGLWidget::update();

        lastPos = event->pos();
        }
    if (event->buttons() & Qt::RightButton) {

        qDebug() << "Souris qui bouge" ;
        m_angleX += dx * 10;
        m_angleY += dy * 10;
        qDebug() << m_angleX;
        qDebug() << m_angleY;
        QOpenGLWidget::update();

        lastPos = event->pos();
        }

    }
void WidgetOpenGL:: startAnimation(){
    if(m_timer->isActive()){
        m_timer->stop();
    }else{
        m_timer->start(0.5);
    }
}

void WidgetOpenGL::changeFov(int value){
fov =value;
QOpenGLWidget::update();

}
void WidgetOpenGL::changeAlpha(int value){
    u_opacity =  (value)*0.01;
    qDebug() << (value)*0.01;
    QOpenGLWidget::update();
}


