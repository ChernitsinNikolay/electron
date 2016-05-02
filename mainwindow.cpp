#include "mainwindow.h"
#include <QTreeView>
#include <QGraphicsView>
#include <QVBoxLayout>
//#include "qlibs/qtreemodel.h"
//#include "models/appmodel.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), treeModel(0)
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

    connect(tv->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(currentChanged(QModelIndex,QModelIndex)));
    QGraphicsScene *scene = new QGraphicsScene;
    graphicsView->setScene(scene);
    //scene->add
}

MainWindow::~MainWindow()
{

}

void MainWindow::currentChanged(QModelIndex old, QModelIndex current)
{
    /*std::cout<<old.data().toString().toLocal8Bit().toStdString()<<"\t"<<old.data(QTreeModel::ItemReference).typeName()<<std::endl;
    if(old.data(QTreeModel::ItemReference).canConvert(QMetaType::type("QTreeModel::QItemType"))) {
        QTreeModel::QItemType type = qvariant_cast<QTreeModel::QItemType>(old.data(QTreeModel::ItemReference));
        std::cout<<QString::fromUtf8(type.getName().c_str()).toLocal8Bit().toStdString()<<std::endl;
        //std::cout<<old.data(Qt::UserRole).<<std::endl;
    }*/
    //old.internalPointer()
}

void MainWindow::setElectronTree(ElectronTree *tree)
{
    tv->setModel(0);
    delete treeModel;
    treeModel = new QTreeModel(this, tree);
    tv->setModel(treeModel);
}
