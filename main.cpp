#include <iostream>
#include <string>
#include <Windows.h>

const std::string gameWindowTitle = "Warblade 1.34";

int main(int args, char** argv)
{
	HWND gameWindow = FindWindowA(nullptr, gameWindowTitle.c_str());
	
	if (!gameWindow) {
		std::cerr << "Cannot find window handler!\n";
		return -1;
	}

	DWORD processId;
	GetWindowThreadProcessId(gameWindow, &processId);
	if (!processId) {
		std::cerr << "Cannot find process id!\n";
		return -1;
	}
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
	if (!hProcess) {
		std::cerr << "Cannot open process!\n";
		return -1;
	}

	int newVal = 1000;
	WriteProcessMemory(hProcess, (LPVOID)0x00848794, &newVal, sizeof(newVal), nullptr);

	return 0;
}