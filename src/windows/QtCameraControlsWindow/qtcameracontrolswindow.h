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
	/// <summary>
	/// Refreshes the camera devices dropdown from QMediaDevices
	/// </summary>
	void refreshCameraDevices();

    /// <summary>
	/// Finds a camera device from the dropdown index
    /// </summary>
    /// <param name="index">The index from the device dropdown</param>
    /// <returns></returns>
    QCameraDevice findDeviceFromIndex(int index);

    void initializeMenuBar();
    void initializeWidgets();

private:
    Ui::QtCameraControlsWindow ui;
    QCamera* pCamera;
	QMediaDevices* pMediaDevices;
	QMediaCaptureSession* pCaptureSession;
};
