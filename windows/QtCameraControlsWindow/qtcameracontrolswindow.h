#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtcameracontrolswindow.h"

class QtCameraControls : public QMainWindow
{
    Q_OBJECT

public:
    QtCameraControls(QWidget *parent = nullptr);
    ~QtCameraControls();

private:
    Ui::QtCameraControlsClass ui;
};
