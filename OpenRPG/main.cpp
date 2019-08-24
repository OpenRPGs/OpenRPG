#include "stdafx.h"
#include <windows.h>

#include "Game/Game.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#ifdef _DEBUG
	// 디버그일 때 콘솔을 표시
	AllocConsole();

	{
		FILE* stream;

		// 출력 및 입력 스트림을 재설정
		freopen_s(&stream, "CONIN$", "rb", stdin);
		freopen_s(&stream, "CONOUT$", "wb", stdout);
		freopen_s(&stream, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}
#endif

	Game::getInstance()
		->boot()
		->run()
		->Dispose();

#ifdef _DEBUG
	// 콘솔 해제
	FreeConsole();
#endif

	return 0;
}