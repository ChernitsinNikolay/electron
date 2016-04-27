#include "elemwidget.h"
#include <QSplitter>
#include <QLayout>
#include <QMenu>
#include <QWidget>
#include <QToolButton>

ElemWidget::ElemWidget(QWidget *parent) : QWidget(parent)
{
    RotLeft = new QPushButton;
    RotLeft->setIcon(QIcon(":/left.png"));
    RotLeft->setIconSize(QSize(35,35));

    RotRight = new QPushButton;
    RotRight->setIcon(QIcon(":/right.png"));
    RotRight->setIconSize(QSize(35,35));

    RefX = new QPushButton;
    RefX->setIcon(QIcon(":/side.png"));
    RefX->setIconSize(QSize(35,35));

    RefY = new QPushButton;
    RefY->setIcon(QIcon(":/updown.png"));
    RefY->setIconSize(QSize(35,35));

    graphicsView = new QGraphicsView;

    scene = new QGraphicsScene;

    graphicsView->setScene(scene);
    QPen blackpen(Qt::black);
    QPen redpen(Qt::red);
    QBrush whitebrush(Qt::white);
    blackpen.setWidth(2);
    redpen.setWidth(2);
    rectangle = scene ->addRect(10,10,50,100,blackpen,whitebrush);
    lineUp = scene ->addLine(35,10,35,-20,redpen);
    lineDowm = scene ->addLine(35,112,35,142,blackpen);
    //rectangle ->setFlag(QGraphicsItem::ItemIsMovable);

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

    connect(RotLeft,SIGNAL(clicked()),this,SLOT(RotateLeft()));
    connect(RotRight,SIGNAL(clicked()),this,SLOT(RotateRight()));
    connect(RefX,SIGNAL(clicked()),this,SLOT(ReflectX()));
    connect(RefY,SIGNAL(clicked()),this,SLOT(ReflectY()));

    setLayout(ElemLayout);

}

void ElemWidget::RotateLeft()
{
    graphicsView->rotate(-90);
}

void ElemWidget::RotateRight()
{
    graphicsView->rotate(90);
}

void ElemWidget::ReflectX()
{
    graphicsView->rotate(180);
}

void ElemWidget::ReflectY()
{
    graphicsView->rotate(180);
}

