#pragma once

#include <array>
#include <unordered_map>

#include "Entity.hpp"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void InsertData(Entity entity, T component)
    {
        size_t newIndex = size;
        entityToIndexMap[entity] = newIndex;
        indexToEntityMap[newIndex] = entity;
        componentArray[newIndex] = component;
        ++size;
    }

    void RemoveData(Entity entity)
    {
        //Copy last element at position of removed element
        size_t indexOfRemovedEntity = entityToIndexMap[entity];
        size_t indexOfLastElement = size - 1;
        componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

        //Update maps to point to new position
        Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
        entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        entityToIndexMap.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);

        --size;
    }

    T& GetData(Entity entity)
    {
        return componentArray[entityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override
    {
        if(entityToIndexMap.find(entity) != entityToIndexMap.end())
        {
            RemoveData(entity);
        }
    }

private:
    std::array<T, MAX_ENTITIES> componentArray{};
    std::unordered_map<Entity, size_t> entityToIndexMap;
    std::unordered_map<size_t, Entity> indexToEntityMap;
    size_t size{};
};