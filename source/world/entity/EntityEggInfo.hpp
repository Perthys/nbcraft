#pragma once

#include <map>

#include "common/math/Color.hpp"
#include "EntityType.hpp"

class EntityEggInfo
{
public:
	EntityEggInfo(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor);

public:
	EntityType::ID m_spawnedType;
	Color m_primaryColor;
	Color m_secondaryColor;

public:
	static void initEggs();

	static const EntityEggInfo* GetByEntityTypeID(EntityType::ID);
	static const std::map<EntityType::ID, EntityEggInfo>& GetEntityEggs() { return entityEggs; }

private:
	static void _addEgg(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor);

private:
	static std::map<EntityType::ID, EntityEggInfo> entityEggs;
};
