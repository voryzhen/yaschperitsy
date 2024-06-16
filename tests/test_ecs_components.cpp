#include "boost/test/unit_test.hpp"

#include "ecs/components/fire_component.h"
#include "ecs/components/keyboard_controller.h"
#include "ecs/components/mouse_controller.h"
#include "ecs/components/sprite_component.h"
#include "ecs/components/transform_component.h"

#include <ecs/entity.h>

BOOST_AUTO_TEST_SUITE(ecs_components_unit_tests_suite)

BOOST_AUTO_TEST_CASE(components_test)
{
    using namespace yaschperitsy::ecs;
    using namespace yaschperitsy::ecs::components;

    auto ent = Entity("Entity");
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

    auto ent = Entity("Entity");
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
