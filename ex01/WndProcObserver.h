#pragma once

class WndProcObserver
{
public:
	WndProcObserver(void){}
	virtual ~WndProcObserver(void){}

	virtual	void	init(HWND hWnd,int width,int height)
	{
		this->width = width;
		this->height = height;
		HDC hdc = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
		hMemPrev = (HBITMAP)SelectObject(hMemDC, hBitmap);
		ReleaseDC(hWnd, hdc);
	}
	virtual	void	timer(HWND hWnd){}
	virtual	void	paint(HWND hWnd)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	virtual	void	destroy(HWND hWnd)
	{
		HBITMAP hBitmap = (HBITMAP)SelectObject(hMemDC, hMemPrev);
		DeleteObject(hBitmap);
		DeleteObject(hMemDC);
	}
	virtual	void	mouselup(HWND hWnd,WPARAM wParam, LPARAM lParam){}

protected:
	HDC hMemDC;
	HBITMAP hMemPrev;
	int width;
	int height;
};
