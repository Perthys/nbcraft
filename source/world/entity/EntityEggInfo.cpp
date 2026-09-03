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
	_addEgg(EntityType::CREEPER,    Color::FromRGB(0x0D, 0xA7, 0x0B), Color::FromRGB(0x00, 0x00, 0x00));
	_addEgg(EntityType::SKELETON,   Color::FromRGB(0xC1, 0xC1, 0xC1), Color::FromRGB(0x49, 0x49, 0x49));
	_addEgg(EntityType::SPIDER,     Color::FromRGB(0x34, 0x2D, 0x26), Color::FromRGB(0xA8, 0x0E, 0x0E));
	_addEgg(EntityType::ZOMBIE,     Color::FromRGB(0x00, 0xAF, 0xAF), Color::FromRGB(0x79, 0x9C, 0x65));
	_addEgg(EntityType::SLIME,      Color::FromRGB(0x51, 0xA0, 0x3E), Color::FromRGB(0x7E, 0xBF, 0x6E));
	_addEgg(EntityType::GHAST,      Color::FromRGB(0xF9, 0xF9, 0xF9), Color::FromRGB(0xBC, 0xBC, 0xBC));
	_addEgg(EntityType::PIG_ZOMBIE, Color::FromRGB(0xEA, 0x93, 0x93), Color::FromRGB(0x4C, 0x71, 0x29));
	_addEgg(EntityType::PIG,        Color::FromRGB(0xF0, 0xA5, 0xA2), Color::FromRGB(0xDB, 0x63, 0x5F));
	_addEgg(EntityType::SHEEP,      Color::FromRGB(0xE7, 0xE7, 0xE7), Color::FromRGB(0xFF, 0xB5, 0xB5));
	_addEgg(EntityType::COW,        Color::FromRGB(0x44, 0x36, 0x26), Color::FromRGB(0xA1, 0xA1, 0xA1));
	_addEgg(EntityType::CHICKEN,    Color::FromRGB(0xA1, 0xA1, 0xA1), Color::FromRGB(0xFF, 0x00, 0x00));
	_addEgg(EntityType::SQUID,      Color::FromRGB(0x22, 0x3B, 0x4D), Color::FromRGB(0x70, 0x88, 0x99));
}

const EntityEggInfo* EntityEggInfo::GetByEntityTypeID(EntityType::ID id)
{
	std::map<EntityType::ID, EntityEggInfo>::const_iterator it = entityEggs.find(id);
	if (it != entityEggs.end())
		return &it->second;

	return nullptr;
}
