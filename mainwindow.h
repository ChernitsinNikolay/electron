#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <elemwidget.h>
#include <QMainWindow>
#include <QModelIndex>
#include "components/electron.h"
#include "qlibs/qtreemodel.h"
#include "qlibs/qpreviewmodel.h"
#include "qlibs/qschememodel.h"
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
    void newScheme();
    void openScheme();
    void saveScheme();

private:
    Electron *m_electron;
    QTreeModel *treeModel;
    QPreviewModel *preview;
    QSchemeModel *scheme;
    QTreeView *TreeV;
    QGraphicsView *Scheme;
    ElemWidget *Elem;
    QMenu *mfile, *mview, *medit, *mhelp;
};

#endif // MAINWINDOW_H
