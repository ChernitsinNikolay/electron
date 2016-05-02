#include "qtreemodel.h"

QTreeModel::QTreeModel(QObject *parent, ElectronTree *eltree) :
    QAbstractItemModel(parent),
    m_eltree(eltree)
{ }

QTreeModel::~QTreeModel()
{ }

QModelIndex QTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (!parent.isValid()) {
        Q_ASSERT((int)m_eltree->childrenSize() > row);
        return createIndex(row, column, (*m_eltree)[row]);
    }

    const ElectronTree* parentInfo = static_cast<ElectronTree*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);
    Q_ASSERT((int)parentInfo->childrenSize() > row);
    return createIndex(row, column, (*parentInfo)[row]);
}

QModelIndex QTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }

    const ElectronTree* childInfo = static_cast<ElectronTree*>(child.internalPointer());
    Q_ASSERT(childInfo != 0);

    return findParent(m_eltree, childInfo);
}

QModelIndex QTreeModel::findParent(ElectronTree *tree, const ElectronTree *item) const
{
    /*if(tree == item)
        return QModelIndex();
    for(size_t i = 0; i < tree->childrenSize(); i++) {
        if((*tree)[i] == item)
            return createIndex(i, 0, tree);
        if((*tree)[i]->childrenSize() > 0) {
            QModelIndex index = findParent((*tree)[i], item);
            if(index.isValid())
                return index;
        }
    }*/
    return QModelIndex();
}

/*int QTreeModel::findRow(const NodeInfo *nodeInfo) const
{
    Q_ASSERT(nodeInfo != 0);
    const NodeInfoList& parentInfoChildren = nodeInfo->parent != 0 ? nodeInfo->parent->children: _nodes;
    NodeInfoList::const_iterator position = qFind(parentInfoChildren, *nodeInfo);
    Q_ASSERT(position != parentInfoChildren.end());
    return std::distance(parentInfoChildren.begin(), position);
}*/

int QTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return m_eltree->childrenSize();
    }
    const ElectronTree* parentInfo = static_cast<const ElectronTree*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);

    return parentInfo->childrenSize();
}

int QTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant QTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const ElectronTree* nodeInfo = static_cast<ElectronTree*>(index.internalPointer());
    Q_ASSERT(nodeInfo != 0);
    return nameData(nodeInfo, role);
}

QVariant QTreeModel::nameData(const ElectronTree* &item, int role) const
{
    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        return QString::fromStdString(item->value().name());
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
