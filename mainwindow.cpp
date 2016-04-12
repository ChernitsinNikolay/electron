#include "mainwindow.h"
#include <QTreeView>
#include "qlibs/qtreemodel.h"
#include "models/electroniccomponentsmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTreeView *tv = new QTreeView(this);
    setCentralWidget(tv);
    tv->setUniformRowHeights(true);
    tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv->setModel(new QTreeModel(this));
}

MainWindow::~MainWindow()
{

}
