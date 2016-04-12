#include "qtreemodel.h"

QTreeModel::QTreeModel(QObject *parent) :
    QAbstractItemModel(parent),
    ElectronicComponentsModel()
{
}

QTreeModel::~QTreeModel()
{}

QModelIndex QTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (!parent.isValid()) {
        Q_ASSERT((int)m_elcomps.size() > row);
        return createIndex(row, column, m_elcomps[row]);
    }

    Tree<ElectronicComponent> *parentInfo = static_cast<Tree<ElectronicComponent>*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);
    Q_ASSERT((int)parentInfo->size() > row);
    return createIndex(row, column, (*parentInfo)[row]);
}

QModelIndex QTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }

    Tree<ElectronicComponent>* childInfo = static_cast<Tree<ElectronicComponent>*>(child.internalPointer());
    Q_ASSERT(childInfo != 0);
    Tree<ElectronicComponent>* parentInfo = childInfo->getParent();
    if (parentInfo != 0 && parentInfo != &m_elcomps)
        return createIndex(findRow(parentInfo), 0, parentInfo);
    return QModelIndex();
}

int QTreeModel::findRow(const Tree<ElectronicComponent> *nodeInfo) const
{
    Q_ASSERT(nodeInfo != 0);
    const Tree<ElectronicComponent>* parentInfoChildren = nodeInfo->getParent() != 0 ? nodeInfo->getParent(): &m_elcomps;
    for(std::size_t i = 0; i < parentInfoChildren->size(); i++)
        if(nodeInfo == (*parentInfoChildren)[i])
            return i;
    return 0;
}

int QTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_elcomps.size();
    const Tree<ElectronicComponent>* parentInfo = static_cast<const Tree<ElectronicComponent>*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);
    return parentInfo->size();
}

int QTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant QTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    const Tree<ElectronicComponent>* nodeInfo = static_cast<Tree<ElectronicComponent>*>(index.internalPointer());
    Q_ASSERT(nodeInfo != 0);
    return nameData(*nodeInfo, role);
}

QVariant QTreeModel::nameData(const Tree<ElectronicComponent> &nodeInfo, int role) const
{
    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        return QString::fromStdString(nodeInfo.value().getName());
    default:
        return QVariant();
    }
    Q_UNREACHABLE();
}

QVariant QTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    const QStringList headers = {"Элементы"};
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section < headers.size()) {
        return headers[section];
    }
    return QVariant();
}
