#ifndef QTREEMODEL_H
#define QTREEMODEL_H

#include <QAbstractItemModel>
#include <QMetaType>
#include "components/electron.h"

class QTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum ItemDataRole {
        ItemReference = Qt::UserRole + 1
    };

    QTreeModel(QObject *parent = 0, const ElectronTree *eltree = 0);
    virtual ~QTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    const ElectronTree *m_eltree;

    //int findRow(const NodeInfo* nodeInfo) const;
    QModelIndex findParent(ElectronTree *tree, const ElectronTree *item) const;
    QVariant nameData(const ElectronTree &item, int role) const;
};
Q_DECLARE_METATYPE(ElectronItem)

#endif // QTREEMODEL_H
