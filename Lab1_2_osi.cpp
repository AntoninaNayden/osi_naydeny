#include <iostream>
#include <Windows.h>
#include <csignal>
#include <stdio.h>


BOOL WINAPI ProcessEvents(DWORD ctrlType) {
	switch (ctrlType)
	{
	case CTRL_BREAK_EVENT:std::cout << "Ctrl break event" << std::endl; break;

	case CTRL_C_EVENT:std::cout << "Ctrl c event" << std::endl; break;

	case CTRL_CLOSE_EVENT:std::cout << "Ctrl close event" << std::endl; break;

	default:break;
	}
	return false;
}

int main() {
	if (SetConsoleCtrlHandler(ProcessEvents, TRUE)) {

		std::cout << "I am waiting for signal";
		while (TRUE) {}
		return 0;
	}
	else {
		std::cout << "Error! Handling is not ok";
		return 1;
	}
}
