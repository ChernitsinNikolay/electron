#include "mainwindow.h"
#include "elemwidget.h"
#include <QLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Elem = new ElemWidget;

    TreeV = new QTreeView;

    QVBoxLayout *generalLayout = new QVBoxLayout;
    generalLayout->addWidget(TreeV);
    generalLayout->addWidget(Elem);

    QWidget *widg = new QWidget;
    widg ->setLayout(generalLayout);
    setCentralWidget(widg);
}

MainWindow::~MainWindow()
{

}
