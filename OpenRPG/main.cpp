#include "stdafx.h"
#include <windows.h>

#include "Game/Game.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#ifdef _DEBUG
	// 디버그일 때 콘솔을 표시
	AllocConsole();

	// 출력 및 입력 스트림을 재설정
	freopen("CONIN$", "rb", stdin);
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	std::ios::sync_with_stdio();
#endif

	Game::getInstance()->run();

#ifdef _DEBUG
	// 콘솔 해제
	FreeConsole();
#endif

	return 0;
}