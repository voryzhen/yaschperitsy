#include "boost/test/unit_test.hpp"

#include "ecs/icomponent.h"
#include <ecs/entity.h>

namespace yaschperitsy::ecs2
{

class Component : public IComponent
{
    public:
        Component() = default;

        Component(int v) : value(v) {}

        void init() override {}

        void update(const SDL_Event& e) override { value++; }

        void render(const app::SDL_RendererUPtr& renderer) override {}

        ~Component() {}

        int value = 0;
};

}; // namespace yaschperitsy::ecs2

BOOST_AUTO_TEST_SUITE(ecs2_entity_unit_tests_suite)

BOOST_AUTO_TEST_CASE(entity_test)
{
    using namespace yaschperitsy::ecs2;

    auto ent = Entity("Entity");
    BOOST_CHECK(ent.is_active());
    BOOST_CHECK(ent.name() == "Entity");

    ent.destroy();
    BOOST_CHECK(!ent.is_active());
}

BOOST_AUTO_TEST_CASE(entity_component_test)
{
    using namespace yaschperitsy::ecs2;

    // clang-format off

    class Comp1 : public Component { public: Comp1(int v) : Component(v){} };
    class Comp2 : public Component { public: Comp2(int v) : Component(v){} };
    class Comp3 : public Component { public: Comp3(int v) : Component(v){} };

    // clang-format on

    auto ent = Entity("Entity");
    auto comp1 = ent.add_component<Comp1>(1);
    auto comp2 = ent.add_component<Comp2>(2);
    auto comp3 = ent.add_component<Comp3>(3);

    BOOST_CHECK(ent.has_component<Comp1>());
    BOOST_CHECK(ent.has_component<Comp2>());
    BOOST_CHECK(ent.has_component<Comp3>());

    auto get_comp1 = ent.get_component<Comp1>();
    auto get_comp2 = ent.get_component<Comp2>();
    auto get_comp3 = ent.get_component<Comp3>();

    BOOST_CHECK(comp1.get() == get_comp1.get());
    BOOST_CHECK(comp2.get() == get_comp2.get());
    BOOST_CHECK(comp3.get() == get_comp3.get());

    ent.update({});

    BOOST_CHECK((dynamic_cast<Comp1*>(comp1.get()))->value == 2);
    BOOST_CHECK((dynamic_cast<Comp2*>(comp2.get()))->value == 3);
    BOOST_CHECK((dynamic_cast<Comp3*>(comp3.get()))->value == 4);
}

BOOST_AUTO_TEST_SUITE_END()
