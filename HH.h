#ifndef HH_H
#define HH_H
#include <QApplication>
#include <Windows.h>

#define WM_G_MOUSEMOVE WM_USER+1

HHOOK keyHook=NULL;
HHOOK mouseHook=NULL;

unsigned int gMouseX = 0;//全局鼠标X坐标
unsigned int gMouseY = 0;//全局鼠标Y坐标

MainWindow * gAppInstance = NULL;

//声明卸载函数,以便调用
void unHook();

////键盘钩子过程
//LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
//{
//
//
//    //在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
//    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
//    if(pkbhs->vkCode==VK_F12)
//    {
//        void unHook();
//        qApp->quit();
//    }
//    return 0;//返回1表示截取消息不再传递,返回0表示不作处理,消息继续传递
//
//}
//鼠标钩子过程
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
	if(nCode == HC_ACTION)
	{
		if(wParam == WM_MOUSEMOVE)
		{   
			gMouseX = ((PMSLLHOOKSTRUCT)lParam)->pt.x;
			gMouseY = ((PMSLLHOOKSTRUCT)lParam)->pt.y;
			gAppInstance->receiveMoseEvent(WM_G_MOUSEMOVE , gMouseX , gMouseY);
		}
	}
	return 0;

}
//卸载钩子
void unHook()
{
    //UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);
}
//安装钩子,调用该函数即安装钩子
void setHook(MainWindow * mainWindow)
{
    //这两个底层钩子,不要DLL就可以全局
    ////							底层键盘钩子
    //keyHook = SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
    //                          底层鼠标钩子
    mouseHook = SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
	gAppInstance = mainWindow;
}

#endif