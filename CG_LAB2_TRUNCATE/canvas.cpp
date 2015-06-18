#include "canvas.h"
#include <QtMath>
#include <QtAlgorithms>
#include <QPainter>
#include <QPainterPath>
#include "truncater.h"

#define SMALL_RANGE 20

double getRange(const QPointF &a,const QPointF &b)
{
    double dx = a.x() - b.x();
    double dx2 = dx*dx;
    double dy = a.y() - b.y();
    double dy2 = dy*dy;
    double r = qSqrt(dx2 + dy2);
    return r;
}

void drawPath(QPainter &painter, const QList<QPointF> points, bool finised = false, bool fill = false, QColor lineColor = QColor(Qt::red), QColor pointColor = QColor(Qt::black))
{
    painter.setRenderHint(QPainter::Antialiasing);
    if (fill && finised) {
        painter.setBrush(QBrush(lineColor));
    } else {
        painter.setBrush(QBrush(Qt::transparent));
    }
    QPen p;
    p.setWidth(2);
    p.setColor(Qt::PinchGesture);
    painter.setPen(lineColor);
    if (points.size() >= 2) {
        QPainterPath path(points.first());
        foreach (const QPointF &point, points) {
            path.lineTo(point);
        }
        if (finised) {
            path.lineTo(points.first());
        }
        painter.drawPath(path);
    }

    p.setWidth(5);
    p.setColor(pointColor);
    painter.setPen(p);
    foreach (const QPointF &point, points) {
        painter.drawPoint(point);
    }


}

void Canvas::calculateObjectTruncation()
{
    _oldObjectPoints = _objectPoints;
    Truncater::truncate(_objectPoints, _windowPoints);
}

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{

}

Canvas::~Canvas()
{

}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawRect(event->rect());
    drawPath(painter, _windowPoints, _windowDraw, true, QColor::fromHsv(120, 100, 200), QColor::fromHsv(120, 255, 200));
    drawPath(painter, _oldObjectPoints, _objectDraw, true, QColor::fromHsv(240, 100, 255), QColor::fromHsv(240, 255, 255));
    drawPath(painter, _objectPoints, _objectDraw, true, QColor::fromHsv(0, 100, 255), QColor::fromHsv(0, 255, 255));
    painter.end();

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (!_windowDraw) {
        QPointF pos(event->pos());
        double range = SMALL_RANGE + 1;
        if (!_windowPoints.isEmpty()) {
            range = getRange(pos, _windowPoints.first());
        }
        if (range > SMALL_RANGE) {
            _windowPoints.append(event->pos());
        } else {
            _windowDraw = true;
        }
    } else if (!_objectDraw) {
        QPointF pos(event->pos());
        double range = SMALL_RANGE + 1;
        if (!_objectPoints.isEmpty()) {
            range = getRange(pos, _objectPoints.first());
        }
        if (range > SMALL_RANGE) {
            _objectPoints.append(event->pos());
        } else {
            _objectDraw = true;
            calculateObjectTruncation();
        }
    }


    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{

}

void Canvas::clear()
{

    _windowPoints.clear();
    _objectPoints.clear();
    _oldObjectPoints.clear();

    _windowDraw = false;
    _objectDraw = false;

    update();
}

void Canvas::setWindowPoints(const QList<QPointF> &windowPoints)
{
    _windowPoints = windowPoints;
    _windowDraw = true;

    update();
}

void Canvas::setObjectPoints(const QList<QPointF> &objectPoints)
{
    _objectPoints = objectPoints;
    _objectDraw = true;
    _oldObjectPoints.clear();
    calculateObjectTruncation();

    update();
}

