#include "QtCameraControlsDialog.h"

/**
* A map of pixel formats to their string representations.
*/
QMap<QVideoFrameFormat::PixelFormat, QString> pixelFormatMap{
	{ QVideoFrameFormat::Format_Invalid, "Invalid" },
	{ QVideoFrameFormat::Format_ARGB8888, "ARGB8888" },
	{ QVideoFrameFormat::Format_ARGB8888_Premultiplied, "ARGB8888_Premultiplied" },
	{ QVideoFrameFormat::Format_XRGB8888, "RGB8888" },
	{ QVideoFrameFormat::Format_BGRA8888, "BGRA8888" },
	{ QVideoFrameFormat::Format_BGRA8888_Premultiplied, "BGRA8888_Premultiplied" },
	{ QVideoFrameFormat::Format_ABGR8888, "ABGR8888" },
	{ QVideoFrameFormat::Format_ABGR8888, "ABGR8888_Premultiplied" },
	{ QVideoFrameFormat::Format_XBGR8888, "XBGR8888" },
	{ QVideoFrameFormat::Format_RGBA8888, "RGBA8888" },
	{ QVideoFrameFormat::Format_BGRX8888, "BGRX8888" },
	{ QVideoFrameFormat::Format_RGBX8888, "RGBX8888" },
	{ QVideoFrameFormat::Format_AYUV, "AYUV" },
	{ QVideoFrameFormat::Format_AYUV_Premultiplied, "AYUV_Premultiplied" },
	{ QVideoFrameFormat::Format_YUV420P, "YUV420P" },
	{ QVideoFrameFormat::Format_YUV422P, "YUV422P" },
	{ QVideoFrameFormat::Format_YV12, "YV12" },
	{ QVideoFrameFormat::Format_UYVY, "UYVY" },
	{ QVideoFrameFormat::Format_YUYV, "YUYV" },
	{ QVideoFrameFormat::Format_NV12, "NV12" },
	{ QVideoFrameFormat::Format_NV21, "NV21" },
	{ QVideoFrameFormat::Format_IMC1, "IMC1" },
	{ QVideoFrameFormat::Format_IMC2, "IMC2" },
	{ QVideoFrameFormat::Format_IMC3, "IMC3" },
	{ QVideoFrameFormat::Format_IMC4, "IMC4" },
	{ QVideoFrameFormat::Format_P010, "P010" },
	{ QVideoFrameFormat::Format_P016, "P016" },
	{ QVideoFrameFormat::Format_Y8, "Y8" },
	{ QVideoFrameFormat::Format_Y16, "Y16" },
	{ QVideoFrameFormat::Format_Jpeg, "Jpeg" },
	{ QVideoFrameFormat::Format_SamplerExternalOES, "SamplerExternalOES" },
	{ QVideoFrameFormat::Format_SamplerRect, "SamplerRect" },
	{ QVideoFrameFormat::Format_YUV420P10, "YUV420P10" },
};

QtCameraControlsDialog::QtCameraControlsDialog(QCamera* camera, QMediaCaptureSession* cap, QWidget* parent)
	: QDialog(parent), pCamera(camera)
{
	ui.setupUi(this);

	/// Initialzie camera device
	mName = camera->cameraDevice().description();
	ui.labelCameraDevice->setText(camera->cameraDevice().description());
	ui.checkboxActive->setChecked(camera->isActive());
	connect(ui.checkboxActive, &QCheckBox::checkStateChanged, camera, [camera](Qt::CheckState state) {
		camera->setActive(state == Qt::CheckState::Checked);
		});

	/// Initialize Formats box
	initializeFormatGroup();

	/// Initialize settings group
	initializeSettingsGroup();
}

QtCameraControlsDialog::~QtCameraControlsDialog()
{}

QString QtCameraControlsDialog::sizeToString(QSize size)
{
	return QString::number(size.width()) + "x" + QString::number(size.height());
}

QSize QtCameraControlsDialog::stringToSize(const QString& str)
{
	QStringList parts = str.split('x');
	if (parts.size() == 2)
		return QSize(parts[0].toInt(), parts[1].toInt());
	return QSize(); // invalid if parsing failed
}

void QtCameraControlsDialog::populateFilterDropdowns()
{
	// Clear existing items
	ui.dropdownFps->clear();
	ui.dropdownResolution->clear();
	ui.dropdownPixelFormat->clear();

	// Populate dropdowns with default/no option as FIRST INDEX (index 0)
	ui.dropdownFps->addItem("Any", QVariant());
	ui.dropdownResolution->addItem("Any", QVariant());
	ui.dropdownPixelFormat->addItem("Any", QVariant());

	// Populate dropdowns with all possible for each category
	QSet<float> fpsSet;
	QSet<QSize> resolutionSet;
	QSet<QVideoFrameFormat::PixelFormat> pixelFormatSet;
	for (QCameraFormat format : mFormats)
	{
		fpsSet.insert(format.maxFrameRate());
		resolutionSet.insert(format.resolution());
		pixelFormatSet.insert(format.pixelFormat());
	}

	// Sort each set
	QList<float> fpsList = fpsSet.values();
	std::sort(fpsList.begin(), fpsList.end(), std::greater<float>());
	QList<QSize> resolutionList = resolutionSet.values();
	std::sort(resolutionList.begin(), resolutionList.end(), [](const QSize& a, const QSize& b) {
		return a.width() > b.width();
		});
	QList<QVideoFrameFormat::PixelFormat> pixelFormatList = pixelFormatSet.values();
	std::sort(pixelFormatList.begin(), pixelFormatList.end(), [](const QVideoFrameFormat::PixelFormat& a, const QVideoFrameFormat::PixelFormat& b) {
		return pixelFormatMap[a] > pixelFormatMap[b];
		});

	// Populate fps dropdown
	for (float fps : fpsList)
	{
		ui.dropdownFps->addItem(QString::number(fps), fps);
	}

	// Populate resolution dropdown
	for (QSize resolution : resolutionList)
	{
		ui.dropdownResolution->addItem(sizeToString(resolution), resolution);
	}

	// Populate pixel format dropdown
	for (QVideoFrameFormat::PixelFormat pixelFormat : pixelFormatList)
	{
		ui.dropdownPixelFormat->addItem(pixelFormatMap[pixelFormat], pixelFormat);
	}
}

void QtCameraControlsDialog::initializeExposureModes()
{

}

void QtCameraControlsDialog::initializeFormatGroup()
{
	// Initialize format list
	mFormats = pCamera->cameraDevice().videoFormats();

	// Check if no formats are available
	if (mFormats.isEmpty())
	{
		/// TODO: Maybe put a message instead?
		ui.groupFormat->hide();
		return;
	}

	// Populate format table
	for (QCameraFormat format : mFormats)
	{
		ui.tableFormats->insertRow(ui.tableFormats->rowCount());
		int row = ui.tableFormats->rowCount() - 1;
		ui.tableFormats->setItem(row, 0, new QtCameraFormatTableWidgetItem(QString::number(format.maxFrameRate()), QtCameraFormatTableItemType::FPS)); // FPS
		ui.tableFormats->setItem(row, 1, new QtCameraFormatTableWidgetItem(sizeToString(format.resolution()), QtCameraFormatTableItemType::RESOLUTION)); // Resolution
		ui.tableFormats->setItem(row, 2, new QtCameraFormatTableWidgetItem(pixelFormatMap[format.pixelFormat()], QtCameraFormatTableItemType::PIXEL_FORMAT)); // Pixel Format
	}

	// Get default format
	defaultFormat = mFormats.first();

	// Update ui elements
	ui.labelFps->setText(QString::number(defaultFormat.maxFrameRate()));
	ui.labelResolution->setText(sizeToString(defaultFormat.resolution()));
	ui.labelPixelFormat->setText(pixelFormatMap[defaultFormat.pixelFormat()]);

	// Populate filter dropdowns
	resetFilters();

	// Connect control signals
	connectFormatControls();
}

void QtCameraControlsDialog::initializeZoomFocusGroup()
{
	/// Initialize Zoom/Focus Box values
	ui.sliderZoom->setValue(pCamera->zoomFactor());
	ui.sliderFocusDistance->setValue(pCamera->focusDistance());

	// Connect widgets to controls
	connect(ui.sliderZoom, &QSlider::valueChanged, pCamera, [this](int value) {
		pCamera->setZoomFactor(value);
		});

	connect(ui.sliderFocusDistance, &QSlider::valueChanged, pCamera, [this](int value) {
		pCamera->setFocusDistance(value);
		});
}

void QtCameraControlsDialog::initializeSettingsGroup()
{
	/// Initialize Settings Box values
	// Controls
	ui.sliderColorTemp->setValue(pCamera->colorTemperature());
	ui.dropdownExposureMode->setCurrentIndex(static_cast<int>(pCamera->exposureMode()));
	ui.sliderExposureComp->setValue(pCamera->exposureCompensation());
	ui.dropdownFlashMode->setCurrentIndex(static_cast<int>(pCamera->flashMode()));
	ui.checkboxAutoExposureTime->setChecked(pCamera->exposureTime());
	ui.sliderManualExposureTime->setValue(pCamera->manualExposureTime());
	ui.checkboxAutoIsoSensitivity->setChecked(pCamera->isoSensitivity());
	ui.sliderManualIsoSensitivity->setValue(pCamera->manualIsoSensitivity());
	ui.dropdownTorchMode->setCurrentIndex(static_cast<int>(pCamera->torchMode()));
	ui.dropdownWhiteBalanceMode->setCurrentIndex(static_cast<int>(pCamera->whiteBalanceMode()));

	/// Initialize min/max values
	//ui.sliderColorTemp->setMinimum();
	//ui.sliderColorTemp->setMaximum();
	//ui.sliderExposureComp->setMinimum();
	//ui.sliderExposureComp->setMaximum();
	ui.sliderManualExposureTime->setMinimum(pCamera->minimumExposureTime());
	ui.sliderManualExposureTime->setMaximum(pCamera->maximumExposureTime());
	ui.sliderManualIsoSensitivity->setMinimum(pCamera->minimumIsoSensitivity());
	ui.sliderManualIsoSensitivity->setMaximum(pCamera->maximumIsoSensitivity());

	// Check if modes are supported
	

	// Connect widgets to controls
	connectSettingsControls();

	// Connect ffmpeg settings button
	connect(ui.buttonFFMPEG, &QPushButton::clicked, this, &QtCameraControlsDialog::openFFPMEGSettings);
}

void QtCameraControlsDialog::connectSettingsControls()
{
	connect(ui.sliderColorTemp, &QSlider::valueChanged, pCamera, [this](int value) {
		pCamera->setColorTemperature(value);
		});
	connect(ui.dropdownExposureMode, &QComboBox::currentIndexChanged, pCamera, [this](int index) {
		pCamera->setExposureMode(static_cast<QCamera::ExposureMode>(index));
		});
	connect(ui.sliderExposureComp, &QSlider::valueChanged, pCamera, [this](int value) {
		pCamera->setExposureCompensation(value);
		});
	connect(ui.dropdownFlashMode, &QComboBox::currentIndexChanged, pCamera, [this](int index) {
		pCamera->setFlashMode(static_cast<QCamera::FlashMode>(index));
		});
	connect(ui.checkboxAutoExposureTime, &QCheckBox::checkStateChanged, pCamera, [this](Qt::CheckState state) {
		pCamera->setAutoExposureTime(); // TODO: add functionality
		});
	connect(ui.sliderManualExposureTime, &QSlider::valueChanged, pCamera, [this](int value) {
		pCamera->setManualExposureTime(value);
		});
	connect(ui.checkboxAutoIsoSensitivity, &QCheckBox::checkStateChanged, pCamera, [this](Qt::CheckState state) {
		pCamera->setAutoIsoSensitivity(); // TODO: add functionality
		});
	connect(ui.sliderManualIsoSensitivity, &QSlider::valueChanged, pCamera, [this](int value) {
		pCamera->setManualIsoSensitivity(value);
		});
	connect(ui.dropdownTorchMode, &QComboBox::currentIndexChanged, pCamera, [this](int index) {
		pCamera->setTorchMode(static_cast<QCamera::TorchMode>(index));
		});
	connect(ui.dropdownWhiteBalanceMode, &QComboBox::currentIndexChanged, pCamera, [this](int index) {
		pCamera->setWhiteBalanceMode(static_cast<QCamera::WhiteBalanceMode>(index));
		});
}

void QtCameraControlsDialog::connectFormatControls()
{
	// Initialize filters
	connect(ui.dropdownFps, &QComboBox::currentIndexChanged, this, &QtCameraControlsDialog::updateFormatTable);
	connect(ui.dropdownResolution, &QComboBox::currentIndexChanged, this, &QtCameraControlsDialog::updateFormatTable);
	connect(ui.dropdownPixelFormat, &QComboBox::currentIndexChanged, this, &QtCameraControlsDialog::updateFormatTable);

	// Initialize reset button
	connect(ui.buttonResetFilters, &QPushButton::clicked, this, &QtCameraControlsDialog::resetFilters);

	// Initialize select button
	connect(ui.buttonSelect, &QPushButton::clicked, this, &QtCameraControlsDialog::onSelectClicked);

	// Initialize format table
	connect(ui.tableFormats, &QTableWidget::cellClicked, this, &QtCameraControlsDialog::onFormatClicked);
}

void QtCameraControlsDialog::resetFilters()
{
	// Block signals to prevent infinite loops
	ui.dropdownFps->blockSignals(true);
	ui.dropdownResolution->blockSignals(true);
	ui.dropdownPixelFormat->blockSignals(true);

	// Populate dropdowns
	populateFilterDropdowns();

	// Update the format table
	updateFormatTable();

	// Unblock signals
	ui.dropdownFps->blockSignals(false);
	ui.dropdownResolution->blockSignals(false);
	ui.dropdownPixelFormat->blockSignals(false);
}

void QtCameraControlsDialog::onFormatClicked(int row, int column)
{
	// Find format that matches row
	auto itr = std::find_if(mFormats.begin(), mFormats.end(), [this, row](const QCameraFormat& format) {
		return qFuzzyCompare(format.maxFrameRate(), ui.tableFormats->item(row, QtCameraFormatTableItemType::FPS)->text().toFloat()) &&
			format.resolution() == stringToSize(ui.tableFormats->item(row, QtCameraFormatTableItemType::RESOLUTION)->text()) &&
			pixelFormatMap[format.pixelFormat()] == ui.tableFormats->item(row, QtCameraFormatTableItemType::PIXEL_FORMAT)->text();
		});
	if (itr == mFormats.end()) {
		// TODO: do more error handling
		QMessageBox::warning(this, "Error", "Format not found.");
		return;
	}

	// Set the camera format
	selectedFormat = *itr;

	// Enable the select button
	ui.buttonSelect->setEnabled(true);
}

void QtCameraControlsDialog::onSelectClicked()
{
	if (selectedFormat.isNull()) {
		// TODO: Add error checking
		QMessageBox::warning(this, "Error", "No format selected.");
		return;
	}

	// Set the camera format
	pCamera->setCameraFormat(selectedFormat);

	// Get the current format of the camera (should be the selected one)
	QCameraFormat currentFormat = pCamera->cameraFormat();

	// Update the UI elements
	ui.labelFps->setText(QString::number(currentFormat.maxFrameRate()));
	ui.labelResolution->setText(sizeToString(currentFormat.resolution()));
	ui.labelPixelFormat->setText(pixelFormatMap[currentFormat.pixelFormat()]);

	// Reset selected filter
	selectedFormat = QCameraFormat();
	ui.buttonSelect->setEnabled(false);
}

void QtCameraControlsDialog::updateFormatTable()
{
	// Clear existing entries
	ui.tableFormats->clearContents();
	ui.tableFormats->setRowCount(0);

	// Extract current filter selections
	QVariant fpsData = ui.dropdownFps->currentData();
	QVariant resData = ui.dropdownResolution->currentData();
	QVariant pfData = ui.dropdownPixelFormat->currentData();

	// Convert them to actual types if they are valid
	bool fpsIsValid = fpsData.isValid();
	bool resIsValid = resData.isValid();
	bool pfIsValid = pfData.isValid();

	// We'll only compare if these are valid
	float selectedFps = fpsIsValid ? fpsData.toFloat() : 0.0f;
	QSize selectedResolution = resIsValid ? resData.toSize() : QSize();
	QVideoFrameFormat::PixelFormat selectedPixelFormat =
		pfIsValid
		? static_cast<QVideoFrameFormat::PixelFormat>(pfData.toInt())
		: QVideoFrameFormat::Format_Invalid;

	// Iterate through all available formats
	for (const QCameraFormat& format : mFormats)
	{
		// Check FPS if valid
		bool matchesFps = true;
		if (fpsIsValid) {
			// Use qFuzzyCompare to account for floating-point comparison
			matchesFps = qFuzzyCompare(format.maxFrameRate(), selectedFps);
		}

		// Check resolution if valid
		bool matchesResolution = true;
		if (resIsValid) {
			matchesResolution = (format.resolution() == selectedResolution);
		}

		// Check pixel format if valid
		bool matchesPixelFormat = true;
		if (pfIsValid) {
			matchesPixelFormat = (format.pixelFormat() == selectedPixelFormat);
		}

		// If all conditions pass, add it to the table
		if (matchesFps && matchesResolution && matchesPixelFormat) {
			int row = ui.tableFormats->rowCount();
			ui.tableFormats->insertRow(row);

			// FPS
			ui.tableFormats->setItem(
				row,
				0,
				new QtCameraFormatTableWidgetItem(QString::number(format.maxFrameRate()), QtCameraFormatTableItemType::FPS));

			// Resolution
			ui.tableFormats->setItem(
				row,
				1,
				new QtCameraFormatTableWidgetItem(sizeToString(format.resolution()), QtCameraFormatTableItemType::RESOLUTION));

			// Pixel Format
			ui.tableFormats->setItem(
				row,
				2,
				new QtCameraFormatTableWidgetItem(pixelFormatMap[format.pixelFormat()], QtCameraFormatTableItemType::PIXEL_FORMAT));
		}
	}
}

void QtCameraControlsDialog::openFFPMEGSettings()
{
	QProcess* process = new QProcess();

	// Hanlde errors
	connect(process, &QProcess::errorOccurred, [this](QProcess::ProcessError error) {
		switch (error) {
		case QProcess::ProcessError::FailedToStart:
			QMessageBox::warning(this, "Error", "Failed to start ffmpeg process.");
			break;
		case QProcess::ProcessError::Crashed:
			QMessageBox::warning(this, "Error", "FFMPEG process crashed.");
			break;
		case QProcess::ProcessError::Timedout:
			QMessageBox::warning(this, "Error", "FFMPEG process timed out.");
			break;
		case QProcess::ProcessError::WriteError:
			QMessageBox::warning(this, "Error", "FFMPEG process write error.");
			break;
		case QProcess::ProcessError::ReadError:
			QMessageBox::warning(this, "Error", "FFMPEG process read error.");
			break;
		case QProcess::ProcessError::UnknownError:
			QMessageBox::warning(this, "Error", "FFMPEG process unknown error.");
			break;
		default:
			QMessageBox::warning(this, "Error", "FFMPEG process error.");
			break;
		}
		});

	process->start("ffmpeg -f dshow -show_video_device_dialog true -i video=\"" + this->mName + '"');
}