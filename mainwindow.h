#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <elemwidget.h>
#include <QMainWindow>
#include <QTreeView>
#include <QPushButton>
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QTreeView *TreeV;
    QGraphicsView *Scheme;
    ElemWidget *Elem;
};

#endif // MAINWINDOW_H
