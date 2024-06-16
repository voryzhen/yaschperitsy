#include "boost/test/unit_test.hpp"

#include <ecs/manager.h>

BOOST_AUTO_TEST_SUITE(ecs_manager_unit_tests_suite)

BOOST_AUTO_TEST_CASE(manager_test)
{
    yaschperitsy::ecs::Manager man;

    const auto ent = man.add_entity("Entity name");

    const auto entites = man.get_entities();
    const auto named_entites = man.get_entities_by_name("Entity name");

    BOOST_CHECK(entites.size() == 1);
    BOOST_CHECK(named_entites.size() == 1);
    BOOST_CHECK(entites.back().get() == named_entites.back().get());
    BOOST_CHECK(ent.get() == entites.back().get());

    const auto new_ent = man.add_entity("New entity name");

    BOOST_CHECK(man.get_entities().size() == 2);
    BOOST_CHECK(man.get_entities_by_name("Entity name").size() == 1);
    BOOST_CHECK(man.get_entities_by_name("New entity name").size() ==
                1);

    ent->destroy();
    man.refresh();

    BOOST_CHECK(man.get_entities().size() == 1);
    BOOST_CHECK(man.get_entities_by_name("Entity name").size() == 0);
    BOOST_CHECK(man.get_entities_by_name("New entity name").size() ==
                1);

    new_ent->destroy();
    man.refresh();

    BOOST_CHECK(man.get_entities().size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
