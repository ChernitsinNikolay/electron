#include "mainwindow.h"
#include <QTreeView>
#include <QGraphicsView>
#include <QVBoxLayout>
//#include "qlibs/qtreemodel.h"
//#include "models/appmodel.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), treeModel(0), preview(0)
{
    //AppModel *model = new AppModel();
    tv = new QTreeView(this);
    tv->setUniformRowHeights(true);
    tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //tv->setModel(new QTreeModel(this, model));
    QGraphicsView *graphicsView = new QGraphicsView(this);
    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(tv);
    vbl->addWidget(graphicsView);
    QWidget *central = new QWidget(this);
    central->setLayout(vbl);
    setCentralWidget(central);

    QGraphicsScene *scene = new QGraphicsScene;
    graphicsView->setScene(scene);
    //scene->add
}

MainWindow::~MainWindow()
{

}

void MainWindow::setElectron(Electron *electron)
{
    m_electron = electron;
    tv->setModel(0);
    delete treeModel;
    delete preview;
    treeModel = new QTreeModel(this, m_electron->tree());
    preview = new QPreviewModel(this, electron);
    tv->setModel(treeModel);
    connect(tv->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), preview, SLOT(currentChanged(QModelIndex,QModelIndex)));
}
