#ifndef QGRAPHICSCHIP_H
#define QGRAPHICSCHIP_H
#include <QGraphicsItem>
#include "components/electron.h"

class QGraphicsChip : public QGraphicsItem
{
public:
    QGraphicsChip(ElectronItem *item);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    ElectronItem *m_eitem;
};

#endif // QGRAPHICSCHIP_H
