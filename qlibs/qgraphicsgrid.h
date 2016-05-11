#ifndef QGRAPHICSGRID_H
#define QGRAPHICSGRID_H
#include <QGraphicsItem>

class QGraphicsGrid : public QGraphicsItem
{
public:
    QGraphicsGrid(float step);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    float m_step;
};

#endif // QGRAPHICSGRID_H
