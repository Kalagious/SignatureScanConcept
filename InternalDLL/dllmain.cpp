// dllmain.cpp : Defines the entry point for the DLL application.

#include "general.h"

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CloseHandle(CreateThread(0, 0, injectMain, 0, 0, 0));
    }
    return TRUE;
}

