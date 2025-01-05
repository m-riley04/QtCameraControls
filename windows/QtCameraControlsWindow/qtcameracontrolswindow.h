#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtcameracontrolswindow.h"

class QtCameraControlsWindow : public QMainWindow
{
    Q_OBJECT

public:
    QtCameraControlsWindow(QWidget *parent = nullptr);
    ~QtCameraControlsWindow();

private:
    Ui::QtCameraControlsWindow ui;
};
