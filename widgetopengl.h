// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#ifndef WIDGETOPENGL_H
#define WIDGETOPENGL_H

#include <QtGui>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include <glm-0.9.8.3/glm/mat4x4.hpp>
#include <glm-0.9.8.3/glm/vec3.hpp>
#include <glm-0.9.8.3/glm/trigonometric.hpp>
#include <glm-0.9.8.3/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.3/glm/gtc/type_ptr.hpp>

class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
    QPoint lastPos;

private slots:
    void update();
    void startAnimation();
    void changeFov(int value);
    void changeAlpha(int value);


public:
    WidgetOpenGL(QWidget* parent = 0);
    ~WidgetOpenGL();
    float fov;
    float u_opacity;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void setNoir();
    void initializeVAO();
    void initializeShader();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLShaderProgram* m_programme;
    QTimer* m_timer;
    GLfloat m_angleY;
    GLfloat m_angleX;
    GLfloat m_angleZ;

    glm::mat4 m_matrix;    //matrice de placement
};

#endif // WIDGETOPENGL_H
