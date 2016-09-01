#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TexasHoldemView::MainWindow w;
    w.show();

    return a.exec();
}
