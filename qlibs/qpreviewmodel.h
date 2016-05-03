#ifndef QPREVIEWMODEL_H
#define QPREVIEWMODEL_H

#include <QObject>
#include <QModelIndex>
#include "components/electron.h"
#include "qlibs/qgraphicschip.h"

class QPreviewModel : public QObject
{
    Q_OBJECT
public:
    explicit QPreviewModel(QObject *parent = 0, Electron *electron = 0);

    QGraphicsChip *current() const;

signals:
    void currentUpdated();

public slots:
    void currentChanged(QModelIndex current, QModelIndex previous);
    void rotateLeft();
    void rotateRight();
    void reflectX();
    void reflectY();

private:
    Electron *m_electron;
};

#endif // QPREVIEWMODEL_H
