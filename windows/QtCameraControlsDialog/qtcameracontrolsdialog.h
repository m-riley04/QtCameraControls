#pragma once

#include <QMainWindow>
#include "ui_qtcameracontrolsdialog.h"

class QtCameraControlsDialog : public QMainWindow
{
	Q_OBJECT

public:
	QtCameraControlsDialog(QWidget *parent = nullptr);
	~QtCameraControlsDialog();

private:
	Ui::QtCameraControlsDialogClass ui;
};
