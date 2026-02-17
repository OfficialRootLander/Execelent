#include "pch.h"
#include "GameHooks.h"
#include "NetConnection.h"
#include <Windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

void GameHooks::InitAll()
{
    GMLHOOK::Init();


    HMODULE hWinInet = GetModuleHandleA("wininet.dll");
    if (!hWinInet)
        hWinInet = LoadLibraryA("wininet.dll");

    if (hWinInet)
    {
        void* internetConnectW = GetProcAddress(hWinInet, "InternetConnectW");

        if (internetConnectW)
        {
            GMLHOOK::Hook(
                internetConnectW,
                NetConnection::HookedInternetConnectW,
                (void**)&OriginalInternetConnectW,
                "wininetW connect"
            );
        }
    }
}
