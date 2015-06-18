#include "drawcanvas.h"
#include <QPainter>
#include <QMouseEvent>

DrawCanvas::DrawCanvas(QWidget *parent) : QOpenGLWidget(parent)
{
}

DrawCanvas::~DrawCanvas()
{

}

void DrawCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(Qt::AlphaDither_Mask)));
    QPen p;
    p.setWidth(5);
    p.setColor(Qt::red);
    painter.setPen(p);
    if (_rectCreated) {
        painter.fillRect(_rect, Qt::blue);

        QVector<QPointF> pointToDrow = _points->getPointsInRect(_rect);
        foreach(const QPointF &point, pointToDrow) {
            painter.drawPoint(point);
        }
    }
    painter.end();


}

void DrawCanvas::setPointsToDraw(QVector<QPointF> &points)
{
    _points = new D2Tree(points);
}

void DrawCanvas::mousePressEvent(QMouseEvent *event)
{
    pressedPos = event->pos();
    this->isMousePressed = true;
    if (!_rectCreated) {
        _rect.setTopLeft(event->pos());
    }

}

void DrawCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    this->isMousePressed = false;
    if (!_rectCreated) {
        _rectCreated = true;
        _rect.setBottomRight(event->pos());
    }
    this->update();

}

void DrawCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (this->isMousePressed && _rectCreated) {
        if (_rect.left() < event->pos().x() && event->pos().x() < _rect.right() &&
                _rect.top() < event->pos().y() && event->pos().y() < _rect.bottom()) {
            //_rect = QRectF((qreal)event->x() , (qreal)event->y(), _rect.width(), _rect.height());
            _rect.moveCenter(QPointF((qreal)event->x(), (qreal)event->y()));
            //update();
            this->repaint();
        }
    }
}

void DrawCanvas::eraseRect()
{
    this->_rectCreated = false;
    update();

}

