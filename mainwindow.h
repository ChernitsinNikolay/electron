#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <elemwidget.h>
#include <QMainWindow>
#include <QModelIndex>
#include "components/electron.h"
#include "qlibs/qtreemodel.h"
#include "qlibs/qpreviewmodel.h"
#include <QTreeView>
#include <QPushButton>
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setElectron(Electron *electron);

private:
    Electron *m_electron;
    QTreeModel *treeModel;
    QPreviewModel *preview;
    QTreeView *TreeV;
    QGraphicsView *Scheme;
    ElemWidget *Elem;
};

#endif // MAINWINDOW_H
