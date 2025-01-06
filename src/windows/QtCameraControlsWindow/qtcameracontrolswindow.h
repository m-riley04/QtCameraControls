#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtcameracontrolswindow.h"
#include <QtMultimedia>
#include "src/windows/QtCameraControlsDialog/qtcameracontrolsdialog.h"

class QtCameraControlsWindow : public QMainWindow
{
    Q_OBJECT

public:
    QtCameraControlsWindow(QWidget *parent = nullptr);
    ~QtCameraControlsWindow();

public slots:
	void refreshCameraDevices();
    QCameraDevice findDeviceFromIndex(int index);

private:
    Ui::QtCameraControlsWindow ui;
    QCamera* pCamera;
	QMediaCaptureSession* pCaptureSession;
};
