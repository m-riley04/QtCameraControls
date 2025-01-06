#include "qtcameracontrolswindow.h"

QtCameraControlsWindow::QtCameraControlsWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	// Initialize camera and capture session
	pCamera = new QCamera();
	pCamera->setCameraDevice(QMediaDevices::defaultVideoInput());
	pCamera->setActive(true);

	// Initialize capture session
	pCaptureSession = new QMediaCaptureSession();
	pCaptureSession->setCamera(pCamera);
	pCaptureSession->setVideoOutput(ui.videoPreview);

	// Initialize media devices
	pMediaDevices = new QMediaDevices();

	// Init dropdown
	refreshCameraDevices();

	// Init other components
	initializeWidgets();
	initializeMenuBar();
}

QtCameraControlsWindow::~QtCameraControlsWindow()
{
	delete pCamera;
	delete pCaptureSession;
	delete pMediaDevices;
}

void QtCameraControlsWindow::refreshCameraDevices() {
	// Clear dropdown list
	ui.dropdownVideoDevices->clear();

	// Block signals to prevent changing camera device
	ui.dropdownVideoDevices->blockSignals(true);

	// Populate dropdown with available cameras
	QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
	for (QCameraDevice& c : cameras) {
		ui.dropdownVideoDevices->addItem(c.description());
	}

	// Unblock signals
	ui.dropdownVideoDevices->blockSignals(false);
}

QCameraDevice QtCameraControlsWindow::findDeviceFromIndex(int index) {
	QCameraDevice selectedDevice;
	QList<QCameraDevice> cameras = QMediaDevices::videoInputs();

	for (int i = 0; i < cameras.length(); i++) {
		if (i == index) selectedDevice = cameras[i];
	}

	return selectedDevice;
}

void QtCameraControlsWindow::initializeMenuBar()
{
	// Device
	connect(ui.actionRefreshDeviceList, &QAction::triggered, this, &QtCameraControlsWindow::refreshCameraDevices);

	// About
	connect(ui.actionGitHub, &QAction::triggered, this, []() {
		QDesktopServices::openUrl(QUrl("https://github.com/m-riley04/QtCameraControls"));
		});

	connect(ui.actionCredits, &QAction::triggered, this, []() {
		QDesktopServices::openUrl(QUrl("https://rileymeyerkorth.com"));
		});
}

void QtCameraControlsWindow::initializeWidgets()
{
	// Connect button to open camera controls dialog
	connect(ui.buttonSettings, &QPushButton::clicked, this, [this]() {
		QtCameraControlsDialog* dialog = new QtCameraControlsDialog(pCamera, pCaptureSession, this);
		dialog->exec();
		});

	// Connect dropdown to change camera device
	connect(ui.dropdownVideoDevices, &QComboBox::currentIndexChanged, this, [this](int i) {
		auto device = findDeviceFromIndex(i);
		pCamera->setCameraDevice(device);
		});

	// Auto refresh camera devices
	connect(pMediaDevices, &QMediaDevices::videoInputsChanged, this, &QtCameraControlsWindow::refreshCameraDevices);

	connect(pCamera, &QCamera::errorOccurred, this, [this](QCamera::Error error) {
		QMessageBox::warning(this, "Error", "Camera error occurred: " + pCamera->errorString());
		
		});

}
