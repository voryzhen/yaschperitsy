#pragma once

#include "Components/Component.hpp"
#include "Events/Event.hpp"
#include "IOSystem/Renderer.hpp"
#include "Logger/Logger.hpp"
#include "TypesID.hpp"
#include <vector>

class Entity;
using EntityPtr = std::shared_ptr<Entity>;
using EntityArray = std::vector<EntityPtr>;

class Entity : public std::enable_shared_from_this<Entity>
{
    public:
        explicit Entity(EntityTypeID typeID = get_entity_typeID<Entity>())
            : typeID_(typeID)
        {
        }

        virtual ~Entity() = default;

        virtual void events();
        virtual void update();
        virtual void render(const Renderer& ren);
        virtual void on_event(const EventSPtr& event);

        bool is_active() const { return active_; }
        void destroy() { active_ = false; }

        EntityTypeID get_typeID() const { return typeID_; };

        template <typename T>
        bool has_component() const
        {
            const auto it = components_.find(get_component_typeID<T>());
            return it != components_.end();
        }

        template <typename T>
        std::shared_ptr<T> get_component() const
        {
            if (const auto it = components_.find(get_component_typeID<T>());
                it != components_.end())
            {
                return std::static_pointer_cast<T>(it->second);
            }
            Logger().error("Can not find component with TypeID: {}",
                           get_component_typeID<T>());
            return nullptr;
        }

        template <typename T, typename... TArgs>
        std::shared_ptr<T> add_component(TArgs&&... args)
        {
            std::shared_ptr<T> component =
                std::make_shared<T>(std::forward<TArgs>(args)...);
            component->owner_ = this->weak_from_this();
            component->init();
            components_[get_component_typeID<T>()] = component;
            return component;
        }

        bool is_intersect(const EntityPtr& entity) const;

    private:
        ComponentStore components_;
        bool active_ { true };
        EntityTypeID typeID_;
};
