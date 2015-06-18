#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QVector>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QVector<QPointF> _controlPoints;
    QList<QPointF> _linePoints;
    int _pointToMoveIndex = -1;

private:
    void calculateLinePoints();

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent * event);
    void clear();
    void setControlPoints(const QVector<QPointF> &controlPoints);

signals:

public slots:
};

#endif // CANVAS_H
