#ifndef HH_H
#define HH_H
#include <QApplication>
#include <Windows.h>

#define WM_G_MOUSEMOVE WM_USER+1

HHOOK keyHook=NULL;
HHOOK mouseHook=NULL;

unsigned int gMouseX = 0;//ȫ�����X����
unsigned int gMouseY = 0;//ȫ�����Y����

MainWindow * gAppInstance = NULL;

//����ж�غ���,�Ա����
void unHook();

////���̹��ӹ���
//LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
//{
//
//
//    //��WH_KEYBOARD_LLģʽ��lParam ��ָ��KBDLLHOOKSTRUCT���͵�ַ
//    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
//    if(pkbhs->vkCode==VK_F12)
//    {
//        void unHook();
//        qApp->quit();
//    }
//    return 0;//����1��ʾ��ȡ��Ϣ���ٴ���,����0��ʾ��������,��Ϣ��������
//
//}
//��깳�ӹ���
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
//ж�ع���
void unHook()
{
    //UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);
}
//��װ����,���øú�������װ����
void setHook(MainWindow * mainWindow)
{
    //�������ײ㹳��,��ҪDLL�Ϳ���ȫ��
    ////							�ײ���̹���
    //keyHook = SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
    //                          �ײ���깳��
    mouseHook = SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
	gAppInstance = mainWindow;
}

#endif