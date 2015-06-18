#ifndef D2TREE_H
#define D2TREE_H

#include <QVector>
#include <QPointF>
#include <QRectF>

class D2Tree
{
public:
    enum class NodeType: int {HORIZONTAL = 0, VERTICAL = 1};
    struct Node {
        QPointF point;
        Node* childRight = nullptr;
        Node* childLeft = nullptr;
        NodeType nodeType = NodeType::HORIZONTAL;
        Node(QPointF point, NodeType nodeType) :
            point(point),
            nodeType(nodeType){
        }
    };
public:
    Node* root;
public:
    D2Tree(QVector<QPointF> &points);
    ~D2Tree();

private:
    Node* createSubTree(QVector<QPointF>::iterator begin, QVector<QPointF>::iterator end, const D2Tree::NodeType nodeType);
    void getPointsInRect(const QRectF &rect, Node* subRoot, QVector<QPointF> &points);

public:
    QVector<QPointF> getPointsInRect(const QRectF &rect);


};

#endif // D2TREE_H
