#pragma once

#include "Item.hpp"
#include "world/entity/EntityType.hpp"

class SpawnEggItem : public Item
{
public:
	SpawnEggItem(int);

public:
	int getIcon(const ItemStack*) const override;
	std::string getDescriptionId(ItemStack&) const override;
	Color getColor(int data) const override;
	bool useOn(ItemStack&, Player&, const TilePos& pos, Facing::Name face) const override;

	static bool SpawnCreature(Level& level, EntityType::ID entityType, const Vec3& pos);
};
