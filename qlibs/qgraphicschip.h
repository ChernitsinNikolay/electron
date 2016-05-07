#ifndef QGRAPHICSCHIP_H
#define QGRAPHICSCHIP_H
#include <QGraphicsItem>
#include "components/electron.h"

class QGraphicsChip : public QGraphicsItem
{
public:
    QGraphicsChip(ElectronItem *item);
    QGraphicsChip(const QGraphicsChip &chip);

    inline ElectronItem *boundItem() const { return m_eitem; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setPos(const QPointF &pos);
    inline void setPos(qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void initial();

    ElectronItem *m_eitem;
    QRectF bounding;
};

inline void QGraphicsChip::setPos(qreal x, qreal y)
{
    m_eitem->setPos(x, y);
    QGraphicsItem::setPos(x, y);
}

#endif // QGRAPHICSCHIP_H
