#pragma once

namespace Config {
    // Example memory offsets (for educational purposes only)
    namespace Offsets {
        constexpr uintptr_t EXAMPLE_PLAYER_STRUCT = 0x1A3F4C0;
        constexpr uintptr_t EXAMPLE_ENTITY_LIST = 0x2B7E890;
        
        // Position offsets within player struct
        namespace Player {
            constexpr uintptr_t POSITION = 0x20;
            constexpr uintptr_t HEALTH = 0x1A4;
            constexpr uintptr_t NAME = 0x228;
        }
    }

    // Signature patterns (AOB)
    namespace Signatures {
        constexpr char EXAMPLE_PATTERN[] = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 0F";
    }
}
