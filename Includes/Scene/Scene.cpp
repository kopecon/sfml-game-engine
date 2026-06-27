
#include "Scene.hpp"

Scene::Scene(Engine &engine): EntityManager(engine) {
}

const PhysicalEnvironment & Scene::environment() const noexcept {
    return environment_;
}
