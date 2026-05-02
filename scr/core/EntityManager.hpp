#pragma once

#include <queue>
#include <vector>
#include <array>

#include "Entity.hpp"
#include "Signature.hpp"


class EntityManager
{
public:
    EntityManager()
    {
        // Initialize the queue with all possible entity IDs
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			availableEntities.push(entity);
		}
    }

    Entity CreateEntity()
    {
		Entity id = availableEntities.front();
		availableEntities.pop();
		++livingEntityCount;

		return id;
    }

    void DestroyEntity(Entity entity)
    {
		// Put the destroyed ID at the back of the queue
		availableEntities.push(entity);
		--livingEntityCount;
    }


	void SetSignature(Entity entity, Signature signature)
	{
		signatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		return signatures[entity];
	}


private:
	// Queue of unused entity IDs
	std::queue<Entity> availableEntities{};

	std::array<Signature, MAX_ENTITIES> signatures{};

	// Total living entities - used to keep limits on how many exist
	uint32_t livingEntityCount = 0;
};