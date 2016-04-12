#ifndef QTREEMODEL_H
#define QTREEMODEL_H

#include <QAbstractItemModel>

#include "models/electroniccomponentsmodel.h"

class QTreeModel : public QAbstractItemModel, ElectronicComponentsModel
{
    Q_OBJECT
public:
    explicit QTreeModel(QObject *parent = 0);
    ~QTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    int findRow(const Tree<ElectronicComponent>* nodeInfo) const;
    QVariant nameData(const Tree<ElectronicComponent> &nodeInfo, int role) const;
};

#endif // QTREEMODEL_H
