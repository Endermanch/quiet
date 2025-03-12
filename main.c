#include <stdio.h>
#include <windows.h>

INT PrintMessage() {
	AttachConsole(ATTACH_PARENT_PROCESS);

	wprintf(L"Silently run applications and scripts.\n\n");
	wprintf(L"QUIET [/E] C:\\Windows\\Application.exe [ARGS]\n");
	wprintf(L"  /E - Run with elevated privileges.\n\n");
	wprintf(L"(c) Endermanch, 2025\n");

	return 1;
}

INT WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	WCHAR *pCmdLine,
	INT	nCmdShow
) {
	CONST WCHAR *command = L"open";

	if (wcslen(pCmdLine) == 0)
		return PrintMessage();

	// Skip spaces at the beginning.
	while (*pCmdLine == L' ')
		pCmdLine++;

	if (wcsnicmp(pCmdLine, L"/E", 2) == 0) {
		command = L"runas";

		pCmdLine += 2;
		while (*pCmdLine++ != L' ');
	}

	WCHAR *params = pCmdLine;
	USHORT len = 0;

	while (*params++ != L' ') len++;

	WCHAR *app = calloc(len + 1, sizeof(WCHAR));
	memcpy_s(app, len * sizeof(WCHAR), pCmdLine, len * sizeof(WCHAR));

	ShellExecuteW(
		NULL,
		command,
		app,
		params,
		NULL,
		SW_HIDE
	);

	free(app);

	return 0;
}