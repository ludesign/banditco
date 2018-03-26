#ifndef UNICODE
	#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h> // for EXIT_ codes

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	MessageBox(NULL, L"every beginning is hard", L"banditco", MB_OK);

	return EXIT_SUCCESS;
}