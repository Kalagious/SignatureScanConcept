#pragma once

#include "windows.h"
#include "iostream"
#include <vector>
#include <TlHelp32.h>


DWORD WINAPI injectMain(LPVOID lpParameter);
uint64_t dwGetModuleSize(const wchar_t* lpszModuleName);
void* signatureScan(std::vector<uint8_t> sig, int32_t offset);