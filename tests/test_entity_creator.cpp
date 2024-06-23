#include "boost/test/unit_test.hpp"
#include "game/entities/Ammunition.h"
#include "game/entities/Organism.h"

#include <ecs/Entity.h>
#include <ecs/EntityCreator.h>
#include <memory>

BOOST_AUTO_TEST_SUITE(entity_creator_unit_tests_suite)

BOOST_AUTO_TEST_CASE(empty_entity_creator)
{
    using namespace yaschperitsy::game;
    using namespace yaschperitsy::ecs;

    auto player = EntityCreator::create_entity<Organism>(
        EntityType::player, 0, 0, 0, nullptr);
    BOOST_CHECK(player->type() == EntityType::player);

    auto enemy = EntityCreator::create_entity<Organism>(
        EntityType::yaschperitsa, 0, 0, 0, nullptr);
    BOOST_CHECK(enemy->type() == EntityType::yaschperitsa);

    auto bullet = EntityCreator::create_entity<Ammunition>(
        AmmunitionType::yaschperitsy_fireball, 0, 0, 0, nullptr);
    BOOST_CHECK(bullet->type() == EntityType::ammunition);
    BOOST_CHECK(
        std::static_pointer_cast<Ammunition>(bullet)->ammo_type() ==
        AmmunitionType::yaschperitsy_fireball);

    auto plasma = EntityCreator::create_entity<Ammunition>(
        AmmunitionType::plasma_shot, 0, 0, 0, nullptr);
    BOOST_CHECK(plasma->type() == EntityType::ammunition);
    BOOST_CHECK(
        std::static_pointer_cast<Ammunition>(plasma)->ammo_type() ==
        AmmunitionType::plasma_shot);
}

BOOST_AUTO_TEST_SUITE_END()
