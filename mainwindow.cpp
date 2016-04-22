#include "mainwindow.h"
#include "elemwidget.h"
#include <QSplitter>
#include <QLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ElemWidget *Elem = new ElemWidget;

    TreeV = new QTreeView;

    QSplitter *VSplt = new QSplitter;
    VSplt->setOrientation(Qt::Vertical);
    VSplt->addWidget(TreeV);
    VSplt->addWidget(Elem);

    QVBoxLayout *generalLayout = new QVBoxLayout;
    generalLayout->addWidget(VSplt);

    QWidget *widg = new QWidget;
    widg ->setLayout(generalLayout);
    setCentralWidget(widg);
}

MainWindow::~MainWindow()
{

}
