#ifndef QPREVIEWMODEL_H
#define QPREVIEWMODEL_H

#include <QObject>
#include <QModelIndex>
#include "components/electron.h"

class QPreviewModel : public QObject
{
    Q_OBJECT
public:
    explicit QPreviewModel(QObject *parent = 0, Electron *electron = 0);

signals:

public slots:
    void currentChanged(QModelIndex current, QModelIndex previous);
    void RotateLeft();
    void RotateRight();
    void ReflectX();
    void ReflectY();
private:
    Electron *m_electron;
};

#endif // QPREVIEWMODEL_H
