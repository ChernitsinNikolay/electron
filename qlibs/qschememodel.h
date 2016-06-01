#ifndef QSCHEMEMODEL_H
#define QSCHEMEMODEL_H
#include <QObject>
#include "qlibs/qgraphicschip.h"
#include "qlibs/qgraphicswire.h"
#include "components/electron.h"

class QSchemeModel : public QObject
{
    Q_OBJECT
public:
    explicit QSchemeModel(QObject *parent = 0, Electron *electron = 0);

    ElectronItem *current() const;
    QVector<QGraphicsChip> chips() const;
    QGraphicsChip addItem(const QGraphicsChip &chip);
    void deleteItem(const QGraphicsChip &chip);
    QVector<QGraphicsWire> wires() const;
    QGraphicsWire addWire(const QGraphicsWire &wire);
    void deleteWire(const QGraphicsWire &wire);
    int size() const;

signals:
    void updated();

public slots:
    void update();

private:
    Electron *m_electron;
};

#endif // QSCHEMEMODEL_H
