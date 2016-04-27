#ifndef ELEMWIDGET_H
#define ELEMWIDGET_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPushButton>
#include <QtGui>
#include <QtCore>

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
    QGraphicsRectItem *rectangle;
    QGraphicsLineItem *lineUp;
    QGraphicsLineItem *lineDowm;
private slots:
    void RotateLeft();
    void RotateRight();
    void ReflectX();
    void ReflectY();
};

#endif // ELEMWIDGET_H
