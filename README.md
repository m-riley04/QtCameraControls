# QtCameraControls
A widget/dialog for controlling Qt camera settings and state. It includes all available slots for QCamera for Qt 6.8.0.

# Supported Platforms
- Windows
- Linux (***untested***, but theoretically *should* work)
- MacOS (***untested***, but theoretically *should* work)

# Features
- [x] Full control over almost every QCamera imaging property, including:
	- [x] Camera start/stop
	- [x] Auto Exposure Time
	- [x] Auto ISO Sensitivity
	- [x] Color Temperature
	- [x] Exposure Compensation
	- [x] Flash Mode
	- [x] Manual Exposure Time
	- [x] Manual ISO Sensitivity
	- [x] Torch Mode
	- [x] White Balance Mode
- [x] Ability to pick and choose the camera format:
    - [x] Frame Rate
	- [x] Resolution
	- [x] Pixel Format
- [x] Control over the zoom and focus of the camera, specifically:
    - [x] Zoom Factor
	- [x] Focus Mode
	- [x] Focus Distance
- [x] FFMPEG support for UVC camera control
- [ ] Full checks for camera feature availablility
- [ ] Full error handling

## Test Program Features
- [ ] Basic camera preview:
	- [ ] QVideoWidget preview
	- [ ] Camera device selection

# Build Instructions
1. Clone the repository
2. Install the necessary [dependencies](#Dependencies)
3. Open the solution (preferrably in Visual Studio)
4. Build the solution

# Dependencies
- Qt 6.8.0
    - QtMultimedia
    - QtMultimediaWidgets

> NOTE: If you are using Visual Studio, you should use the official [Qt Visual Studio Tools extension](https://doc.qt.io/qtvstools/index.html) to manage your Qt installation.