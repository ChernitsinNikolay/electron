#include "qgraphicschip.h"
#include <QPainter>
#include <iostream>

QGraphicsChip::QGraphicsChip(ElectronItem *item) :
    m_eitem(item)
{
    float maxX = 0;
    float minX = 0;
    float maxY = 0;
    float minY = 0;

    //Rectangles;
    for(ElectronImage::Rectangles::const_iterator iter = m_eitem->image().rectangles().begin(); iter != m_eitem->image().rectangles().end(); iter++) {
        const Basic::Rectangle rect = *iter;
        minX = std::min(minX, rect.x());
        minX = std::min(minX, rect.x() + rect.w());
        maxX = std::max(maxX, rect.x());
        maxX = std::max(maxX, rect.x() + rect.w());
        minY = std::min(minY, rect.y());
        minY = std::min(minY, rect.y() + rect.h());
        maxY = std::max(maxY, rect.y());
        maxY = std::max(maxY, rect.y() + rect.h());
    }
    //Arcs;
    for(ElectronImage::Arcs::const_iterator iter = m_eitem->image().arcs().begin(); iter != m_eitem->image().arcs().end(); iter++) {
        const Basic::Arc arc = *iter;
        const Basic::Rectangle rect = arc.rectangle();
        minX = std::min(minX, rect.x());
        minX = std::min(minX, rect.x() + rect.w());
        maxX = std::max(maxX, rect.x());
        maxX = std::max(maxX, rect.x() + rect.w());
        minY = std::min(minY, rect.y());
        minY = std::min(minY, rect.y() + rect.h());
        maxY = std::max(maxY, rect.y());
        maxY = std::max(maxY, rect.y() + rect.h());
    }
    //Lines;
    for(ElectronImage::Lines::const_iterator iter = m_eitem->image().lines().begin(); iter != m_eitem->image().lines().end(); iter++) {
        const Basic::Line line = *iter;
        minX = std::min(minX, line.sx());
        minX = std::min(minX, line.ex());
        maxX = std::max(maxX, line.sx());
        maxX = std::max(maxX, line.ex());
        minY = std::min(minY, line.sy());
        minY = std::min(minY, line.ey());
        maxY = std::max(maxY, line.sy());
        maxY = std::max(maxY, line.ey());
    }
    //Arrows;
    for(ElectronImage::Arrows::const_iterator iter = m_eitem->image().arrows().begin(); iter != m_eitem->image().arrows().end(); iter++) {
        //TODO
    }
    //Strings;
    for(ElectronImage::Strings::const_iterator iter = m_eitem->image().strings().begin(); iter != m_eitem->image().strings().end(); iter++) {
        const Basic::String string = *iter;
        minX = std::min(minX, string.x());
        maxX = std::max(maxX, string.x());
        minY = std::min(minY, string.y());
        maxY = std::max(maxY, string.y());
    }
    //Joins;
    for(ElectronImage::Joins::const_iterator iter = m_eitem->image().joins().begin(); iter != m_eitem->image().joins().end(); iter++) {
        const Basic::Join join = *iter;
        minX = std::min(minX, join.x());
        maxX = std::max(maxX, join.x());
        minY = std::min(minY, join.y());
        maxY = std::max(maxY, join.y());
    }

    bounding.setX(minX);
    bounding.setY(minY);
    bounding.setWidth(maxX - minX);
    bounding.setHeight(maxY - minY);
    //std::cout<<bounding.x()<<"\t"<<bounding.y()<<"\t"<<bounding.width()<<"\t"<<bounding.height()<<std::endl;
}

QRectF QGraphicsChip::boundingRect() const
{
    //return QRectF(-50, -50, 50, 50);
    return bounding;
}

QPainterPath QGraphicsChip::shape() const
{
    QPainterPath path;
    //path.addRect(14, 14, 82, 42);
    path.addRect(bounding);
    return path;
}

void QGraphicsChip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    /*QPolygonF br;
    br.push_back(QPointF(bounding.x(), bounding.y()));
    br.push_back(QPointF(bounding.x() + bounding.width(), bounding.y()));
    br.push_back(QPointF(bounding.x() + bounding.width(), bounding.y() + bounding.height()));
    br.push_back(QPointF(bounding.x(), bounding.y() + bounding.height()));
    painter->drawPolygon(br);*/

    //Rectangles;
    for(ElectronImage::Rectangles::const_iterator iter = m_eitem->image().rectangles().begin(); iter != m_eitem->image().rectangles().end(); iter++) {
        QPolygonF polygon;
        const Basic::Rectangle rect = *iter;
        polygon.push_back(QPointF(rect.x(), rect.y()));
        polygon.push_back(QPointF(rect.x() + rect.w(), rect.y()));
        polygon.push_back(QPointF(rect.x() + rect.w(), rect.y() + rect.h()));
        polygon.push_back(QPointF(rect.x(), rect.y() + rect.h()));
        painter->drawPolygon(polygon);
    }
    //Arcs;
    for(ElectronImage::Arcs::const_iterator iter = m_eitem->image().arcs().begin(); iter != m_eitem->image().arcs().end(); iter++) {
        const Basic::Arc arc = *iter;
        const Basic::Rectangle rect = arc.rectangle();
        painter->drawArc(rect.x(), rect.y(), rect.w(), rect.h(), arc.sAngle() * 16, arc.eAngle() * 16);
    }
    //Lines;
    for(ElectronImage::Lines::const_iterator iter = m_eitem->image().lines().begin(); iter != m_eitem->image().lines().end(); iter++) {
        const Basic::Line line = *iter;
        painter->drawLine(line.sx(), line.sy(), line.ex(), line.ey());
    }
    //Arrows;
    for(ElectronImage::Arrows::const_iterator iter = m_eitem->image().arrows().begin(); iter != m_eitem->image().arrows().end(); iter++) {
        //TODO
    }
    //Strings;
    for(ElectronImage::Strings::const_iterator iter = m_eitem->image().strings().begin(); iter != m_eitem->image().strings().end(); iter++) {
        const Basic::String string = *iter;
        painter->drawText(string.x(), string.y(), QString::fromStdString(string.string()));
    }
    //Joins;
    for(ElectronImage::Joins::const_iterator iter = m_eitem->image().joins().begin(); iter != m_eitem->image().joins().end(); iter++) {
        const Basic::Join join = *iter;
        painter->drawPoint(join.x(), join.y());
    }

    /*QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (lod < 0.2) {
        if (lod < 0.125) {
            painter->fillRect(QRectF(0, 0, 110, 70), fillColor);
            return;
        }

        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(13, 13, 97, 57);
        painter->setBrush(b);
        return;
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(14, 14, 79, 39));
    painter->setBrush(b);

    if (lod >= 1) {
        painter->setPen(QPen(Qt::gray, 1));
        painter->drawLine(15, 54, 94, 54);
        painter->drawLine(94, 53, 94, 15);
        painter->setPen(QPen(Qt::black, 0));
    }

    // Draw text
    if (lod >= 2) {
        QFont font("Times", 10);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
        painter->save();
        painter->scale(0.1, 0.1);
        painter->drawText(170, 180, QString("Model: VSC-2000 (Very Small Chip) at %1x%2").arg(x).arg(y));
        painter->drawText(170, 200, QString("Serial number: DLWR-WEER-123L-ZZ33-SDSJ"));
        painter->drawText(170, 220, QString("Manufacturer: Chip Manufacturer"));
        painter->restore();
    }

    // Draw lines
    QVarLengthArray<QLineF, 36> lines;
    if (lod >= 0.5) {
        for (int i = 0; i <= 10; i += (lod > 0.5 ? 1 : 2)) {
            lines.append(QLineF(18 + 7 * i, 13, 18 + 7 * i, 5));
            lines.append(QLineF(18 + 7 * i, 54, 18 + 7 * i, 62));
        }
        for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2)) {
            lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
            lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
        }
    }
    if (lod >= 0.4) {
        const QLineF lineData[] = {
            QLineF(25, 35, 35, 35),
            QLineF(35, 30, 35, 40),
            QLineF(35, 30, 45, 35),
            QLineF(35, 40, 45, 35),
            QLineF(45, 30, 45, 40),
            QLineF(45, 35, 55, 35)
        };
        lines.append(lineData, 6);
    }
    painter->drawLines(lines.data(), lines.size());

    // Draw red ink
    if (stuff.size() > 1) {
        QPen p = painter->pen();
        painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::NoBrush);
        QPainterPath path;
        path.moveTo(stuff.first());
        for (int i = 1; i < stuff.size(); ++i)
            path.lineTo(stuff.at(i));
        painter->drawPath(path);
        painter->setPen(p);
    }*/
}

void QGraphicsChip::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void QGraphicsChip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void QGraphicsChip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
