#pragma once
#include	<windows.h>
#include	"WndProcObserver.h"

class WinMaker
{
private:
	WinMaker();
public:
	WinMaker(WndProcObserver * wndProcObserver);
	virtual ~WinMaker(void);

	void	setWindow(DWORD style,int right,int bottom);
	bool	init(HINSTANCE hInst,int nCmdShow,LPTSTR className,LPTSTR winName);
	int		messageLoop();

private:
	LPTSTR pClassName;
	LPTSTR pWinName;
	DWORD	winStyle;
	static	int		right;
	static	int		bottom;

	ATOM	MyRegisterClass(HINSTANCE hInstance);
	BOOL	InitInstance(HINSTANCE, int);
	void	setObserver(WndProcObserver	*wndProcObserver);

	static	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	static	WndProcObserver	*wndProcObserver;
};
