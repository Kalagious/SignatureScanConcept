#include "general.h"




DWORD WINAPI injectMain(LPVOID lpParameter)
{
	std::vector<uint8_t> aHelloWorldSignature = { 0x8B, 0x85, 0x00, 0x01, 0x00, 0x00, 0x83, 0xC0, 0x05, 0x89, 0x45, 0x04, 0x8B, 0x45, 0x04, 0x83, 0xC0, 0x07, 0x89, 0x45, 0x04, 0x8B, 0x45, 0x04, 0x83, 0xE8, 0x02, 0x89, 0x45, 0x04};
	
    typedef uint32_t(*helloWorld)(uint32_t test);

    helloWorld pHelloWorld = (helloWorld)signatureScan(aHelloWorldSignature, 0x1E);
    
    printf("InternalDll found HelloWorld at %p\n", pHelloWorld);

    pHelloWorld(20);
	return 0;
}


void* signatureScan(std::vector<uint8_t> sig, int32_t offset)
{
    void* pBase = GetModuleHandle(L"TestingBase.exe");
    uint64_t iModuleSize = dwGetModuleSize(TEXT("TestingBase.exe"));

    uint32_t iSuccessiveMatches = 0;
    for (uint64_t baseOffset = 0; baseOffset < iModuleSize; baseOffset++)
    {

        if (*(uint8_t*)((uint64_t)pBase + baseOffset) == sig.at(iSuccessiveMatches))
            iSuccessiveMatches++;
        else
            iSuccessiveMatches = 0;

        if (iSuccessiveMatches == sig.size())
            return (void*)((uint64_t)pBase + baseOffset - sig.size() - offset + 1);
    }

    return (void*)-1;
}

uint64_t dwGetModuleSize(const wchar_t* lpszModuleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
    DWORD dwModuleSize = 0;
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 ModuleEntry32 = { 0 };
        ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &ModuleEntry32))
        {
            do
            {
                if (wcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
                {
                    dwModuleSize = ModuleEntry32.modBaseSize;
                    break;
                }
            } while (Module32Next(hSnapshot, &ModuleEntry32));
        }
        CloseHandle(hSnapshot);
    }
    return (uint64_t)dwModuleSize;
}