#include "SpawnEggItem.hpp"
#include "world/level/Level.hpp"
#include "world/tile/Tile.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/MobFactory.hpp"
#include "world/entity/EntityEggInfo.hpp"
#include "world/entity/EntityTypeDescriptor.hpp"

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
	const EntityEggInfo* pEggInfo = EntityEggInfo::GetByEntityTypeID((EntityType::ID)item.getAuxValue());
	if (!pEggInfo)
		return Item::getDescriptionId();

	return Item::getDescriptionId() + "." + EntityTypeDescriptor::GetByEntityTypeID(pEggInfo->m_spawnedType)->getEntityType().getName();
}

Color SpawnEggItem::getColor(int data) const
{
	const EntityEggInfo* pEggInfo = EntityEggInfo::GetByEntityTypeID((EntityType::ID)data);
	if (!pEggInfo)
		return Color::WHITE;

	return pEggInfo->m_primaryColor;
}

bool SpawnEggItem::useOn(ItemStack& itemStack, Player& player, const TilePos& pos, Facing::Name face) const
{
	Level& level = player.getLevel();
	TileSource& source = player.getTileSource();

	TileID tile = source.getTile(pos);
	TilePos tp = pos.relative(face);

	float yOffset = 0.0f;
	if (face == Facing::UP && tile == Tile::fence->m_ID)
		yOffset = 0.5f;

	if (!SpawnCreature(level, (EntityType::ID)itemStack.getAuxValue(), Vec3(tp.x + 0.5f, tp.y + yOffset, tp.z + 0.5f)))
		return false;

	if (!player.isCreative())
		itemStack.shrink();

	return true;
}

bool SpawnEggItem::SpawnCreature(Level& level, EntityType::ID entityType, const Vec3& pos)
{
	if (!EntityEggInfo::GetByEntityTypeID(entityType))
		return false;

	if (level.m_bIsClientSide)
		return true;

	Mob* pMob = MobFactory::CreateMob(entityType, level);
	if (!pMob)
		return false;

	pMob->moveTo(pos, Rot2(level.m_random.nextFloat() * 360.0f, 0.0f));
	level.addEntity(pMob);
	pMob->playAmbientSound();
	return true;
}
