#include "mainwindow.h"
#include "elemwidget.h"
#include <QLayout>
#include <QWidget>
#include <QSplitter>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Elem = new ElemWidget;
    Scheme = new QGraphicsView;
    TreeV = new QTreeView;

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
