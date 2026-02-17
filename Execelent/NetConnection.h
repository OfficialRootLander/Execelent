#ifndef NETCONNECTION_H
#define NETCONNECTION_H
#include <iostream>
#include <Windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

typedef HINTERNET(WINAPI* tInternetConnectW)(
    HINTERNET,
    LPCWSTR,
    INTERNET_PORT,
    LPCWSTR,
    LPCWSTR,
    DWORD,
    DWORD,
    DWORD_PTR
    );

extern tInternetConnectW OriginalInternetConnectW;

class NetConnection
{
public:
	//here add like process request hook and stuff

    static HINTERNET WINAPI HookedInternetConnectW(
        HINTERNET hInternet,
        LPCWSTR lpszServerName,
        INTERNET_PORT nServerPort,
        LPCWSTR lpszUserName,
        LPCWSTR lpszPassword,
        DWORD dwService,
        DWORD dwFlags,
        DWORD_PTR dwContext
    );
};

#endif