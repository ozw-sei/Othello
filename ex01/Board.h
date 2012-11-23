#pragma once
#include <windows.h>
#include "wndprocobserver.h"
#include <string>

class Board : public WndProcObserver
{
public:
	Board(void);
	virtual ~Board(void);

	void	init(HWND hWnd,int width,int height);
	void	paint(HWND hWnd);
	void	mouselup(HWND hWnd,WPARAM wParam, LPARAM lParam);

private:
	void	show();
	void	showMessage(std::wstring & message);
	int		checkPiece(int x, int y, bool flip);
	void	turnChange();
	void	computerMove();

	int		computer;	// 1:black 2:white other:êlëŒêl
	int		turn;
	int		board[10][10];
};
