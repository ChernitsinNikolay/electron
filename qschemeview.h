#ifndef QSCHEMEVIEW_H
#define QSCHEMEVIEW_H
#include <QGraphicsView>
#include "qlibs/qschememodel.h"
#include "qlibs/qgraphicswire.h"

class QSchemeView : public QGraphicsView
{
    Q_OBJECT
public:
    QSchemeView(QWidget *parent = 0);

    QPointF mapToGridScene(const QPoint &point) const;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool event(QEvent *event);

public slots:
    void updateModel();
    void setModel(QSchemeModel *model);
    void wire(const QPointF &point);
    void userDeleteItemChip();
    void userDeleteItemWire();

private:
    QGraphicsScene *scene;
    QSchemeModel *m_model;
    QGraphicsItem *m_current;
    QGraphicsWire *m_current_wire;
    QGraphicsTextItem *m_text;
    float m_gridStep;
};

#endif // QSCHEMEVIEW_H
