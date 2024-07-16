#include "boost/test/unit_test.hpp"
#include "core/ecs/Entity.h"
#include "old_game/entities/Ammunition.h"
#include "old_game/entities/Organism.h"

#include <core/ecs/Manager.h>

BOOST_AUTO_TEST_SUITE(ecs_manager_unit_tests_suite)

BOOST_AUTO_TEST_CASE(manager_test)
{
    using namespace yaschperitsy::ecs;
    using namespace yaschperitsy::game;

    Manager man;

    const auto ent = man.add_entity<Ammunition>(
        AmmunitionType::yaschperitsy_fireball, 100, 100, 1, nullptr);

    const auto entites = man.get_entities();
    const auto named_entites = man.get_entities(EntityType::ammunition);

    BOOST_CHECK(entites.size() == 1);
    BOOST_CHECK(named_entites.size() == 1);
    BOOST_CHECK(entites.back().get() == named_entites.back().get());
    BOOST_CHECK(ent.get() == entites.back().get());

    const auto new_ent = man.add_entity<Organism>(EntityType::player,
                                                  100, 100, 1, nullptr);

    BOOST_CHECK(man.get_entities().size() == 2);
    BOOST_CHECK(man.get_entities(EntityType::player).size() == 1);
    BOOST_CHECK(man.get_entities(EntityType::ammunition).size() == 1);

    ent->destroy();
    man.refresh();

    BOOST_CHECK(man.get_entities().size() == 1);
    BOOST_CHECK(man.get_entities(EntityType::player).size() == 1);
    BOOST_CHECK(man.get_entities(EntityType::ammunition).size() == 0);

    new_ent->destroy();
    man.refresh();

    BOOST_CHECK(man.get_entities().size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
