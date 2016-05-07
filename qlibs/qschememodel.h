#ifndef QSCHEMEMODEL_H
#define QSCHEMEMODEL_H
#include <QObject>
#include "qlibs/qgraphicschip.h"
#include "components/electron.h"

class QSchemeModel : public QObject
{
    Q_OBJECT
public:
    explicit QSchemeModel(QObject *parent = 0, Electron *electron = 0);

    ElectronItem *current() const;
    QGraphicsChip addItem(const QGraphicsChip &chip);

signals:

public slots:

private:
    Electron *m_electron;
};

#endif // QSCHEMEMODEL_H
