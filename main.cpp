#include "mainwindow.h"
#include <QApplication>
#include "components/electron.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Electron electron;

    MainWindow w;
    w.setElectronTree(electron.tree());
    w.show();

    return a.exec();
}
