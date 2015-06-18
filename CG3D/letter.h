#ifndef LETTER_H
#define LETTER_H

#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include <QColor>
#include <QGridLayout>
#include <QColorDialog>
#include <GL/glu.h>

class Letter : public QGLWidget
{
    Q_OBJECT
public:
    explicit Letter(QWidget *parent = 0);
    GLint getMoveX() const;
    void setMoveX(const GLint &value);

    GLint getMoveY() const;
    void setMoveY(const GLint &value);

    GLint getMoveZ() const;
    void setMoveZ(const GLint &value);

    void changeXScale(GLfloat x);

    void changeYScale(GLfloat y);

    void changeZScale(GLfloat z);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    GLfloat **initFace(GLfloat **);
    GLfloat ** initBack(GLfloat **);
    void drawProjections();
    void drawXYProjection();
    void drawXZProjection();
    void drawYZProjection();
    void drawAxis();
    void draw();
    int faceAtPosition(const QPoint &pos);

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;

    GLint moveX;
    GLint moveY;
    GLint moveZ;

    GLfloat scaleX;
    GLfloat scaleY;
    GLfloat scaleZ;

    QColor faceColors[4];
    QPoint lastPos;
    GLfloat ** face;
    GLfloat ** back;
signals:

public slots:

};

#endif // LETTER_H
