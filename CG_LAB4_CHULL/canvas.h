#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QList<QPointF> _points;
    QList<QPointF> _hullPoints;
    QList<QPointF> _minPoints;
    QList<QPointF> _maxPoints;
    QPointF _lp;
    QPointF _rp;
    QList<double> _bordes;

    bool _hullDraw = false;
    bool _showExampleInfo = false;

private:
    void calculateConvexHull();

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void clear();
    void setPoints(const QList<QPointF> &windowPoints);

    bool hullDraw() const;
    void setHullDraw(bool hullDraw);

    bool showExampleInfo() const;
    void setShowExampleInfo(bool showExampleInfo);

signals:

public slots:
};

#endif // CANVAS_H
