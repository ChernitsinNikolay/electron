#ifndef QGRAPHICSCHIP_H
#define QGRAPHICSCHIP_H
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QMenu>
#include "components/electron.h"

class QGraphicsChip : public QGraphicsObject
{
    Q_OBJECT
public:
    QGraphicsChip(ElectronItem *item);
    QGraphicsChip(const QGraphicsChip &chip);

    inline ElectronItem *boundItem() const { return m_eitem; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setPos(const QPointF &pos);
    inline void setPos(qreal x, qreal y);

    void setComplete(bool st = true);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

signals:
    void deleteMe();
    void clickToContact(const QPointF&);

private slots:
    void userDelete();

private:
    void initial();
    void createContextMenu();

    ElectronItem *m_eitem;
    Basic::Join *selected_join;
    bool m_selected;
    bool m_complete;
    QRectF bounding;
    QColor m_color;
    QMenu m_menu;
};

inline void QGraphicsChip::setPos(qreal x, qreal y)
{
    m_eitem->setPos(x, y);
    QGraphicsItem::setPos(x, y);
}

#endif // QGRAPHICSCHIP_H
