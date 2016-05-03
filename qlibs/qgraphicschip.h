#ifndef QGRAPHICSCHIP_H
#define QGRAPHICSCHIP_H
#include <QGraphicsItem>

class QGraphicsChip : public QGraphicsItem
{
public:
    QGraphicsChip();

    QRectF boundingRect() const Q_DECL_OVERRIDE {}
    QPainterPath shape() const Q_DECL_OVERRIDE {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE {}

};

#endif // QGRAPHICSCHIP_H
