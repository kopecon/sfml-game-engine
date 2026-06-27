#include <utility>
#include "EntityManager/EntityManager.hpp"
#include "Engine.hpp"


EntityManager::EntityManager(Engine &engine)
    : engine(engine) {
}

void EntityManager::update() {
    // REMOVE FLAGGED MEMBERS
    std::erase_if(
        entities_,
        [](const auto &entity) { return entity.second->markedForRemoval_; }
    );

    std::erase_if(
        actors_,
        [](const auto &entity) { return entity.second->markedForRemoval_; }
    );

    // UPDATE MEMBERS
    for (const auto &actor: actors_ | std::views::values) {
        if (actor->markedForRemoval_) continue;
        actor->update();
    }

    for (const auto &entity: entities_ | std::views::values) {
        if (entity->markedForRemoval_) continue;
        entity->update();
    }

    // ADD NEW MEMBERS
    for (auto &actor: actorAddQue_) {
        actors_.emplace(actor->Node<Actor>::instance_id(), std::move(actor));
    }
    actorAddQue_.clear();

    for (auto &entity: entityAddQue_) {
        entities_.emplace(entity->instance_id(), std::move(entity));
    }
    entityAddQue_.clear();
}
