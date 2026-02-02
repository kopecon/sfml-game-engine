//
// Created by Andrew on 29/11/2025.
//

#include "Game/Game.hpp"
#include "Game/World/World.hpp"
#include <unordered_map>


Game::Game(const std::string &title):
    title_(title),
    video_(*this, title)
    {}

World& Game::createWorld(std::string name) {
    auto world = std::make_unique<World>(*this, std::move(name));
    const std::string key = world->name;
    auto [it, inserted] = worlds_.emplace(key, std::move(world));
    World& worldRef = *it->second;
    pCurrentWorld_ = &worldRef;  //TODO: temporary
    return worldRef;
}

EventHandler & Game::getEventHandler() {
    return eventHandler_;
}

World* Game::getWorld(std::string name) {
    const auto NAME = text::up(std::move(name));
    const auto it = worlds_.find(NAME);
    if (it == worlds_.end()) {
        std::cerr << "World with name: " << name << " was not found.\n";
        return nullptr;
    }
    return it->second.get();
}

World & Game::getCurrentWorld() const {
    return *pCurrentWorld_;
}

AudioComponent & Game::getAudio() {
    return audio_;
}

VideoComponent & Game::getVideo() {
    return video_;
}

InputHandler & Game::getInput() {
    return input_;
}

TimeComponent & Game::getTime() {
    return time_;
}

TextureComponent & Game::getTextures() {
    return textures_;
}

PhysicsEngine & Game::getPhysics() {
    return physics_;
}

void Game::update() {
    video_.update();
    input_.clear();
    time_.update();
    eventHandler_.process(video_.getEvents());
    pCurrentWorld_->update();
}
