#include "boost/test/unit_test.hpp"

#include "core/ecs/components/FireComponent.h"
#include "core/ecs/components/KeyboardController.h"
#include "core/ecs/components/MouseController.h"
#include "core/ecs/components/SpriteComponent.h"
#include "core/ecs/components/TransformComponent.h"

#include <core/ecs/Entity.h>

BOOST_AUTO_TEST_SUITE(ecs_components_unit_tests_suite)

BOOST_AUTO_TEST_CASE(components_test)
{
    using namespace yaschperitsy::ecs;
    using namespace yaschperitsy::ecs::components;

    auto ent = Entity(yaschperitsy::ecs::EntityType::ammunition);
    BOOST_CHECK(ent.is_active());

    auto fire_comp = ent.add_component<FireComponent>(5);
    BOOST_CHECK(ent.has_component<FireComponent>());
    auto transform_comp = ent.add_component<TransformComponent>(5, 5);
    BOOST_CHECK(ent.has_component<TransformComponent>());

    BOOST_CHECK(!ent.has_component<SpriteComponent>());
    BOOST_CHECK(!ent.has_component<KeyboardController>());
    BOOST_CHECK(!ent.has_component<MouseController>());

    auto get_fire_comp = ent.get_component<FireComponent>();
    auto get_transform_comp = ent.get_component<TransformComponent>();

    BOOST_CHECK(fire_comp.get() == get_fire_comp.get());
    BOOST_CHECK(transform_comp.get() == get_transform_comp.get());
}

BOOST_AUTO_TEST_CASE(transform_components_test)
{
    using namespace yaschperitsy::ecs;
    using namespace yaschperitsy::ecs::components;

    auto ent = Entity(yaschperitsy::ecs::EntityType::ammunition);
    auto transform_comp = ent.add_component<TransformComponent>(5, 5);
    BOOST_CHECK(ent.has_component<TransformComponent>());

    transform_comp->set_velocity({2, 2});

    auto pos = transform_comp->position();
    BOOST_CHECK((pos.x() == 5) && (pos.y() == 5));
    ent.update({});
    auto new_pos = transform_comp->position();
    BOOST_CHECK((new_pos.x() == 11) && (new_pos.y() == 11));
}

BOOST_AUTO_TEST_SUITE_END()
