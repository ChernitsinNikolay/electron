#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <elemwidget.h>
#include <QMainWindow>
#include <QTreeView>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QTreeView *TreeV;
    ElemWidget *Elem;
};

#endif // MAINWINDOW_H
