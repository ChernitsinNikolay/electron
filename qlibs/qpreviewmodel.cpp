#include "qpreviewmodel.h"
#include "qtreemodel.h"
#include <QMetaType>
#include <iostream>

QPreviewModel::QPreviewModel(QObject *parent, Electron *electron) :
    QObject(parent), m_electron(electron)
{
}

ElectronItem *QPreviewModel::current() const
{
    return m_electron->current();
}

void QPreviewModel::currentChanged(QModelIndex current, QModelIndex previous)
{
    Q_UNUSED(previous);
    QVariant var = current.data(QTreeModel::ItemReference);
    if(var.canConvert(QMetaType::type("ElectronItem"))) {
        ElectronItem item = qvariant_cast<ElectronItem>(var);
        m_electron->setCurrent(item);
        std::cout<<"good\t"<<QString::fromStdString(item.name()).toLocal8Bit().toStdString()<<std::endl;
        emit currentUpdated();
    }
}

void QPreviewModel::rotateLeft()
{
    m_electron->rotateCurrent(90);
    emit currentUpdated();
}

void QPreviewModel::rotateRight()
{
    m_electron->rotateCurrent(-90);
    emit currentUpdated();
}

void QPreviewModel::reflectX()
{
    m_electron->reflectCurrent(ElectronAxis::X);
    emit currentUpdated();
}

void QPreviewModel::reflectY()
{
    m_electron->reflectCurrent(ElectronAxis::Y);
    emit currentUpdated();
}

