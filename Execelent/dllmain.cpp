// dllmain.cpp : Defines the entry point for the DLL application.
#pragma once
#include "pch.h"
#include <iostream>
#include "GameHooks.h"

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w+", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    freopen_s(&f, "CONOUT$", "w", stderr);
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitleA("Execelent Redirector (Made by RootLander) for OT6.5");

    GameHooks::InitAll();


    std::cout << "Hello From Execelent!\n";

    return  0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread = CreateThread(nullptr, 0, ThreadProc, hModule, 0, nullptr);
        if (!hThread) {
            MessageBoxA(NULL, "CreateThread failed!", "Error", MB_OK | MB_ICONERROR);
        }
        else {
            CloseHandle(hThread);
        }
    }
    return TRUE;
}


