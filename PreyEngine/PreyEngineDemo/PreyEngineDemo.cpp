#include <windows.h>
#include "GameProcess.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 메모리 누수 체크
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	GameProcess* gameProcess = new GameProcess();
	
	gameProcess->Initalize(hInstance);
	gameProcess->Update();
	gameProcess->Finalize();

	delete gameProcess;

	//_CrtDumpMemoryLeaks();
}