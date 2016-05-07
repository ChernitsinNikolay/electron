#include "mainwindow.h"
#include <QTreeView>
#include <QGraphicsView>
#include <QVBoxLayout>
//#include "qlibs/qtreemodel.h"
//#include "models/appmodel.h"
#include <iostream>
#include "elemwidget.h"
#include <QLayout>
#include <QWidget>
#include <QSplitter>
#include <QMenuBar>
#include "qschemeview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), treeModel(0), preview(0), scheme(0)
{
    Elem = new ElemWidget;
    Scheme = new QSchemeView;
    TreeV = new QTreeView(this);
    TreeV->setUniformRowHeights(true);
    TreeV->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QMenu *file = menuBar()->addMenu("File");
    QMenu *view = menuBar()->addMenu("View");
    QMenu *edit = menuBar()->addMenu("Edit");

    QVBoxLayout *generalLayout = new QVBoxLayout;
    generalLayout->setMargin(0);
    generalLayout->addWidget(TreeV);
    generalLayout->addWidget(Elem);

    QWidget *leftWidget = new QWidget;
    leftWidget->setLayout(generalLayout);

    QSplitter *mainSplitter = new QSplitter (Qt::Horizontal);
    mainSplitter->addWidget(leftWidget);
    mainSplitter->addWidget(Scheme);

    setCentralWidget(mainSplitter);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setElectron(Electron *electron)
{
    m_electron = electron;
    TreeV->setModel(0);
    delete treeModel;
    delete preview;
    delete scheme;
    treeModel = new QTreeModel(this, m_electron->tree());
    preview = new QPreviewModel(this, m_electron);
    scheme = new QSchemeModel(this, m_electron);
    TreeV->setModel(treeModel);
    Elem->setModel(preview);
    static_cast<QSchemeView*>(Scheme)->setModel(scheme);
    connect(TreeV->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), preview, SLOT(currentChanged(QModelIndex,QModelIndex)));
}
