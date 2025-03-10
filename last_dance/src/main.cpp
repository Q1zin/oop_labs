#include <QApplication>
#include <QMainWindow>
#include "include/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Last Dance");
    mainWindow.resize(1280, 720);
    mainWindow.setFixedSize(1280, 720);
    mainWindow.show();

    return app.exec();
}
