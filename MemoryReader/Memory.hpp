#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>

class Memory {
public:
    bool Attach(const char* procName);
    uintptr_t GetModuleBase(const char* modName);
    template<typename T> T Read(uintptr_t addr);
    std::string ReadString(uintptr_t addr, size_t maxLen = 256);
    uintptr_t PatternScan(uintptr_t base, const char* sig);
    void Close();

private:
    HANDLE hProcess = nullptr;
    DWORD pid = 0;

    std::vector<int> PatternToBytes(const char* pattern);
};
