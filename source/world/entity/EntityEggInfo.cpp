#include "EntityEggInfo.hpp"

std::map<EntityType::ID, EntityEggInfo> EntityEggInfo::entityEggs = std::map<EntityType::ID, EntityEggInfo>();

EntityEggInfo::EntityEggInfo(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor)
	: m_spawnedType(spawnedType)
	, m_primaryColor(primaryColor)
	, m_secondaryColor(secondaryColor)
{
}

void EntityEggInfo::_addEgg(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor)
{
	entityEggs.insert(std::make_pair(spawnedType, EntityEggInfo(spawnedType, primaryColor, secondaryColor)));
}

void EntityEggInfo::initEggs()
{
	_addEgg(EntityType::CREEPER,    0xFF0BA70D, 0xFF000000);
	_addEgg(EntityType::SKELETON,   0xFFC1C1C1, 0xFF494949);
	_addEgg(EntityType::SPIDER,     0xFF262D34, 0xFF0E0EA8);
	_addEgg(EntityType::ZOMBIE,     0xFFAFAF00, 0xFF659C79);
	_addEgg(EntityType::SLIME,      0xFF3EA051, 0xFF6EBF7E);
	_addEgg(EntityType::GHAST,      0xFFF9F9F9, 0xFFBCBCBC);
	_addEgg(EntityType::PIG_ZOMBIE, 0xFF9393EA, 0xFF29714C);
	_addEgg(EntityType::PIG,        0xFFA2A5F0, 0xFF5F63DB);
	_addEgg(EntityType::SHEEP,      0xFFE7E7E7, 0xFFB5B5FF);
	_addEgg(EntityType::COW,        0xFF263644, 0xFFA1A1A1);
	_addEgg(EntityType::CHICKEN,    0xFFA1A1A1, 0xFF0000FF);
	_addEgg(EntityType::SQUID,      0xFF4D3B22, 0xFF998870);
}

const EntityEggInfo* EntityEggInfo::GetByEntityTypeID(EntityType::ID id)
{
	std::map<EntityType::ID, EntityEggInfo>::const_iterator it = entityEggs.find(id);
	if (it != entityEggs.end())
		return &it->second;

	return nullptr;
}
