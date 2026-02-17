#pragma once
#ifndef GMLHOOK_H
#define GMLHOOK_H
#pragma once
#include <Windows.h>
#include "MinHook.h"
#pragma comment(lib, "libMinHook.x86.lib")
#include <iostream>
#include <string>

class GMLHOOK
{
public:
    static void DisplayHookMessage(std::string DisplayMessage, int ReturnCode);
    static int Hook(void* Address, void* Detour, void** OG, std::string DisplayMessage = "");

    template<typename T>
    static int Hook(void* Address, void* Detour, T& OriginalFn, std::string DisplayMessage = "")
    {
        return Hook(Address, Detour, reinterpret_cast<void**>(&OriginalFn), DisplayMessage);
    }

    template<typename Addr, typename T>
    static int Hook(Addr Address, void* Detour, T& OriginalFn, std::string DisplayMessage = "")
    {
        return Hook(reinterpret_cast<void*>(Address),
            Detour,
            reinterpret_cast<void**>(&OriginalFn),
            DisplayMessage);
    }

    static inline int Init()
    {
        MH_STATUS status = MH_Initialize();
        if (status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED)
        {
            return 1;
        }
        return 0;
    }

};


#endif