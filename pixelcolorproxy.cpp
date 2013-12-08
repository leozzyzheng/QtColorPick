#include "pixelcolorproxy.h"

PixelColorProxy::PixelColorProxy(QObject *parent)
	: QObject(parent)
{
	m_mouseX = 0;
	m_mouseY = 0;
}

PixelColorProxy::~PixelColorProxy()
{

}

void PixelColorProxy::onMouseMove()
{
	HDC hDesktopDC = ::GetDC(NULL);
	COLORREF c;
	BYTE r;
	BYTE g;
	BYTE b;
	while (true)
	{
		c = GetPixel(hDesktopDC , m_mouseX , m_mouseY);
		r = GetRValue(c);
		g = GetGValue(c);
		b = GetBValue(c);
		emit proxyFinish(r , g , b , m_mouseX , m_mouseY);
		QThread::msleep(30);
	}
	DeleteDC(hDesktopDC);
}

void PixelColorProxy::setMousePos( int x , int y )
{
	m_mouseX = x;
	m_mouseY = y;
}


