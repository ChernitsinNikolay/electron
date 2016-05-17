#include "qschememodel.h"

QSchemeModel::QSchemeModel(QObject *parent, Electron *electron) :
    QObject(parent), m_electron(electron)
{

}

ElectronItem *QSchemeModel::current() const
{
    return m_electron->current();
}

QVector<QGraphicsChip> QSchemeModel::chips() const
{
    QVector<QGraphicsChip> tchip;//(m_electron->scheme()->wsize());
    for(size_t i = 0; i < m_electron->scheme()->csize(); i++)
        tchip.push_back(QGraphicsChip(m_electron->scheme()->chipAt(i)));
    return tchip;
}

QVector<QGraphicsWire> QSchemeModel::wires() const
{
    QVector<QGraphicsWire> twire;//(m_electron->scheme()->wsize());
    for(size_t i = 0; i < m_electron->scheme()->wsize(); i++)
        twire.push_back(QGraphicsWire(m_electron->scheme()->wireAt(i)));
    return twire;
}

QGraphicsChip QSchemeModel::addItem(const QGraphicsChip &chip)
{
    return QGraphicsChip(m_electron->scheme()->addItem(*chip.boundItem()));
}

void QSchemeModel::deleteItem(const QGraphicsChip &chip)
{
    m_electron->scheme()->deleteItem(*chip.boundItem());
    //m_electron->scheme()->deleteItem(ElectronElement());
}

QGraphicsWire QSchemeModel::addWire(const QGraphicsWire &wire)
{
    return QGraphicsWire(m_electron->scheme()->addWire(*wire.boundItem(), *wire.fromItem()->boundItem(), *wire.toItem()->boundItem()));
}

void QSchemeModel::deleteWire(const QGraphicsWire &wire)
{
    m_electron->scheme()->deleteWire(*wire.boundItem());
    //m_electron->scheme()->deleteWire(ElectronWire());
}

void QSchemeModel::update()
{
    emit updated();
}
