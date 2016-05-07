#ifndef QSCHEMEVIEW_H
#define QSCHEMEVIEW_H
#include <QGraphicsView>
#include "qlibs/qschememodel.h"

class QSchemeView : public QGraphicsView
{
    Q_OBJECT
public:
    QSchemeView(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool event(QEvent *event);

public slots:
    void setModel(QSchemeModel *model);

private:
    QGraphicsScene *scene;
    QSchemeModel *m_model;
    QGraphicsItem *m_current;
};

#endif // QSCHEMEVIEW_H
