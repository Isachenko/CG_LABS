#include "d2tree.h"

qreal min(qreal a, qreal b) {
    if (a < b) {
        return a;
    }
    return b;
}

qreal max(qreal a, qreal b) {
    if (a > b) {
        return a;
    }
    return b;
}

struct LessThenByX {
    bool operator()(const QPointF &a, const QPointF &b) {
        return a.x() < b.x();
    }
};
struct LessThenByY {
    bool operator()(const QPointF &a, const QPointF &b) {
        return a.y() < b.y();
    }
};

D2Tree::D2Tree(QVector<QPointF> &points)
{
    root = createSubTree(points.begin(), points.end(), NodeType::HORIZONTAL);
}

D2Tree::~D2Tree()
{

}

D2Tree::Node *D2Tree::createSubTree(QVector<QPointF>::iterator begin, QVector<QPointF>::iterator end, const D2Tree::NodeType nodeType)
{
    if (nodeType == NodeType::HORIZONTAL) {
        LessThenByX lessThenByX;
        qSort(begin, end, lessThenByX);
    } else if (nodeType == NodeType::VERTICAL) {
        LessThenByY lessThenByY;
        qSort(begin, end, lessThenByY);
    }

    if (begin == end) {
        return new Node(*begin, nodeType);
    } else {
        QVector<QPointF>::iterator mid = begin + (end - begin) / 2;

        NodeType childNodeType = NodeType::HORIZONTAL;
        if (nodeType == NodeType::HORIZONTAL) {
            childNodeType = NodeType::VERTICAL;
        }
        Node* childLeft = nullptr;
        if (begin != mid) {
            childLeft = createSubTree(begin, mid - 1, childNodeType);
        }
        Node* childRight = nullptr;
        if (mid != end) {
            childRight = createSubTree(mid + 1, end, childNodeType);
        }
        Node* subRoot = new Node(*mid, nodeType);
        subRoot->childLeft = childLeft;
        subRoot->childRight = childRight;
        return subRoot;
    }
}

void D2Tree::getPointsInRect(const QRectF &rect, D2Tree::Node *subRoot, QVector<QPointF> &points)
{
    if ((subRoot->point.x() >= rect.left()) && (subRoot->point.x() <= rect.right())
            && (subRoot->point.y() >= rect.top()) && (subRoot->point.y() <= rect.bottom())) {
        points.append(subRoot->point);
    }

    if (subRoot->nodeType == NodeType::HORIZONTAL) {
        if ((rect.left() <= subRoot->point.x()) && subRoot->childLeft) {
            qreal right = min(subRoot->point.x(), rect.right());
            getPointsInRect(QRectF(QPointF(rect.left(), rect.top()), QPointF(right, rect.bottom())),
                            subRoot->childLeft, points);
        }
        if ((rect.right() >= subRoot->point.x()) && subRoot->childRight) {
            qreal left = max(subRoot->point.x(), rect.left());
            getPointsInRect(QRectF(QPointF(left, rect.top()), QPointF(rect.right(), rect.bottom())),
                            subRoot->childRight, points);
        }
    } else if (subRoot->nodeType == NodeType::VERTICAL) {
        if ((rect.top() <= subRoot->point.y()) && subRoot->childLeft) {
            qreal bottom = min(subRoot->point.y(), rect.bottom());
            getPointsInRect(QRectF(QPointF(rect.left(), rect.top()), QPointF(rect.right(), bottom)),
                            subRoot->childLeft, points);
        }
        if ((rect.bottom() >= subRoot->point.y()) && subRoot->childRight) {
            qreal top = max(subRoot->point.y(), rect.top());
            getPointsInRect(QRectF(QPointF(rect.left(), top), QPointF(rect.right(), rect.bottom())),
                            subRoot->childRight, points);
        }
    }

}

QVector<QPointF> D2Tree::getPointsInRect(const QRectF &rect)
{
    QVector<QPointF> pointsToDrow;
    getPointsInRect(rect, root, pointsToDrow);
    return pointsToDrow;
}

