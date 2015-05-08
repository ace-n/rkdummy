// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[512];

	// Get a handle to the process.
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

	// Get the process name.
	if (NULL != hProcess) {
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	// Print the process name and identifier. (Change "1564" to whatever PID you want to detect.)
	if ((int)processID == 1564) {
		MessageBoxW(NULL, L"DETECTED!", szProcessName, 0);
	}

	// Release the handle to the process.
	CloseHandle(hProcess);
}

int _tmain(int argc, _TCHAR* argv[]) {
	while (1) {

		// Get PID list
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		unsigned int i;
		if (!K32EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) { return 1; }

		// Get # of PIDs
		cProcesses = cbNeeded / sizeof(DWORD);

		// Print name/PID for each process.
		for (i = 0; i < cProcesses; i++) {
			if (aProcesses[i] != 0) { PrintProcessNameAndID(aProcesses[i]); }
		}

		Sleep(1000);
	}
}

