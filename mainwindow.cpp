#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint & Qt::MSWindowsFixedSizeDialogHint);
	setFixedSize(this->width(), this->height());
	m_pPixelColorProxy = new PixelColorProxy();
	m_pProxyThread = new QThread();

	__initConnection();

	m_pPixelColorProxy->moveToThread(m_pProxyThread);

	m_pProxyThread->start();
	emit mouseMove();

	m_hDesktopDC = GetDC(NULL);
	m_screenWidth = GetDeviceCaps(m_hDesktopDC, HORZRES);
	m_screenHeight = GetDeviceCaps(m_hDesktopDC, VERTRES);
}

void MainWindow::__initConnection()
{
	connect( this				, SIGNAL(mouseMove()),						m_pPixelColorProxy ,	SLOT(onMouseMove()));
	connect( m_pPixelColorProxy , SIGNAL(proxyFinish(BYTE,BYTE,BYTE,int,int)),this ,				SLOT(onColorProxyFinished(BYTE,BYTE,BYTE,int,int)),Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
	DeleteDC(m_hDesktopDC);
	unHook();
}

void MainWindow::receiveMoseEvent( int Msg , int x , int y )
{
	if(x<0) x=0;
	else if(x>m_screenWidth-1)  x = m_screenWidth-1;
	if(y<0) y=0;
	else if(y>m_screenHeight-1) y = m_screenHeight-1;

	m_pPixelColorProxy->setMousePos(x , y);
}

void MainWindow::onColorProxyFinished( BYTE r , BYTE g , BYTE b , int x , int y)
{
	QString R = QString::number(r);
	QString G = QString::number(g);
	QString B = QString::number(b);
	QString X = QString::number(x);
	QString Y = QString::number(y);
	QString text = "RGB("+R+","+G+","+B+")\nPosition("+X+","+Y+")";
	ui->m_oLabel2->setText(text);
}


