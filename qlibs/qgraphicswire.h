#ifndef QGRAPHICSWIRE_H
#define QGRAPHICSWIRE_H
#include <QGraphicsItem>
#include <QBrush>
#include <QMenu>
#include "components/electron.h"

class QGraphicsWirePrivate;

class QGraphicsWire : public QGraphicsObject
{
    Q_OBJECT
public:
    QGraphicsWire();

    void addPoint(const QPointF &point);
    void replaceLastPoint(const QPointF &point);
    bool deleteLastPoint();
    void setComplete(bool st = true);
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

signals:
    void deleteMe();

private slots:
    void userDelete();

private:
    QVector<QGraphicsWirePrivate*> m_items;
    QColor color;
    QMenu m_menu;

    friend class QGraphicsWirePrivate;
};

#endif // QGRAPHICSWIRE_H
