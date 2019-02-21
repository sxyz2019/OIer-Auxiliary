/*
#ifndef UNICODE
#	define UNICODE
#endif
#ifndef _UNICODE
#	define _UNICODE
#endif
*/
#include <Windows.h>
#include <tchar.h>
// 必须要进行前导声明
LRESULT CALLBACK WindowProc(
    _In_  HWND hwnd,
    _In_  UINT uMsg,
    _In_  WPARAM wParam,
    _In_  LPARAM lParam
);
// 程序入口点
int CALLBACK WinMain(
    _In_  HINSTANCE hInstance,
    _In_  HINSTANCE hPrevInstance,
    _In_  LPSTR lpCmdLine,
    _In_  int nCmdShow
  )
{
    // 类名
    TCHAR cls_Name[] = _T("My Class");
    // 设计窗口类
    WNDCLASS wc = { };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProc;
    wc.lpszClassName = cls_Name;
    wc.hInstance = hInstance;
    // 注册窗口类
    RegisterClass(&wc);
    // 创建窗口
    HWND hwnd = CreateWindow(
        cls_Name,           //类名，要和刚才注册的一致
        __T("我的应用程序"),    //窗口标题文字
        WS_OVERLAPPEDWINDOW, //窗口外观样式
        38,                 //窗口相对于父级的X坐标
        20,                 //窗口相对于父级的Y坐标
        480,                //窗口的宽度
        250,                //窗口的高度
        NULL,               //没有父窗口，为NULL
        NULL,               //没有菜单，为NULL
        hInstance,          //当前应用程序的实例句柄
        NULL);              //没有附加数据，为NULL
    if(hwnd == NULL) //检查窗口是否创建成功
        return 0;
    // 显示窗口
    ShowWindow(hwnd, SW_SHOW);
    // 更新窗口
    UpdateWindow(hwnd);
    // 消息循环
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
// 在WinMain后实现
LRESULT CALLBACK WindowProc(
    _In_  HWND hwnd,
    _In_  UINT uMsg,
    _In_  WPARAM wParam,
    _In_  LPARAM lParam
)
{
    switch(uMsg)
    {
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}