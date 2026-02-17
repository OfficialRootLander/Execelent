#include "pch.h"
#include "NetConnection.h"
#pragma comment(lib, "Ws2_32.lib")
#include "opts.h"
#include <string>

tInternetConnectW OriginalInternetConnectW = nullptr;

HINTERNET WINAPI NetConnection::HookedInternetConnectW(
    HINTERNET hInternet,
    LPCWSTR lpszServerName,
    INTERNET_PORT nServerPort,
    LPCWSTR lpszUserName,
    LPCWSTR lpszPassword,
    DWORD dwService,
    DWORD dwFlags,
    DWORD_PTR dwContext
)
{
    if (lpszServerName)
    {
        std::wcout << L"[WinInet] Connecting to: "
            << lpszServerName
            << L":" << nServerPort
            << std::endl;

        // Redirect ALL Epic OL domains
        if (wcsstr(lpszServerName, L".ol.epicgames.com") != nullptr)
        {
            std::wcout << L"[Redirected] -> " << ServerIpString << L":" << std::to_wstring(ServerPort) << std::endl;
            lpszServerName = ServerIpString;
            nServerPort = ServerPort;
        }
    }

    return OriginalInternetConnectW(
        hInternet,
        lpszServerName,
        nServerPort,
        lpszUserName,
        lpszPassword,
        dwService,
        dwFlags,
        dwContext
    );
}