#include "canvas.h"
#include <QtMath>
#include <QtAlgorithms>
#include <QPainter>
#include <QPainterPath>
#include "splineengine.h"

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

void Canvas::calculateLinePoints()
{
    _linePoints.clear();
    SplineEngine::calculateBSpline(_controlPoints, _linePoints);
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
    drawPath(painter, _controlPoints.toList(), false, false, QColor::fromHsv(120, 100, 200), QColor::fromHsv(120, 255, 200));
    drawPath(painter, _linePoints, false, false, QColor::fromHsv(0, 100, 255), QColor::fromHsv(0, 255, 255));
    painter.end();

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    _pointToMoveIndex = -1;
    int index = 0;
    foreach(const QPointF &point, _controlPoints) {
        double range = getRange(event->pos(), point);
        if (range < SMALL_RANGE) {
            _pointToMoveIndex = index;
            break;
        }
        ++index;
    }
    if (_pointToMoveIndex == -1) {
        _controlPoints.append(event->pos());
        //_pointToMoveIndex = _controlPoints.size() - 1;
    }

    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    _pointToMoveIndex = -1;
    calculateLinePoints();
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (_pointToMoveIndex != -1) {
        _controlPoints[_pointToMoveIndex] = event->pos();
    }
    update();
}

void Canvas::clear()
{
    _controlPoints.clear();
    _linePoints.clear();

    update();
}

void Canvas::setControlPoints(const QVector<QPointF> &controlPoints)
{
    _controlPoints = controlPoints;

    update();
}

