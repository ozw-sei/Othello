///////////////////////////////////////
//
//	�v���O���~���O���K�U
//
//	Windows�v���O���~���O�i�I�Z�����쐬�j
//
//	�Q�l�T�C�g�F
//		JavaScript�̃I�Z��(�����̃R�[�h���Q�l�ɂ��܂���)(�j�R�j�R����Ɏ����������)
//		 http://void-main.org/niconicoprogram/?JavaScript%E3%81%AE%E3%82%AA%E3%82%BB%E3%83%AD
//		(�j�R�j�R����F�y�v���O���~���O�z�I�Z����1���Ԃō���Ă݂��y��������z)
//		http://www.nicovideo.jp/watch/sm8391299
//
//	���K�F
//		�ΐ푊����R���s���[�^�ɂ��ē����悤�ɉ������邱��
//		Board�N���X��computerMove()�̒����쐬����
//
///////////////////////////////////////
// ex01.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "ex01.h"
#include "WinMaker.h"		// Window�쐬 �N���X
#include "Board.h"			// Othello Game �N���X

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
	if(!winmaker.init(hInstance,nCmdShow,L"Programming���K�U",L"Othello"))
		return	FALSE;

	return winmaker.messageLoop();
}
