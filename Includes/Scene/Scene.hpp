# pragma once

#include "EntityManager/EntityManager.hpp"
#include "Physics/PhysicalEnvironment.hpp"


class Scene : public EntityManager, public id::Node<Scene> {
public:
    explicit Scene(Engine &engine);

    [[nodiscard]] const PhysicalEnvironment &environment() const noexcept;

protected:
    PhysicalEnvironment environment_;
};

template<typename T>
concept IsScene = std::derived_from<T, Scene>;
