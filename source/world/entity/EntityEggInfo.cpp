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
	_addEgg(EntityType::CREEPER,    Color::FromRGB(13, 167, 11), Color::FromRGB(0, 0, 0));
	_addEgg(EntityType::SKELETON,   Color::FromRGB(193, 193, 193), Color::FromRGB(73, 73, 73));
	_addEgg(EntityType::SPIDER,     Color::FromRGB(52, 45, 38), Color::FromRGB(168, 14, 14));
	_addEgg(EntityType::ZOMBIE,     Color::FromRGB(0, 175, 175), Color::FromRGB(121, 156, 101));
	_addEgg(EntityType::SLIME,      Color::FromRGB(81, 160, 62), Color::FromRGB(126, 191, 110));
	_addEgg(EntityType::GHAST,      Color::FromRGB(249, 249, 249), Color::FromRGB(188, 188, 188));
	_addEgg(EntityType::PIG_ZOMBIE, Color::FromRGB(234, 147, 147), Color::FromRGB(76, 113, 41));
	_addEgg(EntityType::PIG,        Color::FromRGB(240, 165, 162), Color::FromRGB(219, 99, 95));
	_addEgg(EntityType::SHEEP,      Color::FromRGB(231, 231, 231), Color::FromRGB(255, 181, 181));
	_addEgg(EntityType::COW,        Color::FromRGB(68, 54, 38), Color::FromRGB(161, 161, 161));
	_addEgg(EntityType::CHICKEN,    Color::FromRGB(161, 161, 161), Color::FromRGB(255, 0, 0));
	_addEgg(EntityType::SQUID,      Color::FromRGB(34, 59, 77), Color::FromRGB(112, 136, 153));
}

const EntityEggInfo* EntityEggInfo::GetByEntityTypeID(EntityType::ID id)
{
	std::map<EntityType::ID, EntityEggInfo>::const_iterator it = entityEggs.find(id);
	if (it != entityEggs.end())
		return &it->second;

	return nullptr;
}
