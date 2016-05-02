#include "qtreemodel.h"

struct QTreeModel::NodeInfo
{
    NodeInfo():
        m_id(0),
        parent(0),
        mapped(false)
    {}

    NodeInfo(const uint64_t &id, QString name, NodeInfo* parent = 0):
        m_name(name),
        m_id(id),
        parent(parent),
        mapped(false)
    {}

    bool operator ==(const NodeInfo& another) const
    {
        bool r = this->m_id == another.m_id;
        Q_ASSERT(!r || this->parent == another.parent);
        Q_ASSERT(!r || this->mapped == another.mapped);
        Q_ASSERT(!r || this->children == another.children);
        return r;
    }

    QString m_name;
    uint64_t m_id;
    QVector<NodeInfo> children;
    NodeInfo* parent;

    bool mapped;
};

QTreeModel::QTreeModel(QObject *parent, ElectronicComponentsModel *ecmodel) :
    QAbstractItemModel(parent),
    m_ecmodel(ecmodel)
{
    fetchRootDirectory();
}

QTreeModel::~QTreeModel()
{
}

QModelIndex QTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (!parent.isValid()) {
        Q_ASSERT(_nodes.size() > row);
        return createIndex(row, column, const_cast<NodeInfo*>(&_nodes[row]));
    }

    NodeInfo* parentInfo = static_cast<NodeInfo*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);
    Q_ASSERT(parentInfo->mapped);
    Q_ASSERT(parentInfo->children.size() > row);
    return createIndex(row, column, &parentInfo->children[row]);
}

QModelIndex QTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }

    NodeInfo* childInfo = static_cast<NodeInfo*>(child.internalPointer());
    Q_ASSERT(childInfo != 0);
    NodeInfo* parentInfo = childInfo->parent;
    if (parentInfo != 0) {
        return createIndex(findRow(parentInfo), 0, parentInfo);
    }
    else {
        return QModelIndex();
    }
}

int QTreeModel::findRow(const NodeInfo *nodeInfo) const
{
    Q_ASSERT(nodeInfo != 0);
    const NodeInfoList& parentInfoChildren = nodeInfo->parent != 0 ? nodeInfo->parent->children: _nodes;
    NodeInfoList::const_iterator position = qFind(parentInfoChildren, *nodeInfo);
    Q_ASSERT(position != parentInfoChildren.end());
    return std::distance(parentInfoChildren.begin(), position);
}

int QTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return _nodes.size();
    }
    const NodeInfo* parentInfo = static_cast<const NodeInfo*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);

    return parentInfo->children.size();
}

bool QTreeModel::hasChildren(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        const NodeInfo* parentInfo = static_cast<const NodeInfo*>(parent.internalPointer());
        Q_ASSERT(parentInfo != 0);
        if (!parentInfo->mapped) {
            return true;//QDir(parentInfo->fileInfo.absoluteFilePath()).count() > 0;
        }
    }
    return QAbstractItemModel::hasChildren(parent);
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

    const NodeInfo* nodeInfo = static_cast<NodeInfo*>(index.internalPointer());
    const QString& name = nodeInfo->m_name;
    Q_ASSERT(nodeInfo != 0);
    return nameData(name, role);
}

QVariant QTreeModel::nameData(const QString &name, int role) const
{
    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        return name;
    default:
        return QVariant();
    }
    Q_UNREACHABLE();
}

QVariant QTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    const QStringList headers = {"Имя", "Дата изменения", "Размер", "Тип"};
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section < headers.size()) {
        return headers[section];
    }
    return QVariant();
}

bool QTreeModel::canFetchMore(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return false;
    }

    const NodeInfo* parentInfo = static_cast<const NodeInfo*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);
    return !parentInfo->mapped;
}

void QTreeModel::fetchMore(const QModelIndex &parent)
{
    Q_ASSERT(parent.isValid());
    NodeInfo* parentInfo = static_cast<NodeInfo*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);
    Q_ASSERT(!parentInfo->mapped);

    const uint64_t& id = parentInfo->m_id;

    beginInsertRows(parent, 0, m_ecmodel->size(id));
    for(size_t i = 0; i < m_ecmodel->size(id); i++) {
        uint64_t tid = m_ecmodel->id(id, i);
        parentInfo->children.push_back(NodeInfo(tid, QString::fromStdString(m_ecmodel->name(tid)), parentInfo));
    }
    parentInfo->mapped = true;
    endInsertRows();
}

void QTreeModel::fetchRootDirectory()
{
    //const QFileInfoList drives = QDir::drives();
    //qCopy(drives.begin(), drives.end(), std::back_inserter(_nodes));
    for(size_t i = 0; i < m_ecmodel->size(0); i++) {
        uint64_t id = m_ecmodel->id(0, i);
        _nodes.push_back(NodeInfo(id, QString::fromStdString(m_ecmodel->name(id))));
    }
}
