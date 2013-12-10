#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <windows.h>
#include "pixelcolorproxy.h"

void unHook();

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void receiveMoseEvent(int Msg , int x , int y);

public slots:
	void onColorProxyFinished(BYTE r , BYTE g , BYTE b , int x , int y);

signals:
	void mouseMove();

private:
	void				__initConnection();
    Ui::MainWindow *	ui;
	PixelColorProxy *	m_pPixelColorProxy;
	QThread *			m_pProxyThread;
	HDC					m_hDesktopDC;
	int					m_screenWidth;
	int					m_screenHeight;
	QTimer *		    m_pTimer;
};

#endif // MAINWINDOW_H
