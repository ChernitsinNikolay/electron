#ifndef QTREEMODEL_H
#define QTREEMODEL_H

#include <QAbstractItemModel>
#include "models/electroniccomponentsmodel.h"

class QTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum ItemDataRole {
        ItemReference = Qt::UserRole + 1
    };

    QTreeModel(QObject *parent = 0, ElectronicComponentsModel *ecmodel = 0);
    virtual ~QTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);

    bool hasChildren(const QModelIndex &parent) const;

private:
    struct NodeInfo;
    typedef QVector<NodeInfo> NodeInfoList;
    NodeInfoList _nodes;
    ElectronicComponentsModel *m_ecmodel;

    void fetchRootDirectory();
    int findRow(const NodeInfo* nodeInfo) const;
    QVariant nameData(const QString& name, int role) const;
};

#endif // QTREEMODEL_H
