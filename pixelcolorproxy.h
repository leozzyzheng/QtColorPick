#ifndef PIXELCOLORPROXY_H
#define PIXELCOLORPROXY_H

#include <QObject>
#include <windows.h>
#include <QThread>

class PixelColorProxy : public QObject
{
	Q_OBJECT

public:
	PixelColorProxy(QObject *parent = 0);
	~PixelColorProxy();
	void setMousePos(int x , int y);
signals:
	void proxyFinish(BYTE r , BYTE g , BYTE b , int x , int y);

public slots:
	void onMouseMove();

private:
	int m_mouseX;
	int m_mouseY;
};

#endif // PIXELCOLORPROXY_H
