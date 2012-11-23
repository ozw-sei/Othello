#include "StdAfx.h"
#include "WinMaker.h"

WndProcObserver	* WinMaker::wndProcObserver = NULL;

int	WinMaker::right = 0;
int	WinMaker::bottom = 0;

WinMaker::WinMaker(WndProcObserver	*pObserver)
{
	setObserver(pObserver);
}

WinMaker::~WinMaker(void)
{
}

bool	WinMaker::init(HINSTANCE hInst,int nCmdShow,LPTSTR className,LPTSTR winName)
{
	pClassName = className;
	pWinName = winName;
	MyRegisterClass(hInst);
	if (!InitInstance (hInst, nCmdShow)){
		return false;
	}
	return	true;
}

int	WinMaker::messageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}

void	WinMaker::setWindow(DWORD style,int right,int bottom)
{
	winStyle = style;
	this->right = right;
	this->bottom = bottom;
}

void	WinMaker::setObserver(WndProcObserver	*pObserver)
{
	wndProcObserver = pObserver;
}


ATOM WinMaker::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WinMaker::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= pClassName;
	wcex.hIconSm		= NULL;
	return RegisterClassEx(&wcex);
}
BOOL WinMaker::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	RECT r;
	r.left = r.top = 0;
	r.right = right;
	r.bottom = bottom;
	AdjustWindowRectEx(&r,winStyle, false, 0);
	hWnd = CreateWindow(pClassName,pWinName,winStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,r.right - r.left , r.bottom - r.top,NULL, NULL, hInstance, NULL);
   if (!hWnd)
      return FALSE;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

LRESULT CALLBACK WinMaker::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message){
	case WM_CREATE:		WinMaker::wndProcObserver->init(hWnd,WinMaker::right,WinMaker::bottom);
						break;
	case WM_LBUTTONUP:	WinMaker::wndProcObserver->mouselup(hWnd,wParam,lParam);
						break;
	case WM_TIMER:		WinMaker::wndProcObserver->timer(hWnd);
						break;
	case WM_PAINT:		WinMaker::wndProcObserver->paint(hWnd);
						break;
	case WM_DESTROY:	WinMaker::wndProcObserver->destroy(hWnd);
						PostQuitMessage(0);
						break;
	default:			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
