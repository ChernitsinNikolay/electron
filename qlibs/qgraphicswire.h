#ifndef QGRAPHICSWIRE_H
#define QGRAPHICSWIRE_H
#include <QGraphicsItem>
#include <QBrush>
#include <QMenu>
#include "components/electron.h"
#include "qlibs/qgraphicschip.h"

class QGraphicsWirePrivate;

class QGraphicsWire : public QGraphicsObject
{
    Q_OBJECT
public:
    QGraphicsWire();
    QGraphicsWire(const QGraphicsWire &wire);
    QGraphicsWire(ElectronWire *wire);

    QGraphicsWire &operator=(const QGraphicsWire &item);

    inline ElectronWire *boundItem() const { return m_ewire; }

    void setFromItem(QGraphicsChip *item);
    inline QGraphicsChip *fromItem() const { return m_from; }
    void setToItem(QGraphicsChip *item);
    inline QGraphicsChip *toItem() const { return m_to; }

    void addPoint(const QPointF &point);
    void replaceLastPoint(const QPointF &point);
    bool deleteLastPoint();
    bool setComplete(bool st = true);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setPos(const QPointF &pos);
    void setPos(qreal x, qreal y);

    enum {
        QWire = 65535
    };
    virtual int type() const;

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

signals:
    void deleteMe();

private slots:
    void userDelete();

private:
    void setPos(const Basic::Point &point);

    enum Type {
        User,
        Model
    };

    QVector<QGraphicsWirePrivate*> m_items;
    QGraphicsChip *m_from, *m_to;
    QColor color;
    QMenu m_menu;
    ElectronWire *m_ewire;
    Type m_type;

    friend class QGraphicsWirePrivate;
};

#endif // QGRAPHICSWIRE_H
