#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QList<QPointF> _windowPoints;
    QList<QPointF> _objectPoints;
    QList<QPointF> _oldObjectPoints;

    bool _windowDraw = false;
    bool _objectDraw = false;

private:
    void calculateObjectTruncation();

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void clear();
    void setWindowPoints(const QList<QPointF> &windowPoints);
    void setObjectPoints(const QList<QPointF> &objectPoints);

signals:

public slots:
};

#endif // CANVAS_H
