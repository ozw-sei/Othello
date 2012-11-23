#include "StdAfx.h"
#include "Board.h"

Board::Board(void):
 computer(0)
,turn(2)
{
}

Board::~Board(void)
{
}

void	Board::init(HWND hWnd,int width,int height)
{
	WndProcObserver::init(hWnd,width,height);

	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			board[i][j] = 0;
		}
	}
	board[4][5] = 1;
	board[5][4] = 1;
	board[4][4] = 2;
	board[5][5] = 2;
	turnChange();
	computer = 2;
	show();
	InvalidateRect(hWnd, NULL, false);
}

void	Board::mouselup(HWND hWnd,WPARAM wp, LPARAM lp)
{
	int		xposi = LOWORD(lp);
	int		yposi = HIWORD(lp);
	for(int x = 1; x <= 8; x++) {
		for(int y = 1; y <= 8; y++) {
			if(		x*33 < xposi && xposi < (x+1)*33
				&&	y*33 < yposi && yposi < (y+1)*33){
				if(board[x][y] == 0 && checkPiece(x, y, true)){
					turnChange();
					show();
					InvalidateRect(hWnd, NULL, false);
				}
				return;
			}
		}
	}
}

void Board::paint(HWND hWnd)
{
	show();
	WndProcObserver::paint(hWnd);
}

void Board::show()
{
    HPEN hPen, hOldPen;
    HBRUSH hBrush, hOldBrush;

	for(int x = 1; x <= 8; x++) {
		for(int y = 1; y <= 8; y++) {
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			hOldPen = (HPEN)SelectObject(hMemDC, hPen);
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			hOldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
			Rectangle(hMemDC,x*33,y*33,(x+1)*33,(y+1)*33);
			SelectObject(hMemDC, hOldPen);
			SelectObject(hMemDC, hOldBrush);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			COLORREF crColor = -1;
			if(board[x][y] == 2){		// black
				crColor = RGB(255, 255, 255);
			}
			else if(board[x][y] == 1){	// white
				crColor = RGB(0, 0, 0);
			}
			if(crColor != -1){
				hBrush = CreateSolidBrush(crColor);
				hOldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
				Ellipse(hMemDC,x*33+1,y*33+1,(x+1)*33-1,(y+1)*33-1);
				SelectObject(hMemDC, hOldBrush);
				DeleteObject(hBrush);
			}
		}
	}
}

int Board::checkPiece(int x, int y, bool flip)
{
	int ret = 0;

	for(int dx = -1; dx <= 1; dx++) {
		for(int dy = -1; dy <= 1; dy++) {
			if(dx == 0 && dy == 0){
				continue;
			}
			int nx = x + dx;
			int	ny = y + dy, n = 0;
			while(board[nx][ny] == 3 - turn){
				n++; nx += dx;
				ny += dy;
			}
			if(n > 0 && board[nx][ny] == turn){
				ret += n;
				if(flip) {
					nx = x + dx;
					ny = y + dy;
					while(board[nx][ny] == 3 - turn) {
						board[nx][ny] = turn;
						nx += dx; ny += dy;
					}
					board[x][y] = turn;
				}
			}
		}
	}
	return ret;
}

void Board::showMessage(std::wstring & message)
{
	SetBkColor(hMemDC,RGB(0, 0, 0));
	SetTextColor(hMemDC, RGB(255, 255, 255));
	TextOut(hMemDC, 5, 5, L"                                        ", 40);
	TextOut(hMemDC, 5, 5, message.c_str(), message.length());
}

void Board::turnChange()
{
	int b = 0;
	int	w = 0;

	turn = 3 - turn;		// 1 -> 2 -> 1
	std::wstring message = ((turn == 1)?L"black":L"white");

	for(int x = 1; x <= 8; x++) {
		for(int y = 1; y <= 8; y++) {
			if(board[x][y] == 0 && checkPiece(x, y, false)){
				showMessage(message + L"'s move");
				computerMove();
				return;
			}
		}
	}
	turn = 3 - turn;
	message += L" pass / ";
	message += (turn == 1)?L"black":L"white";
	message += L"'s move";
	for(int x = 1; x <= 8; x++) {
		for(int y = 1; y <= 8; y++) {
			if(board[x][y] == 0 && checkPiece(x, y, false)) {
				showMessage(message);
				computerMove();
				return;
			} else {
				if(board[x][y] == 1) { b++; }
				if(board[x][y] == 2) { w++; }
			}
		}
	}
	TCHAR	buf[256];
	wsprintf(buf,L"black:%d white:%d",b,w);
	message = buf;
	if(b == w) {
		message += L" -> draw";
	} else {
		message += ((b > w)? L" -> black": L" -> white");
		message += L" won";
	}
	showMessage(message);
}

void Board::computerMove()
{
	// computerの番の時
	if(turn == computer) {
		// ここにコンピュータの処理を記述する
		// 置ける場所を探して、コマを置く
		// mouselup()を参照（クリックしてコマを置いているところ）
		for(int x = 1; x <= 8; x++) {
			for(int y = 1; y <= 8; y++) {
				if(board[x][y] == 0){
					if(checkPiece(x, y, true)){
						turnChange();
						return;
					}
				}
			}
		}
	}
}
