#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

#define KEY_ZERO 0x30

//throws std::runtime_error, with msg, when ptr is null
template <typename Type>
void checkAddressNotNull(Type* ptr, const std::string& msg);

//constants
const std::string gameWindowTitle = "Warblade 1.34";
const unsigned int lowerMoneyLimit = 4000;
const LPVOID addressMoneyVar = reinterpret_cast<LPVOID*>(0x00848794);

int main(int args, char** argv)
{
	try {
		HWND gameWindow = FindWindowA(nullptr, gameWindowTitle.c_str());
		checkAddressNotNull(gameWindow, "Cannot find window handler !");

		DWORD processId;
		GetWindowThreadProcessId(gameWindow, &processId);
		checkAddressNotNull(&processId, "Cannot find process id !");

		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
		checkAddressNotNull(hProcess, "Cannot open process !");

		while (true) {
			int currAccount;
			ReadProcessMemory(hProcess, addressMoneyVar, &currAccount, sizeof(currAccount), nullptr);
						
			if (currAccount < lowerMoneyLimit) {
				WriteProcessMemory(hProcess, addressMoneyVar, &lowerMoneyLimit, sizeof(lowerMoneyLimit), nullptr);
			}

			if (GetAsyncKeyState(KEY_ZERO)) {
				break;
			}
		}
	}
	catch (std::runtime_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
	}

	return 0;
}

template <typename Type>
void checkAddressNotNull(Type* ptr, const std::string& msg) {
	if (!ptr) {
		throw std::runtime_error(msg);
	}
}