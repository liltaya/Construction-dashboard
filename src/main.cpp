#include "construction/MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    construction::MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}