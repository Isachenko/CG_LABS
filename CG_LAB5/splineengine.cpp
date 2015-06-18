#include "splineengine.h"
#include <QVector4D>
#include <QGenericMatrix>

#define POINTS_COUNT 100

QMatrix4x4 SplineEngine::Ms;// = QMatrix4x4();

SplineEngine::SplineEngine()
{

}

SplineEngine::~SplineEngine()
{

}

void SplineEngine::initMatrix()
{
    QVector4D row = QVector4D(-1, 3, -3, 1);
    Ms.setRow(0, row);
    row = QVector4D(3, -6, 3, 0);
    Ms.setRow(1, row);
    row = QVector4D(-3, 0, 3, 0);
    Ms.setRow(2, row);
    row = QVector4D(1, 4, 1, 0);
    Ms.setRow(3, row);
    Ms /= 6.0;
}

SplineEngine::calculateBSpline(const QVector<QPointF> &controlPoints, QList<QPointF> &linePoints)
{
    double step = 1.0 / (double)POINTS_COUNT;


    if (controlPoints.size() > 3) {
        int i = 0;
        QVector4D v1(2*controlPoints[i].x() - controlPoints[i+1].x(), controlPoints[i].x(), controlPoints[i+1].x(), controlPoints[i+2].x());
        QVector4D v2(2*controlPoints[i].y() - controlPoints[i+1].y(), controlPoints[i].y(), controlPoints[i+1].y(), controlPoints[i+2].y());

        v1 = Ms.map(v1);
        v2 = Ms.map(v2);

        double t = 0;
        for(int i = 0; i < POINTS_COUNT; ++i) {
            double x = v1[0]*(t*t*t) + v1[1]*(t*t) + v1[2]*(t) + v1[3];
            double y = v2[0]*(t*t*t) + v2[1]*(t*t) + v2[2]*(t) + v2[3];
            linePoints.append(QPointF(x, y));

            t += step;
        }
    }

    for(int i = 0; i < controlPoints.size() - 3; ++i) {
        QVector4D v1(controlPoints[i].x(), controlPoints[i+1].x(), controlPoints[i+2].x(), controlPoints[i+3].x());
        QVector4D v2(controlPoints[i].y(), controlPoints[i+1].y(), controlPoints[i+2].y(), controlPoints[i+3].y());

        v1 = Ms.map(v1);
        v2 = Ms.map(v2);

        double t = 0;
        for(int i = 0; i < POINTS_COUNT; ++i) {
            double x = v1[0]*(t*t*t) + v1[1]*(t*t) + v1[2]*(t) + v1[3];
            double y = v2[0]*(t*t*t) + v2[1]*(t*t) + v2[2]*(t) + v2[3];
            linePoints.append(QPointF(x, y));

            t += step;
        }
    }

    if (controlPoints.size() > 3) {
        int i = controlPoints.size() - 1;
        QVector4D v1(controlPoints[i - 2].x(), controlPoints[i - 1].x(), controlPoints[i].x(), 2*controlPoints[i].x() - controlPoints[i - 1].x());
        QVector4D v2(controlPoints[i - 2].y(), controlPoints[i - 1].y(), controlPoints[i].y(), 2*controlPoints[i].y() - controlPoints[i - 1].y());

        v1 = Ms.map(v1);
        v2 = Ms.map(v2);

        double t = 0;
        for(int i = 0; i < POINTS_COUNT; ++i) {
            double x = v1[0]*(t*t*t) + v1[1]*(t*t) + v1[2]*(t) + v1[3];
            double y = v2[0]*(t*t*t) + v2[1]*(t*t) + v2[2]*(t) + v2[3];
            linePoints.append(QPointF(x, y));

            t += step;
        }
    }
}

