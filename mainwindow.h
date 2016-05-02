#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include "components/electron.h"
#include "qlibs/qtreemodel.h"
#include <QTreeView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setElectronTree(ElectronTree *tree);

private slots:
    void currentChanged(QModelIndex old, QModelIndex current);

private:
    QTreeModel *treeModel;
    QTreeView *tv;
};

#endif // MAINWINDOW_H
