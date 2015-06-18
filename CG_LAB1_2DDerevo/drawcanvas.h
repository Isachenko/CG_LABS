#ifndef DRAWCANVAS_H
#define DRAWCANVAS_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector>
#include <QPointF>

#include <d2tree.h>

class DrawCanvas : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit DrawCanvas(QWidget *parent = 0);
    ~DrawCanvas();

private:
    D2Tree* _points = NULL;
    void paintEvent(QPaintEvent*);
    QRectF _rect;
    bool _rectCreated = false;

    bool isMousePressed = false;
    QPointF pressedPos;

public:
    void setPointsToDraw(QVector<QPointF> &points);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    void eraseRect();

signals:

public slots:
};

#endif // DRAWCANVAS_H
