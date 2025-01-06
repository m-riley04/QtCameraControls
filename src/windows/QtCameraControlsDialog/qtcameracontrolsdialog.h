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

	/// <summary>
	/// Converts a QSize to a formatted string.
	/// </summary>
	/// <param name="size"></param>
	/// <returns>A QString of the form "[width]x[height]</returns>
	static QString sizeToString(QSize size);

	/// <summary>
	/// Converts a formatted QString to a QSize.
	/// </summary>
	/// <param name="str">A QString of the form "[width]x[height]"</param>
	/// <returns>A QSize with the corresponding width and height.</returns>
	static QSize stringToSize(const QString& str);

private:
	Ui::QtCameraControlsDialogClass ui;
	QCamera* pCamera;
	QMediaCaptureSession* pCaptureSession;
	QString mName;
	QList<QCameraFormat> mFormats;
	QCameraFormat defaultFormat;
	QCameraFormat selectedFormat;

	/// <summary>
	/// Popualtes the FPS, Resolution, and Pixel Format dropdowns based on the current formats.
	/// </summary>
	void populateFilterDropdowns();

	/// <summary>
	/// Populates the exposure mode dropdown based on the supported modes.
	/// </summary>
	void populateExposureModes();

	/// <summary>
	/// Populates the flash mode dropdown based on the supported modes.
	/// </summary>
	void populateFlashModes();

	/// <summary>
	/// Populates the torch mode dropdown based on the supported modes.
	/// </summary>
	void populateTorchModes();

	/// <summary>
	/// Populates the white balance mode dropdown based on the supported modes.
	/// </summary>
	void populateWhiteBalanceModes();

	/// <summary>
	/// Populates the focus mode dropdown based on the supported modes.
	/// </summary>
	void populateFocusModes();

	/// <summary>
	/// Initializes the supported features by toggling the corresponding UI elements.
	/// </summary>
	void initializeSupportedFeatures();

	void initializeFormatGroup();
	void initializeZoomFocusGroup();
	void initializeSettingsGroup();

	void connectFormatControls();
	void connectZoomFocusControls();
	void connectSettingsControls();

	/// <summary>
	/// Resets the dropdown filters for the format table.
	/// </summary>
	void resetFilters();

public slots:
	/// <summary>
	/// Updates the format table based on the current dropdown filters.
	/// </summary>
	void updateFormatTable();

	/// <summary>
	/// Slot that is called when a format is clicked in the format table.
	/// </summary>
	/// <param name="row"></param>
	/// <param name="column"></param>
	void onFormatClicked(int row, int column);

	/// <summary>
	/// Slot that is called when the select button is clicked.
	/// </summary>
	void onSelectClicked();

	/// <summary>
	/// Opens the FFMPEG settings dialog (Windows only).
	/// </summary>
	void openFFMPEGSettings();
};
