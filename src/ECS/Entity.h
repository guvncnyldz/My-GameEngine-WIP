#ifndef ENTITY_H
#define ENTITY_H

#include "pch.h"

struct Entity
{
    const uint32_t Id;

    [[nodiscard]] constexpr uint32_t index() const noexcept { return extractIndex(Id); }
    [[nodiscard]] constexpr uint32_t generation() const noexcept { return extractGeneration(Id); }

    void log() const noexcept
    {
        LOG_INFO(std::format("Id: {} Index: {} Generation: {}", Id, index(), generation()));
    }
private:
    [[nodiscard]] static constexpr uint32_t extractIndex(uint32_t id) noexcept { return id & INDEX_MASK; }
    [[nodiscard]] static constexpr uint32_t extractGeneration(uint32_t id) noexcept { return (id >> INDEX_BITS) & GENERATION_MASK; }

    [[nodiscard]] static constexpr uint32_t packedIndex(uint32_t index) noexcept { return index & INDEX_MASK; }
    [[nodiscard]] static constexpr uint32_t packedGeneration(uint32_t generation) noexcept { return (generation & GENERATION_MASK) << INDEX_BITS; }
    [[nodiscard]] static constexpr uint32_t packedId(uint32_t index, uint32_t generation) noexcept { return packedIndex(index) | packedGeneration(generation); }

    [[nodiscard]] static constexpr Entity create(uint32_t index, uint32_t generation) noexcept
    {
        return { packedId(index, generation) };
    }

    static constexpr uint32_t INDEX_BITS = 20;
    static constexpr uint32_t GENERATION_BITS = 12;

    static constexpr uint32_t INDEX_MASK = (1u << INDEX_BITS) - 1u;
    static constexpr uint32_t GENERATION_MASK = (1u << GENERATION_BITS) - 1u;
    
    template <std::size_t N>
    friend class EntityPool;
};

#endif
