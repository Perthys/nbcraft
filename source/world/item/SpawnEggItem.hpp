#pragma once

#include "Item.hpp"
#include "world/entity/EntityType.hpp"

class SpawnEggItem : public Item
{
public:
	SpawnEggItem(int itemID);

public:
	int getIcon(const ItemStack* pItem) const override;
	std::string getDescriptionId(ItemStack& item) const override;
	Color getColor(int data) const override;
	bool useOn(ItemStack& itemStack, Player& player, const TilePos& pos, Facing::Name face) const override;

	static bool SpawnCreature(Level& level, EntityType::ID entityType, const Vec3& pos);
};
