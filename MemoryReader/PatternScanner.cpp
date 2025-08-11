#include "Memory.hpp"

std::vector<int> Memory::PatternToBytes(const char* pattern) {
    auto bytes = std::vector<int>{};
    char* start = const_cast<char*>(pattern);
    char* end = start + strlen(pattern);

    for (char* curr = start; curr < end; ++curr) {
        if (*curr == '?') {
            ++curr;
            bytes.push_back(-1);
        } else {
            bytes.push_back(strtoul(curr, &curr, 16));
        }
    }
    return bytes;
}

uintptr_t Memory::PatternScan(uintptr_t base, const char* sig) {
    MODULEINFO mi;
    if (!GetModuleInformation(hProcess, (HMODULE)base, &mi, sizeof(mi)))
        return 0;

    auto patternBytes = PatternToBytes(sig);
    auto scanBytes = reinterpret_cast<uint8_t*>(base);
    size_t patternSize = patternBytes.size();

    for (size_t i = 0; i < mi.SizeOfImage - patternSize; ++i) {
        bool found = true;
        for (size_t j = 0; j < patternSize; ++j) {
            if (scanBytes[i + j] != patternBytes[j] && patternBytes[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) 
            return (uintptr_t)&scanBytes[i];
    }
    return 0;
}
