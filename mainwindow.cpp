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
#include <QFileDialog>
#include "qschemeview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), treeModel(0), preview(0), scheme(0)
{
    Elem = new ElemWidget;
    Scheme = new QSchemeView;
    TreeV = new QTreeView(this);
    TreeV->setUniformRowHeights(true);
    TreeV->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mfile = menuBar()->addMenu(QString::fromUtf8("Файл"));
    QAction *anew = mfile->addAction(QString::fromUtf8("Создать"));
    QAction *aopen = mfile->addAction(QString::fromUtf8("Открыть"));
    QAction *asave = mfile->addAction(QString::fromUtf8("Сохранить"));
    mfile->addSeparator();
    QAction *aexit = mfile->addAction(QString::fromUtf8("Выход"));
    mview = menuBar()->addMenu(QString::fromUtf8("Вид"));
    mview->addAction(QString::fromUtf8("Увеличить"))->setEnabled(false);
    mview->addAction(QString::fromUtf8("Уменьшить"))->setEnabled(false);
    mview->addAction(QString::fromUtf8("Вместить"))->setEnabled(false);
    medit = menuBar()->addMenu(QString::fromUtf8("Правка"));
    medit->addAction(QString::fromUtf8("Отменить"))->setEnabled(false);
    medit->addAction(QString::fromUtf8("Вернуть"))->setEnabled(false);
    medit->addSeparator();
    medit->addAction(QString::fromUtf8("Вырезать"))->setEnabled(false);
    medit->addAction(QString::fromUtf8("Копировать"))->setEnabled(false);
    medit->addAction(QString::fromUtf8("Вставить"))->setEnabled(false);
    mhelp = menuBar()->addMenu(QString::fromUtf8("Справка"));
    mhelp->addAction(QString::fromUtf8("Справка"))->setEnabled(false);
    mhelp->addSeparator();
    mhelp->addAction(QString::fromUtf8("О программе"))->setEnabled(false);

    connect(anew, SIGNAL(triggered()), SLOT(newScheme()));
    connect(aopen, SIGNAL(triggered()), SLOT(openScheme()));
    connect(asave, SIGNAL(triggered()), SLOT(saveScheme()));
    connect(aexit, SIGNAL(triggered()), SLOT(close()));

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

void MainWindow::newScheme()
{
    m_electron->newScheme();
    scheme->update();
}

void MainWindow::openScheme()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Открыть схему"),
                                                 "",
                                                 tr("Scheme (*.sch)"));
    if(!fname.isEmpty()) {
        m_electron->loadFromFile(fname.toStdString());
        scheme->update();
    }
}

void MainWindow::saveScheme()
{
    QString fname = QFileDialog::getSaveFileName(this, tr("Сохранить схему"),
                                                 "untitled.sch",
                                                 tr("Scheme (*.sch)"));
    if(!fname.isEmpty()) {
        m_electron->saveToFile(fname.toStdString());
        scheme->update();
    }
}
