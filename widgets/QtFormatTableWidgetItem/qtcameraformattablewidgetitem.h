#pragma once

#include <QTableWidgetItem>

enum QtCameraFormatTableItemType
{
	FPS,
	RESOLUTION,
	PIXEL_FORMAT
};

class QtCameraFormatTableWidgetItem : public QTableWidgetItem
{

public:
	QtCameraFormatTableWidgetItem(QString text, int type);
	~QtCameraFormatTableWidgetItem();

	bool operator< (const QTableWidgetItem& other) const;
};
