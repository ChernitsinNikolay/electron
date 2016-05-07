#include "qschemeview.h"
#include <iostream>
#include <QEvent>
#include <QMouseEvent>
#include "qlibs/qgraphicschip.h"

QSchemeView::QSchemeView(QWidget *parent) :
    QGraphicsView(parent), m_model(0), m_current(0)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setBackgroundBrush(QBrush(Qt::gray));
    setMouseTracking(true);
}

void QSchemeView::setModel(QSchemeModel *model)
{
    m_model = model;
}

void QSchemeView::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_current)
        return;
    m_current->setPos(mapToScene(event->pos()));
}

void QSchemeView::mousePressEvent(QMouseEvent *event)
{
    //std::cout<<"press"<<std::endl;
    switch(event->button()) {
    case Qt::LeftButton:
        break;

    case Qt::RightButton:
        break;

    default:
        break;
    }
}

bool QSchemeView::event(QEvent *event)
{
    //std::cout<<event->type()<<std::endl;
    switch(event->type()) {
    case QEvent::Enter:
        if(m_current) {
            scene->removeItem(m_current);
            scene->update();
        }
        m_current = new QGraphicsChip(m_model->current());
        scene->addItem(m_current);
        m_current->setScale(2);
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
