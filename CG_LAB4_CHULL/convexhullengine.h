#ifndef CONVEXHULLENGINE_H
#define CONVEXHULLENGINE_H

#include <QList>
#include <QPointF>


class ConvexHullEngine
{
public:
    ConvexHullEngine();
    ~ConvexHullEngine();

    static QList<QPointF> getConvexHull(QList<QPointF> &points, QPointF *r_lp, QPointF *r_rp, QList<QPointF> *r_minPoints, QList<QPointF> *r_maxPoints, QList<double> *r_borders);
};

#endif // CONVEXHULLENGINE_H
