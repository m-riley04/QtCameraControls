# QtCameraControls
A widget/dialog for controlling Qt camera settings and state. It includes all available slots for QCamera for Qt 6.8.0.

<img src="https://raw.githubusercontent.com/m-riley04/QtCameraControls/refs/heads/main/media/main_and_dialog.png"/>

# Table of Contents
- [Supported Platforms](#supported-platforms)
- [Features](#features)
    - [Test Program Features](#test-program-features)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
    - [Main Window](#main-window)
    - [QtCameraControlDialog](#qtcameracontroldialog)
        - [Formats](#formats)
        - [Zoom and Focus](#zoom-and-focus)
        - [Settings and Properties](#settings-and-properties)

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
- [x] Full checks for camera feature availablility
- [ ] "Full" error handling
- [x] Docstrings for all functions

> NOTE: While the code _should_ be fully functional, some camera features may not be recognized as "supported" due to current QCamera limitations.

## Test Program Features
- [x] Basic camera preview:
	- [x] QVideoWidget preview
	- [x] Camera device selection
	- [x] Add auto-refresh for camera devices

# Build Instructions
1. Clone the repository
2. Install the necessary [dependencies](#Dependencies)
3. Open the solution (preferrably in Visual Studio)
4. Build the solution

# Usage
## Main Window
This is a window primarily for showing the utilization of the QtCameraControlsDialog widget. It has the following features:
- QVideoWidget for viewing the current camera preview
- Dropdown for selecting the camera device
    - Automatically updates, but can be manually refreshed through the menu bar
- Menubar for certain functions and "About" links

<img src="https://raw.githubusercontent.com/m-riley04/QtCameraControls/refs/heads/main/media/main_window.png"/>

## QtCameraControlDialog
This is the dialog window/widget that is used to control the camera options/settings. At the top, you are able to see the camera device name and toggle it on or off. 

### Formats
This tab is for changing the format of the camera:
- FPS
- Resolution
- Pixel Format
<img src="https://raw.githubusercontent.com/m-riley04/QtCameraControls/refs/heads/main/media/dialog_format.png"/>

### Zoom and Focus
This tab is for chaning the zoom and focus properties of the camera:
- Zoom Rate
- Zoom Factor
- Focus Mode
- Focus Distance
<img src="https://github.com/m-riley04/QtCameraControls/blob/main/media/dialog_zoomfocus.png"/>

### Settings and Properties
This tab is for changing the majority of the camera's visual properties:
- Color Temperature
- Exposure Mode
- Exposure Composition
- Flash Mode
- Auto Exposure Time
- Auto ISO Sensitivity
- Manual ISO Sensitivity
- Torch Mode
- White Balance Mode
- FFMPEG-based DirectShow UVC control window (Windows only)
<img src="https://github.com/m-riley04/QtCameraControls/blob/main/media/dialog_settings.png"/>

# Dependencies
- Qt 6.8.0
    - QtCore
    - QtGUI
    - QtMultimedia
    - QtMultimediaWidgets

> NOTE: If you are using Visual Studio, you should use the official [Qt Visual Studio Tools extension](https://doc.qt.io/qtvstools/index.html) to manage your Qt installation.
