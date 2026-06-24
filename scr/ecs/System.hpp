#pragma once

#include <set>

#include "Entity.hpp"

class System
{
public:
	std::set<Entity> entities;
};