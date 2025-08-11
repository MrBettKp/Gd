#include "EntityParser.hpp"
#include <algorithm>

GameEntity EntityParser::ParseFromMemory(const uint8_t* rawData, size_t size) {
    GameEntity entity;
    // Basic parsing logic (example)
    entity.position.x = *reinterpret_cast<const float*>(rawData);
    entity.position.y = *reinterpret_cast<const float*>(rawData + 4);
    entity.position.z = *reinterpret_cast<const float*>(rawData + 8);
    return entity;
}

std::vector<GameEntity> EntityParser::ParseEntityList(const uint8_t* rawData, size_t size) {
    std::vector<GameEntity> entities;
    const size_t entitySize = 32; // Example struct size
    size_t count = size / entitySize;

    for (size_t i = 0; i < count; ++i) {
        entities.push_back(ParseFromMemory(rawData + (i * entitySize), entitySize));
    }

    return entities;
}
