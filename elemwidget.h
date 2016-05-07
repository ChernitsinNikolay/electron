#ifndef ELEMWIDGET_H
#define ELEMWIDGET_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPushButton>
#include <QtGui>
#include <QtCore>
#include "qlibs/qpreviewmodel.h"

class ElemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ElemWidget(QWidget *parent = 0);

private:
    QPushButton *RotLeft;
    QPushButton *RotRight;
    QPushButton *RefX;
    QPushButton *RefY;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;

public slots:
    void setModel(QPreviewModel *model);
    void curentChanged();

private:
    QPreviewModel *m_model;
};

#endif // ELEMWIDGET_H
