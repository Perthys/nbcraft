#pragma once

#include <map>

#include "Item.hpp"
#include "world/entity/EntityType.hpp"

class SpawnEggItem : public Item
{
public:
	class Type
	{
	public:
		Type(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor);

	public:
		EntityType::ID m_spawnedType;
		Color m_primaryColor;
		Color m_secondaryColor;

	public:
		static void initEggs();

		static const Type* GetByEntityTypeID(EntityType::ID id);
		static const std::map<EntityType::ID, Type>& GetEntityEggs() { return entityEggs; }

	private:
		static void _addEgg(EntityType::ID spawnedType, const Color& primaryColor, const Color& secondaryColor);

	private:
		static std::map<EntityType::ID, Type> entityEggs;
	};

public:
	SpawnEggItem(int itemID);

public:
	int getIcon(const ItemStack* pItem) const override;
	std::string getDescriptionId(ItemStack& item) const override;
	std::string getHovertextName(ItemStack& item) const override;
	Color getColor(int auxValue) const override;
	bool useOn(ItemStack& itemStack, Player& player, const TilePos& pos, Facing::Name face) const override;

public:
	static bool SpawnCreature(Level& level, EntityType::ID entityType, const Vec3& pos);
};
