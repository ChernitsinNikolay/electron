#include "qgraphicsgrid.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QVector>

QGraphicsGrid::QGraphicsGrid(float step) :
    QGraphicsItem(), m_step(step)
{
    setScale(2.0);
}

QRectF QGraphicsGrid::boundingRect() const
{
    //QGraphicsScene *tscene = scene();
    //return scene() ? scene()->sceneRect() : QRectF();
    return QRectF(0, 0, 420, 297);
}

void QGraphicsGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rect = boundingRect();
    QVector<QLineF> vlines, hlines;
    for(float i = rect.x(); i < rect.x() + rect.width(); i += m_step) {
        QLineF line;
        line.setLine(i, rect.y(), i, rect.y() + rect.height());
        vlines.push_back(line);
    }
    for(float i = rect.y(); i < rect.y() + rect.height(); i += m_step) {
        QLineF line;
        line.setLine(rect.x(), i, rect.x() + rect.width(), i);
        hlines.push_back(line);
    }
    painter->setPen(QPen(Qt::gray, 0.1, Qt::DotLine));
    painter->drawLines(vlines);
    painter->drawLines(hlines);
}
