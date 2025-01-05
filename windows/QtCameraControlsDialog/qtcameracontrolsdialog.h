#pragma once

#include <QDialog>
#include "ui_QtCameraControlsDialog.h"
#include "../../widgets/QtFormatTableWidgetItem/qtcameraformattablewidgetitem.h"
#include <algorithm>
#include <QListWidget>
#include <QtMultimedia>
#include <QMessageBox>

class QtCameraControlsDialog : public QDialog
{
	Q_OBJECT

public:
	QtCameraControlsDialog(QCamera* camera, QMediaCaptureSession* cap, QWidget* parent = nullptr);
	~QtCameraControlsDialog();

	static QString sizeToString(QSize size);
	static QSize stringToSize(const QString& str);

private:
	Ui::QtCameraControlsDialogClass ui;
	QCamera* pCamera;
	QMediaCaptureSession* pCaptureSession;
	QString mName;
	QList<QCameraFormat> mFormats;
	QCameraFormat defaultFormat;
	QCameraFormat selectedFormat;

	void populateFilterDropdowns();

	void initializeExposureModes();
	void initializeFlashModes();
	void initializeFocusModes();
	void initializeTorchModes();
	void initializeWhiteBalanceModes();

	void initializeFormatGroup();
	void initializeZoomFocusGroup();
	void initializeSettingsGroup();

	void connectSettingsControls();
	void connectFormatControls();

	void resetFilters();

public slots:
	void updateFormatTable();
	void onFormatClicked(int row, int column);
	void onSelectClicked();

	void openFFPMEGSettings();
};
