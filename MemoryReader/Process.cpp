#include "Memory.hpp"
#include <Psapi.h>

bool Memory::Attach(const char* procName) {
    PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) 
        return false;

    if (Process32First(snapshot, &pe)) {
        do {
            if (!_stricmp(pe.szExeFile, procName)) {
                pid = pe.th32ProcessID;
                hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
                CloseHandle(snapshot);
                return hProcess != nullptr;
            }
        } while (Process32Next(snapshot, &pe));
    }

    CloseHandle(snapshot);
    return false;
}

uintptr_t Memory::GetModuleBase(const char* modName) {
    MODULEENTRY32 me = { sizeof(MODULEENTRY32) };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

    if (snapshot == INVALID_HANDLE_VALUE) 
        return 0;

    if (Module32First(snapshot, &me)) {
        do {
            if (!_stricmp(me.szModule, modName)) {
                CloseHandle(snapshot);
                return (uintptr_t)me.modBaseAddr;
            }
        } while (Module32Next(snapshot, &me));
    }

    CloseHandle(snapshot);
    return 0;
}

template<typename T>
T Memory::Read(uintptr_t addr) {
    T buffer;
    ReadProcessMemory(hProcess, (LPCVOID)addr, &buffer, sizeof(T), nullptr);
    return buffer;
}

std::string Memory::ReadString(uintptr_t addr, size_t maxLen) {
    std::string buffer(maxLen, '\0');
    ReadProcessMemory(hProcess, (LPCVOID)addr, &buffer[0], maxLen, nullptr);
    return buffer.c_str();
}

void Memory::Close() {
    if (hProcess) {
        CloseHandle(hProcess);
        hProcess = nullptr;
    }
}
