#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QTreeView>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent);
private:
    QTreeView *TreeV;
};

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
#endif // MAINWINDOW_H
