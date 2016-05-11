#include "qschemeview.h"
#include <iostream>
#include <QEvent>
#include <QMouseEvent>
#include "qlibs/qgraphicschip.h"
#include "qlibs/qgraphicsgrid.h"
#include <math.h>

QSchemeView::QSchemeView(QWidget *parent) :
    QGraphicsView(parent), m_model(0), m_current(0), m_current_wire(0), m_gridStep(5)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setMouseTracking(true);
    scene->addItem(new QGraphicsGrid(m_gridStep));
}

QPointF QSchemeView::mapToGridScene(const QPoint &point) const
{
    QPointF r = mapToScene(point);
    r.rx() = 2.0 * round(r.x() / 2.0 / m_gridStep) * m_gridStep;
    r.ry() = 2.0 * round(r.y() / 2.0 / m_gridStep) * m_gridStep;
    return r;
}

void QSchemeView::setModel(QSchemeModel *model)
{
    m_model = model;
}

void QSchemeView::wire(const QPointF &point)
{
    if(m_current) {
        scene->removeItem(m_current);
        m_current = NULL;
        scene->update();
    }
    if(!m_current_wire) {
        std::cout<<"start wire"<<std::endl;
        m_current_wire = new QGraphicsWire();
        scene->addItem(m_current_wire);
        connect(m_current_wire, SIGNAL(deleteMe()), SLOT(userDeleteItemWire()));
        m_current_wire->setPos(point);
        m_current_wire->addPoint(point);
        //m_current_wire = new QGraphicsWire(QPointF(0, 0), *qobject_cast<QGraphicsObject*>(sender()));
        //m_current_wire->setEndPoint(QPointF(0, -100));
        //m_current_wire->setPos(point);
        //scene->addItem(m_current_wire);
        //scene->update();
    } else {
        std::cout<<"end wire"<<std::endl;
        m_current_wire->setComplete();
        m_current_wire = NULL;
        //m_current_wire->addCompletePoint(point, *qobject_cast<QGraphicsObject*>(sender()));
        //m_current_wire = NULL;
        //scene->update();
    }
}

void QSchemeView::userDeleteItemChip()
{
    QGraphicsItem *item = (QGraphicsChip*)sender();
    scene->removeItem(item);
}

void QSchemeView::userDeleteItemWire()
{
    QGraphicsItem *item = (QGraphicsWire*)sender();
    scene->removeItem(item);
}

void QSchemeView::mouseMoveEvent(QMouseEvent *event)
{
    //std::cout<<"move "<<event->x()<<"\t"<<event->y()<<std::endl;
    if(m_current_wire) {
        m_current_wire->replaceLastPoint(mapToGridScene(event->pos()));
        //m_current_wire->setEndPoint(mapToGridScene(event->pos()));
        //update();
    }
    if(m_current) {
        static_cast<QGraphicsChip*>(m_current)->setPos(mapToGridScene(event->pos()));
    }
    QGraphicsView::mouseMoveEvent(event);
}

void QSchemeView::mousePressEvent(QMouseEvent *event)
{
    //std::cout<<"press"<<std::endl;
    switch(event->button()) {
    case Qt::LeftButton:
        if(m_current_wire) {
            m_current_wire->addPoint(mapToGridScene(event->pos()));
            //m_current_wire->addCurvePoint(mapToGridScene(event->pos()));
            //update();
        } else if(m_current) {
            QGraphicsChip *chip = new QGraphicsChip(m_model->addItem(*static_cast<QGraphicsChip*>(m_current)));
            scene->addItem(chip);
            connect(chip, SIGNAL(deleteMe()), SLOT(userDeleteItemChip()));
            scene->removeItem(m_current);
            m_current = NULL;
            chip->setComplete();
            connect(chip, SIGNAL(clickToContact(QPointF)), SLOT(wire(QPointF)));
            scene->update();
        } else {
            /*m_current = new QGraphicsChip(m_model->current());
            static_cast<QGraphicsChip*>(m_current)->setPos(event->pos());
            scene->addItem(m_current);*/
        }
        break;

    case Qt::RightButton:
        if(m_current_wire) {
            //if(m_current_wire->removeCurvePoint()) {
            if(m_current_wire->deleteLastPoint()) {
                scene->removeItem(m_current_wire);
                m_current_wire = NULL;
                //scene->update();
            }
        } else if(m_current) {
            scene->removeItem(m_current);
            m_current = NULL;
            scene->update();
        }
        break;

    default:
        break;
    }
    QGraphicsView::mousePressEvent(event);
}

bool QSchemeView::event(QEvent *event)
{
    QGraphicsView::event(event);
    //std::cout<<event->type()<<std::endl;
    switch(event->type()) {
    case QEvent::Resize:
        std::cout<<"resize"<<std::endl;
        break;

    case QEvent::Enter:
        if(!m_current_wire) {
            if(m_current) {
                scene->removeItem(m_current);
                scene->update();
            }
            m_current = new QGraphicsChip(m_model->current());
            scene->addItem(m_current);
        }
        break;

    case QEvent::Leave:
        if(m_current) {
            scene->removeItem(m_current);
            m_current = NULL;
            scene->update();
        }
        break;

    default:
        QGraphicsView::event(event);
    }

    return true;
}
