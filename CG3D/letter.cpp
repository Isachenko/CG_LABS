#include <QtGui>
#include <QtOpenGL>

#include "letter.h"

Letter::Letter(QWidget *parent)
    : QGLWidget(parent)
{


    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    setFixedSize(350, 350);
    //setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    moveX = 0;
    moveY = 0;
    moveZ = 0;

    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    rotationX = 0.0;
    rotationY = 0.0;
    rotationZ = 0.0;

    face = new GLfloat*[12];

    for (int i = 0; i < 12; i++){
        face[i] = new GLfloat[3];
    }


    initFace(face);

    back = new GLfloat*[12];

    for (int i = 0; i < 12; i++){
        back[i] = new GLfloat[3];
    }

    initBack(back);

    faceColors[0] = QColor(60, 125, 80);
    faceColors[1] = QColor(60, 0, 255);;
    faceColors[2] = QColor(255, 0, 50);
    faceColors[3] = QColor(0, 255, 60);

    this->autoFillBackground();
}


GLfloat ** Letter::initBack(GLfloat ** result){

    GLfloat p1[3] = { 0.0, 0.0, -2.0 };
    GLfloat p2[3] = { 2.0, 0.0, -2.0 };
    GLfloat p3[3] = { 2.0, 0.0, -2.0 };
    GLfloat p4[3] = { 4.0, 6.0, -2.0 };
    GLfloat p5[3] = { 4.0, 0.0, -2.0 };
    GLfloat p6[3] = { 6.0, 0.0, -2.0 };
    GLfloat p7[3] = { 6.0, 8.0, -2.0 };
    GLfloat p8[3] = { 4.0, 8.0, -2.0 };
    GLfloat p9[3] = { 4.0, 8.0, -2.0 };
    GLfloat p10[3] = { 2.0, 2.0, -2.0 };
    GLfloat p11[3] = { 2.0, 8.0, -2.0 };
    GLfloat p12[3] = { 0.0, 8.0, -2.0 };


    GLfloat * back[12] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12};


    //result = new GLfloat*[12];

    //result = face;
    for (int i = 0; i < 12; i++){
        //result[i] = new GLfloat[3];
        for (int j = 0; j < 3; j++){
            result[i][j] = back[i][j];
        }
    }

    return back;
}

void Letter::drawProjections()
{
    drawXYProjection();
}

void Letter::drawXYProjection()
{

}

void Letter::drawXZProjection()
{

}

void Letter::drawYZProjection()
{

}

void Letter::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Letter::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    //gluPerspective (50.0, 1, 1.0, 20.0);
    glOrtho(-10.0, +10.0, -7.0, +13.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void Letter::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void Letter::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void Letter::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

    if (event->buttons() & Qt::LeftButton) {
        rotationX -= 5 * dy;
        rotationY += 5 * dx;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        rotationX -= 5 * dy;
        rotationZ += 5 * dx;
        updateGL();
    }
    lastPos = event->pos();
}

void Letter::mouseDoubleClickEvent(QMouseEvent *event)
{
    int face = faceAtPosition(event->pos());
    if (face != -1) {
        QColor color = QColorDialog::getColor(faceColors[face], this);
        if (color.isValid()) {
            faceColors[face] = color;
            updateGL();
        }
    }
}

GLfloat **Letter::initFace(GLfloat ** result)
{
    GLfloat P1[3] = { 0.0, 0.0, 0.0 };
    GLfloat P2[3] = { 2.0, 0.0, 0.0 };
    GLfloat P3[3] = { 2.0, 0.0, 0.0 };
    GLfloat P4[3] = { 4.0, 6.0, 0.0 };
    GLfloat P5[3] = { 4.0, 0.0, 0.0 };
    GLfloat P6[3] = { 6.0, 0.0, 0.0 };
    GLfloat P7[3] = { 6.0, 8.0, 0.0 };
    GLfloat P8[3] = { 4.0, 8.0, 0.0 };
    GLfloat P9[3] = { 4.0, 8.0, 0.0 };
    GLfloat P10[3] = { 2.0, 2.0, 0.0 };
    GLfloat P11[3] = { 2.0, 8.0, 0.0 };
    GLfloat P12[3] = { 0.0, 8.0, 0.0 };


   GLfloat * face[12] = {P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12};

   //result = new GLfloat*[12];

   //result = face;
   for (int i = 0; i < 12; i++){
       //result[i] = new GLfloat[3];
       for (int j = 0; j < 3; j++){
           result[i][j] = face[i][j];
       }
   }

   return face;
}


void Letter::draw()
{
    //gluProject()
    GLfloat ** face1 = new GLfloat*[12];

    for (int i = 0; i < 12; i++){
        face1[i] = new GLfloat[3];
    }

    GLfloat ** back1 = new GLfloat*[12];

    for (int i = 0; i < 12; i++){
        back1[i] = new GLfloat[3];
    }


    for (int i = 0; i < 12; i++){
        face1[i][0] = face[i][0];
        face1[i][1] = face[i][1];
        face1[i][2] = face[i][2];
        back1[i][0] = back[i][0];
        back1[i][1] = back[i][1];
        back1[i][2] = back[i][2];
    }

    for (int i = 0; i < 12; i++){
        GLfloat x = face1[i][1];
        GLfloat y = face1[i][2];
        face1[i][1] = x * cos(rotationX) + y * sin(rotationX);
        face1[i][2] = -x * sin(rotationX) + y * cos(rotationX);



        x = back1[i][1];
        y = back1[i][2];
        back1[i][1] = x * cos(rotationX) + y * sin(rotationX);
        back1[i][2] = -x * sin(rotationX) + y * cos(rotationX);


        x = face1[i][0];
        y = face1[i][1];
        face1[i][0] = x * cos(rotationZ) + y * sin(rotationZ);
        face1[i][1] = -x * sin(rotationZ) + y * cos(rotationZ);


        x = back1[i][0];
        y = back1[i][1];
        back1[i][0] = x * cos(rotationZ) + y * sin(rotationZ);
        back1[i][1] = -x * sin(rotationZ) + y * cos(rotationZ);


        x = face1[i][0];
        y = face1[i][2];
        face1[i][0] = x * cos(rotationY) + y * sin(rotationY);
        face1[i][2] = -x * sin(rotationY) + y * cos(rotationY);


        x = back1[i][0];
        y = back1[i][2];
        back1[i][0] = x * cos(rotationY) + y * sin(rotationY);
        back1[i][2] = -x * sin(rotationY) + y * cos(rotationY);

    }

    for (int i = 0; i < 12; i++){
        face1[i][0] = (moveX + 3) + face1[i][0];
        face1[i][1] = (moveY + 3) + face1[i][1];
        face1[i][2] = (moveZ + 5) + face1[i][2];

        back1[i][0] = (moveX + 3) + back1[i][0];
        back1[i][1] = (moveY + 3) + back1[i][1];
        back1[i][2] = (moveZ + 5) + back1[i][2];
    }

    GLfloat * coords1[6][3] = {
        { face1[0], face1[1], face1[10] }, { face1[2], face1[8], face1[9] },
        {face1[2], face1[3], face1[8] }, { face1[4], face1[6], face1[7] },
        { face1[4], face1[5], face1[6] }, { face1[0], face1[10], face1[11] }
    };

    GLfloat * coords2[6][3] = {
        { back1[1], back1[0], back1[10] }, { back1[8], back1[2], back1[9] },
        { back1[3], back1[2], back1[8] }, { back1[6], back1[4], back1[7] },
        { back1[5], back1[4], back1[6] }, { back1[10], back1[0], back1[11] }
    };


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    gluLookAt(3.0, 1.0, 7.0, -1.0, -2.0, -1.0, 0.0, 1.0, 0.0);
    // DRAWiNG AXIS

    qglColor(QColor(25, 25, 25));
    glLineWidth(2.5);

        glBegin(GL_LINES);
        glVertex3f(0, 0, 0.0);
        glVertex3f(150, 0, 0);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(0, 0.0, 0.0);
        glVertex3f(0, 0, 150);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0);
        glVertex3f(0, 150, 0);
        glEnd();

    glScalef(scaleX, scaleY, scaleZ);
    glLineWidth(1);
    //gluLookAt(0,20,0, 0, 0, 0, 0, 1, 0);
    //glTranslatef((GLfloat)moveX, (GLfloat)moveY,(GLfloat) moveZ);
    glPushMatrix();
    //glRotatef(rotationX, 1.0, 0.0, 0.0);
    //glRotatef(rotationY, 0.0, 1.0, 0.0);
    //glRotatef(rotationZ, 0.0, 0.0, 1.0);

    qglColor(faceColors[2]);
    for (int i = 0; i < 6; ++i) {
        glLoadName(i);
        glBegin(GL_TRIANGLES);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(coords1[i][j][0], coords1[i][j][1],
                       coords1[i][j][2]);
        }
        glEnd();




        glLoadName(i + 6);
        glBegin(GL_POLYGON);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(coords2[i][j][0], coords2[i][j][1],
                       coords2[i][j][2]);
        }
        glEnd();
    }

    for (int i = 0; i < 12; i++){
        glLoadName(i + 12);

        glBegin(GL_POLYGON);
        glVertex3f(face1[i][0], face1[i][1], face1[i][2]);
        glVertex3f(back1[i][0], back1[i][1], back1[i][2]);
        glVertex3f(back1[(i + 1) % 12][0], back1[(i + 1) % 12][1], back1[(i + 1) % 12][2]);
        glVertex3f(face1[(i + 1) % 12][0], face1[(i + 1) % 12][1], face1[(i + 1) % 12][2]);
        glEnd();
    }




    qglColor(faceColors[0]);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    //*************************************************************
    // XY PROJECTION

    for (int i = 0; i < 6; ++i) {
        glLoadName(i * 90);
        glBegin(GL_TRIANGLES);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(coords1[i][j][0], coords1[i][j][1],
                       0);
        }
        glEnd();

        glLoadName(i + 60);
        glBegin(GL_POLYGON);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(coords2[i][j][0], coords2[i][j][1],
                       0);
        }
        glEnd();
    }

    for (int i = 0; i < 12; i++){
        glLoadName(i + 120);

        glBegin(GL_POLYGON);
        glVertex3f(face1[i][0], face1[i][1], 0);
        glVertex3f(back1[i][0], back1[i][1], 0);
        glVertex3f(back1[(i + 1) % 12][0], back1[(i + 1) % 12][1], 0);
        glVertex3f(face1[(i + 1) % 12][0], face1[(i + 1) % 12][1], 0);
        glEnd();
    }

    //glPopMatrix();
    //*************************************************************
    // XZ PROJECTION

    qglColor(faceColors[3]);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    for (int i = 0; i < 6; ++i) {
        glLoadName(i * 190);
        glBegin(GL_TRIANGLES);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(coords1[i][j][0], 0,
                       coords1[i][j][2]);
        }
        glEnd();

        glLoadName(i + 160);
        glBegin(GL_POLYGON);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(coords2[i][j][0], 0,
                       coords2[i][j][2]);
        }
        glEnd();
    }

    for (int i = 0; i < 12; i++){
        glLoadName(i + 220);

        glBegin(GL_POLYGON);
        glVertex3f(face1[i][0], 0, face1[i][2]);
        glVertex3f(back1[i][0], 0, back1[i][2]);
        glVertex3f(back1[(i + 1) % 12][0], 0, back1[(i + 1) % 12][2]);
        glVertex3f(face1[(i + 1) % 12][0], 0, face1[(i + 1) % 12][2]);
        glEnd();
    }


    //*************************************************************
    // YZ PROJECTION
    qglColor(faceColors[1]);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    for (int i = 0; i < 6; ++i) {
        glLoadName(i * 290);
        glBegin(GL_TRIANGLES);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(0, coords1[i][j][1],
                       coords1[i][j][2]);
        }
        glEnd();

        glLoadName(i + 260);
        glBegin(GL_POLYGON);

        for (int j = 0; j < 3; ++j) {
            glVertex3f(0, coords2[i][j][1],
                       coords2[i][j][2]);
        }
        glEnd();
    }

    for (int i = 0; i < 12; i++){
        glLoadName(i + 320);

        glBegin(GL_POLYGON);
        glVertex3f(0, face1[i][1], face1[i][2]);
        glVertex3f(0, back1[i][1], back1[i][2]);
        glVertex3f(0, back1[(i + 1) % 12][1], back1[(i + 1) % 12][2]);
        glVertex3f(0, face1[(i + 1) % 12][1], face1[(i + 1) % 12][2]);
        glEnd();
    }
    glPopMatrix();
}

int Letter::faceAtPosition(const QPoint &pos)
{
    const int MaxSize = 512;
    GLuint buffer[MaxSize];
    GLint viewport[4];

    makeCurrent();

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(GLdouble(pos.x()), GLdouble(viewport[3] - pos.y()),
                  5.0, 5.0, viewport);

    GLfloat x = GLfloat(width()) / height();
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}
GLint Letter::getMoveZ() const
{
    return moveZ;
}

void Letter::setMoveZ(const GLint &value)
{
    moveZ = value;
}

void Letter::changeXScale(GLfloat x)
{
    scaleX = x;
    //scaleY = zoom;
    //scaleZ = zoom;
}

void Letter::changeYScale(GLfloat y)
{
    scaleY = y;
}

void Letter::changeZScale(GLfloat z)
{
    scaleZ = z;
}

GLint Letter::getMoveY() const
{
    return moveY;
}

void Letter::setMoveY(const GLint &value)
{
    moveY = value;
}

GLint Letter::getMoveX() const
{
    return moveX;
}

void Letter::setMoveX(const GLint &value)
{
    moveX = value;
}

