#include "convexhullengine.h"
#include <QVector>
#include <QStack>

#define APROXIMATE_POINTS_IN_SECTOR 10
#define INF 9999999

ConvexHullEngine::ConvexHullEngine()
{

}

ConvexHullEngine::~ConvexHullEngine()
{

}

bool isPointPosOnRight(const QPointF &p1, const QPointF &p2, const QPointF &p3) {
    double d = (p3.x() - p1.x()) * (p2.y() - p1.y()) - (p3.y() - p1.y()) * (p2.x() - p1.x());
    return (d > 0);
}

QList<QPointF> ConvexHullEngine::getConvexHull(QList<QPointF> &points, QPointF *r_lp, QPointF* r_rp, QList<QPointF> *r_minPoints, QList<QPointF> *r_maxPoints, QList<double> *r_borders)
{
    int sectorsCount = points.size() / APROXIMATE_POINTS_IN_SECTOR;
    if (sectorsCount == 0) {
        sectorsCount = 1;
    }
    if (sectorsCount > 30) {
        sectorsCount = 30;
    }

    QPointF lp = points.first();
    QPointF rp = points.first();
    foreach(const QPointF &point, points) {
        if (point.x() < lp.x()) {
            lp = point;
        }
        if (point.x() > rp.x()) {
            rp = point;
        }
    }

    QVector<QPointF> minPointsInSectors;
    QVector<QPointF> maxPointsInSectors;
    for(int i = 0; i < sectorsCount; ++i) {
        minPointsInSectors.append(QPointF(0, INF + 1));
        maxPointsInSectors.append(QPointF(0, -INF - 1));
    }
    double sectorsSize = (rp.x() - lp.x()) / ((double)sectorsCount);
    foreach(const QPointF &point, points) {
        int sectorIndex = ((int)((point.x() - lp.x()) / sectorsSize) ) % sectorsCount;
        if (point.y() < minPointsInSectors[sectorIndex].y()) {
            minPointsInSectors[sectorIndex] = point;
        }
        if (point.y() > maxPointsInSectors[sectorIndex].y()) {
            maxPointsInSectors[sectorIndex] = point;
        }
    }

    QList<QPointF> convexHullPoints;
    convexHullPoints.append(lp);
    foreach(const QPointF &point, minPointsInSectors) {
        convexHullPoints.append(point);
    }
    convexHullPoints.append(rp);
    for(int i = maxPointsInSectors.size() - 1; i >=0; --i) {
        convexHullPoints.append(maxPointsInSectors[i]);
    }
    convexHullPoints.append(lp);

    QStack<QPointF> stack;
    stack.append(convexHullPoints.first());
    stack.append(convexHullPoints.at(1));
    convexHullPoints.removeFirst();
    convexHullPoints.removeFirst();

    foreach (const QPointF &point, convexHullPoints) {
        QPointF p3 = point;
        QPointF p2 = stack.top();
        stack.pop();
        QPointF p1 = stack.top();
        while(isPointPosOnRight(p1, p2, p3)) {
            if (stack.size() > 1) {
                p2 = p1;
                stack.pop();
                p1 = stack.top();
            } else {
                stack.pop();
                p2 = p1;
                break;
            }
        }
        stack.append(p2);
        stack.append(p3);
    }
    convexHullPoints = stack.toList();


    *r_lp = lp;
    *r_rp = rp;
    r_maxPoints->clear();
    r_maxPoints->append(maxPointsInSectors.toList());
    r_minPoints->clear();
    r_minPoints->append(minPointsInSectors.toList());
    r_borders->clear();
    for(int i = 0; i <= sectorsCount; ++i) {
        r_borders->append(lp.x() + (i * sectorsSize));
    }
    return convexHullPoints;
}

