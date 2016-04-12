#include "mainwindow.h"
#include <QTreeView>
#include "qlibs/qtreemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTreeView *tv = new QTreeView(this);
    setCentralWidget(tv);
    tv->setUniformRowHeights(true);
    tv->setModel(new QTreeModel(this));
}

MainWindow::~MainWindow()
{

}
