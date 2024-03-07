#include <windows.h>
#include "GameProcess.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	GameProcess* gameProcess = new GameProcess();
	
	gameProcess->Initalize(hInstance);
	gameProcess->Update();
	gameProcess->Finalize();

	delete gameProcess;
}