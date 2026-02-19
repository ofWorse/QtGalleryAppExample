#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QDir dir;
    if(!dir.exists("images"))
    {
        dir.mkdir("images");
        qDebug() << "Folder 'images' was created. Put some images there.";
    }

    MainWindow window;
    window.show();

    return app.exec();
}
