#include "mainwindow.h"
#include <QSplitter>
#include <QLayout>
#include <QMenu>

ElemWidget::ElemWidget(QWidget *parent) : QWidget(parent)
{
    RotLeft = new QPushButton("RotL");
    RotRight = new QPushButton("RotR");
    RefX = new QPushButton("RefX");
    RefY = new QPushButton("RefY");

    graphicsView = new QGraphicsView;

    QVBoxLayout *BtmLayout = new QVBoxLayout;
    BtmLayout->setMargin(0);
    BtmLayout->addWidget(RotLeft);
    BtmLayout->addWidget(RotRight);
    BtmLayout->addWidget(RefX);
    BtmLayout->addWidget(RefY);

    QHBoxLayout *ElemLayout = new QHBoxLayout;
    ElemLayout->setMargin(0);
    ElemLayout->addLayout(BtmLayout);
    ElemLayout->addWidget(graphicsView);

    setLayout(ElemLayout);
}

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{


    ElemWidget *Elem = new ElemWidget;

    TreeV = new QTreeView;

    QSplitter *VSplt = new QSplitter;
    VSplt->setOrientation(Qt::Vertical);
    VSplt->addWidget(TreeV);
    VSplt->addWidget(Elem);

    QVBoxLayout *generalLayout = new QVBoxLayout;
    generalLayout->addWidget(VSplt);
    setLayout(generalLayout);

}

