#include "windows.h"
#include <iostream>
#include <csignal>
#include <signal.h>

void main()
{
	PROCESS_INFORMATION procInfo;
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	ZeroMemory(&procInfo, sizeof(PROCESS_INFORMATION));
	if (!CreateProcess(L"D:\\OS_lab\\os_lab1_child_win\\x64\\Debug\\os_lab1_child_win.exe", NULL,
		NULL, NULL, FALSE, 0, NULL, NULL, &cif, &procInfo))
	{
		std::cout << "Procees can't be started. Error: " << GetLastError << std::endl;
		return;
	}

	std::cout << "Process is started" << std::endl;
	HANDLE hProc = procInfo.hProcess;
	if (hProc != NULL) {
		WaitForSingleObject(procInfo.hProcess, INFINITE);
		DWORD exitCode;
		GetExitCodeProcess(hProc, &exitCode);
		std::cout << "Process is ended with code: " << exitCode << std::endl;
	}

	CloseHandle(procInfo.hThread);
	return;
}
