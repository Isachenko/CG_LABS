#include "canvas.h"
#include <QtMath>
#include <QtAlgorithms>
#include <QPainter>
#include <QPainterPath>
#include "convexhullengine.h"
#include <QLineF>

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
    p.setWidth(3);
    p.setColor(Qt::PinchGesture);
    painter.setPen(lineColor);
    if (finised) {
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
    }

    p.setWidth(3);
    p.setColor(pointColor);
    painter.setPen(p);
    foreach (const QPointF &point, points) {
        painter.drawPoint(point);
    }
}




bool Canvas::hullDraw() const
{
    return _hullDraw;
}

void Canvas::setHullDraw(bool hullDraw)
{
    _hullDraw = hullDraw;
}

bool Canvas::showExampleInfo() const
{
    return _showExampleInfo;
}

void Canvas::setShowExampleInfo(bool showExampleInfo)
{
    _showExampleInfo = showExampleInfo;
}
void Canvas::calculateConvexHull()
{
    _hullPoints = ConvexHullEngine::getConvexHull(_points, &_lp, &_rp, &_minPoints, &_maxPoints, &_bordes);
    setHullDraw(true);
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
    drawPath(painter, _points, false, true, QColor::fromHsv(120, 100, 200), QColor::fromHsv(120, 255, 200));
    if (_showExampleInfo) {

        QPen p;
        p.setWidth(4);
        p.setColor(QColor::fromHsv(0, 255, 255));
        painter.setPen(p);
        foreach(const QPointF &point, _minPoints) {
            painter.drawPoint(point);
        }
        p.setColor(QColor::fromHsv(0, 255, 200));
        painter.setPen(p);
        foreach(const QPointF &point, _maxPoints) {
            painter.drawPoint(point);
        }
    }

    drawPath(painter, _hullPoints, _hullDraw, false, QColor::fromHsv(60, 100, 200), QColor::fromHsv(60, 255, 200));


    if (_showExampleInfo) {
        QPen p;
        p.setWidth(5);
        p.setColor(Qt::blue);
        painter.setPen(p);
        painter.drawPoint(_lp);
        painter.drawPoint(_rp);

        p.setWidth(1);
        p.setColor(Qt::black);
        painter.setPen(p);
        foreach(double border, _bordes) {
            QLineF line(border, 0, border, 10000);
            painter.drawLine(line);
        }
    }



    painter.end();

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    _points.append(event->pos());
    calculateConvexHull();
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{

}

void Canvas::clear()
{
    _points.clear();
    _hullPoints.clear();
    _hullDraw = false;
    update();
}

void Canvas::setPoints(const QList<QPointF> &windowPoints)
{
    _points = windowPoints;
    calculateConvexHull();
    update();
}


