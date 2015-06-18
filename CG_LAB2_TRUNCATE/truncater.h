#ifndef TRUNCATER_H
#define TRUNCATER_H

#include <QList>
#include <QPointF>
#include <QLineF>

class Truncater
{
public:
    Truncater();
    ~Truncater();

    static void truncate(QList<QPointF> &object, const QList<QPointF> &frame);
};

#endif // TRUNCATER_H
