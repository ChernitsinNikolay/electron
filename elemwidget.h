#ifndef ELEMWIDGET_H
#define ELEMWIDGET_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>

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
};

#endif // ELEMWIDGET_H
