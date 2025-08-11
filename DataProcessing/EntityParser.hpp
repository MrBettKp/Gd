#pragma once
#include <string>
#include <vector>

struct Vector3 {
    float x, y, z;
};

struct GameEntity {
    uintptr_t address;
    Vector3 position;
    std::string name;
    int32_t health;
    int32_t typeId;
};

class EntityParser {
public:
    static GameEntity ParseFromMemory(const uint8_t* rawData, size_t size);
    static std::vector<GameEntity> ParseEntityList(const uint8_t* rawData, size_t size);
};
