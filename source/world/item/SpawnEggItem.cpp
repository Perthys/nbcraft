#include "SpawnEggItem.hpp"
#include "common/Util.hpp"
#include "client/locale/Language.hpp"
#include "world/level/Level.hpp"
#include "world/tile/Tile.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/MobFactory.hpp"
#include "world/entity/EntityTypeDescriptor.hpp"

std::map<EntityType::ID, SpawnEggItem::Type> SpawnEggItem::Type::entityEggs = std::map<EntityType::ID, SpawnEggItem::Type>();

SpawnEggItem::Type::Type(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor)
	: m_spawnedType(spawnedType)
	, m_primaryColor(primaryColor)
	, m_secondaryColor(secondaryColor)
{
}

void SpawnEggItem::Type::_addEgg(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor)
{
	entityEggs.insert(std::make_pair(spawnedType, Type(spawnedType, primaryColor, secondaryColor)));
}

void SpawnEggItem::Type::initEggs()
{
	_addEgg(EntityType::CREEPER,    Color::FromRGB(13, 167, 11),   Color::FromRGB(0, 0, 0));
	_addEgg(EntityType::SKELETON,   Color::FromRGB(193, 193, 193), Color::FromRGB(73, 73, 73));
	_addEgg(EntityType::SPIDER,     Color::FromRGB(52, 45, 38),    Color::FromRGB(168, 14, 14));
	_addEgg(EntityType::ZOMBIE,     Color::FromRGB(0, 175, 175),   Color::FromRGB(121, 156, 101));
	_addEgg(EntityType::SLIME,      Color::FromRGB(81, 160, 62),   Color::FromRGB(126, 191, 110));
	_addEgg(EntityType::GHAST,      Color::FromRGB(249, 249, 249), Color::FromRGB(188, 188, 188));
	_addEgg(EntityType::PIG_ZOMBIE, Color::FromRGB(234, 147, 147), Color::FromRGB(76, 113, 41));
	_addEgg(EntityType::PIG,        Color::FromRGB(240, 165, 162), Color::FromRGB(219, 99, 95));
	_addEgg(EntityType::SHEEP,      Color::FromRGB(231, 231, 231), Color::FromRGB(255, 181, 181));
	_addEgg(EntityType::COW,        Color::FromRGB(68, 54, 38),    Color::FromRGB(161, 161, 161));
	_addEgg(EntityType::CHICKEN,    Color::FromRGB(161, 161, 161), Color::FromRGB(255, 0, 0));
	_addEgg(EntityType::SQUID,      Color::FromRGB(34, 59, 77),    Color::FromRGB(112, 136, 153));
}

const SpawnEggItem::Type* SpawnEggItem::Type::GetByEntityTypeID(EntityType::ID id)
{
	std::map<EntityType::ID, Type>::const_iterator it = entityEggs.find(id);
	if (it != entityEggs.end())
		return &it->second;

	return nullptr;
}

SpawnEggItem::SpawnEggItem(int itemID) : Item(itemID)
{
	m_bStackedByData = true;
	m_maxDamage = 0;
}

int SpawnEggItem::getIcon(const ItemStack* pItem) const
{
	return Item::egg->getIcon(pItem);
}

std::string SpawnEggItem::getDescriptionId(ItemStack& item) const
{
	std::string descriptionId = Item::getDescriptionId();

	EntityType::ID entityTypeId = (EntityType::ID)item.getAuxValue();
	const EntityTypeDescriptor* pTypeDesc = EntityTypeDescriptor::GetByEntityTypeID(entityTypeId);
	if (pTypeDesc)
	{
		const EntityType& entityType = pTypeDesc->getEntityType();
		descriptionId += "." + entityType.getName();
	}

	return descriptionId;
}

std::string SpawnEggItem::getHovertextName(ItemStack& item) const
{
	std::string entityName = "entity.unknown.name";
	EntityType::ID entityTypeId = (EntityType::ID)item.getAuxValue();
	const EntityTypeDescriptor* pTypeDesc = EntityTypeDescriptor::GetByEntityTypeID(entityTypeId);
	if (pTypeDesc)
		entityName = "entity." + pTypeDesc->getEntityType().getName() + ".name";

	return Util::format(Language::get(Item::getName()).c_str(), Language::get(entityName).c_str());
}

Color SpawnEggItem::getColor(int auxValue) const
{
	const Type* pType = Type::GetByEntityTypeID((EntityType::ID)auxValue);
	if (!pType)
		return Color::WHITE;

	return pType->m_primaryColor;
}

bool SpawnEggItem::useOn(ItemStack& itemStack, Player& player, const TilePos& pos, Facing::Name face) const
{
	Level& level = player.getLevel();
	TileSource& source = player.getTileSource();

	TilePos tp = pos.relative(face);
	Vec3 spawnPos(tp.x + 0.5f, float(tp.y), tp.z + 0.5f);

	Tile* pTile = Tile::tiles[source.getTile(pos)];
	if (face == Facing::UP && pTile)
	{
		const AABB* pAABB = pTile->getAABB(source, pos);
		if (pAABB)
			spawnPos.y = pAABB->max.y;
	}

	if (!SpawnCreature(level, (EntityType::ID)itemStack.getAuxValue(), spawnPos))
		return false;

	if (!player.isCreative())
		itemStack.shrink();

	return true;
}

bool SpawnEggItem::SpawnCreature(Level& level, EntityType::ID entityType, const Vec3& pos)
{
	if (level.m_bIsClientSide)
		return true;

	Mob* pMob = MobFactory::CreateMob(entityType, level);
	if (!pMob)
		return false;

	pMob->moveTo(pos, Rot2(level.m_random.nextFloat() * 360.0f, 0.0f));
	level.addEntity(pMob);

	return true;
}
