#include "windows/QtCameraControlsWindow/qtcameracontrolswindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCameraControlsWindow w;
    w.show();
    return a.exec();
}
