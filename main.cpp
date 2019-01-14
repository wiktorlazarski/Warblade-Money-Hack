#include <iostream>
#include <string>
#include <Windows.h>

const std::string gameWindowTitle = "Warblade 1.34";

int main(int args, char** argv)
{
	HWND gameWindow = FindWindowA(NULL, gameWindowTitle.c_str());
	
	if (gameWindow == NULL) {
		std::cerr << "Window not found !\n";
	}



	return 0;
}