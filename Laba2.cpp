#include <iostream>
#include <Windows.h>
#include <processthreadsapi.h>
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

void reverse_string() {
    while (true) {
        char str[100];
        scanf_s("%s", str, 100);
        std::cout << _strrev(str) << std::endl;
    }
}

void random() {
    while (true) {
        double randomNum = (double)rand() / RAND_MAX;
        std::cout << randomNum << std::endl;
        Sleep(1000);
    }
}

int main()
{
    SetConsoleCtrlHandler(ProcessEvents, TRUE);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)reverse_string, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)random, NULL, 0, NULL);
    while (true);
    return 0;
}