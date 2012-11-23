///////////////////////////////////////
//
//	プログラミング演習Ⅱ
//
//	Windowsプログラミング（オセロを作成）
//
//	参考サイト：
//		JavaScriptのオセロ(ここのコードを参考にしました)(ニコニコ動画に実況解説あり)
//		 http://void-main.org/niconicoprogram/?JavaScript%E3%81%AE%E3%82%AA%E3%82%BB%E3%83%AD
//		(ニコニコ動画：【プログラミング】オセロを1時間で作ってみた【実況解説】)
//		http://www.nicovideo.jp/watch/sm8391299
//
//	演習：
//		対戦相手をコンピュータにして動くように改造すること
//		BoardクラスのcomputerMove()の中を作成する
//
///////////////////////////////////////
// ex01.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "ex01.h"
#include "WinMaker.h"		// Window作成 クラス
#include "Board.h"			// Othello Game クラス

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	Board		othello;
	WinMaker	winmaker(&othello);

	winmaker.setWindow(WS_OVERLAPPEDWINDOW,33*10,33*10);
	if(!winmaker.init(hInstance,nCmdShow,L"Programming演習Ⅱ",L"Othello"))
		return	FALSE;

	return winmaker.messageLoop();
}
