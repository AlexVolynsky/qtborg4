#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString fileName;

    if (argc >= 2)
        fileName = argv[1];
    else
        fileName = ".";

    TabDialog tabdialog(fileName);
    tabdialog.show();

    return app.exec();
}
