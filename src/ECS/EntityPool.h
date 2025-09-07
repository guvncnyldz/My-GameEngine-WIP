#ifndef ENTITYPOOL_H
#define ENTITYPOOL_H

#include "Entity.h"

template <std::size_t InitialSize>
class EntityPool {
public:
    EntityPool() : entities(InitialSize, 0), available(0), next(0) {}

    Entity get()
    {
        uint32_t index = 0;
        if (available > 0)
        {
            index = next;
            next = Entity::extractIndex(entities[next]);
            available--;
        }
        else
        {
            index = next++;
            if (next >= entities.size())
            {
                auto newSize = next * 2;
                entities.resize(newSize, 0);
                LOG_WARNING(std::format("Entity size is resized: {}", newSize));
            }
        }
        return Entity::create(index, Entity::extractGeneration(entities[index]));
    }

    void destroy(Entity entity)
    {
        auto index = entity.index();
        auto generation = Entity::extractGeneration(entities[index]);
        entities[index] = Entity::packedId(next, ++generation);
        next = index;
        available++;
    }

private:
    std::vector<uint32_t> entities;
    uint32_t available;
    uint32_t next;
};


#endif
