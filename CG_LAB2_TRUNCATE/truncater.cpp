#include "truncater.h"

Truncater::Truncater()
{

}

Truncater::~Truncater()
{

}

bool isPointPosOnRight(const QPointF &p1, const QPointF &p2, const QPointF &p3) {
    double d = (p3.x() - p1.x()) * (p2.y() - p1.y()) - (p3.y() - p1.y()) * (p2.x() - p1.x());
    return (d > 0);
}

bool isPointInside(const QPointF &p1, const QPointF &p2, const QPointF &p3, bool ifFrameClockwise) {
    bool isPointOnRight = isPointPosOnRight(p1, p2, p3);
    return !(isPointOnRight^ifFrameClockwise);
}

void Truncater::truncate(QList<QPointF> &object, const QList<QPointF> &frame)
{
    // определение внутренней стороны рамки
    bool clockwise = true;
    if (frame.size() < 3) {
        return;
    } else {
        QPointF f1 = frame.first();
        QPointF f2 = frame.at(1);
        QPointF f3 = frame.at(2);
        if (!isPointPosOnRight(f1, f2, f3)) {
            clockwise = false;
        }
    }

    for (int frameIndex = 0; frameIndex < frame.size(); ++frameIndex) {
        QList<QPointF> newObject;
        QPointF f1 = frame.at(frameIndex);
        QPointF f2 = frame.at((frameIndex + 1) % frame.size());
        for (int objectIndex = 0; objectIndex < object.size(); ++objectIndex) {
            QPointF o1 = object.at(objectIndex);
            QPointF o2 = object.at((objectIndex + 1) % object.size());

            bool o1Inside = isPointInside(f1, f2, o1, clockwise);
            bool o2Inside = isPointInside(f1, f2, o2, clockwise);

            if (o1Inside && o2Inside) {
                newObject.append(o2);
            } else if(o1Inside && !o2Inside) {
                QPointF *intersectPoint = new QPointF();
                QLineF fLine(f1, f2);
                QLineF oLine(o1, o2);
                fLine.intersect(oLine, intersectPoint);
                newObject.append(*intersectPoint);
                delete intersectPoint;
            } else if(!o1Inside && o2Inside) {
                QPointF *intersectPoint = new QPointF();
                QLineF fLine(f1, f2);
                QLineF oLine(o1, o2);
                fLine.intersect(oLine, intersectPoint);
                newObject.append(*intersectPoint);
                newObject.append(o2);
                delete intersectPoint;
            }
        }
        object = newObject;
    }


}

