#ifndef SPLINEENGINE_H
#define SPLINEENGINE_H

#include <QVector>
#include <QPointF>
#include <QList>
#include <QMatrix4x4>
#include <QMatrix4x2>

class SplineEngine
{
private:
    static QMatrix4x4 Ms;

public:
    SplineEngine();
    ~SplineEngine();

    static void initMatrix();
    static calculateBSpline(const QVector<QPointF> &controlPoints, QList<QPointF> &linePoints);
    void hui();
    int ggg();
};

#endif // SPLINEENGINE_H
