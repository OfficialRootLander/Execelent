#include "pch.h"
#include "GMLHOOK.h"
#include <sstream>
#include <iomanip>

int HookedFunctionNumber = 0;

void GMLHOOK::DisplayHookMessage(std::string DisplayMessage, int ReturnCode)
{
	if (DisplayMessage != "")
	{
		std::string SuccesCode = ReturnCode == 0 ? "Succesfully hooked function " + DisplayMessage + " [" + std::to_string(HookedFunctionNumber) + "]" : "Failed to hook function " + DisplayMessage + " [" + std::to_string(HookedFunctionNumber) + "]";
		std::cout << SuccesCode << "\n";
	}
	else
	{
		std::string SuccesCode = ReturnCode == 0 ? "Succesfully Hooked Function! [" + std::to_string(HookedFunctionNumber) + "]" : "Failed to hook function! [" + std::to_string(HookedFunctionNumber) + "]";
		std::cout << SuccesCode << "\n";
	}
}

int GMLHOOK::Hook(void* Address, void* Detour, void** OG, std::string DisplayMessage)
{
	int ReturnCode = 0;
	HookedFunctionNumber++;

	if (MH_CreateHook(Address, Detour, OG) != MH_OK) {
		ReturnCode = 1;
	}

	// Enable hook
	if (MH_EnableHook(Address) != MH_OK) {
		ReturnCode = 1;
	}


	if (ReturnCode == 0)
	{
		std::stringstream ss;
		ss << " at (0x"
			<< std::hex << std::uppercase
			<< (uintptr_t)Address
			<< ")";

		DisplayMessage += ss.str();
	}

	DisplayHookMessage(DisplayMessage, ReturnCode);
	return ReturnCode;
}