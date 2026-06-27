#include <unordered_map>
#include "Game/Game.hpp"
#include "Game/World/World.hpp"
#include "Utils/logger.hpp"


Game::Game(const std::string &title):
    title_(title),
    video_(*this, title)
    {}

World& Game::createWorld(std::string name) {
    auto world = std::make_unique<World>(*this, std::move(name));
    const std::string key = world->getName();
    auto [it, inserted] = worlds_.emplace(key, std::move(world));
    World& worldRef = *it->second;
    if (!pCurrentWorld_) pCurrentWorld_ = &worldRef;
    return worldRef;
}

EventHandler & Game::getEventHandler() {
    return eventHandler_;
}

World* Game::getWorld(std::string name) {
    const auto NAME = text::up(std::move(name));
    const auto it = worlds_.find(NAME);
    if (it == worlds_.end()) {
        const auto msg = "World with name: " + name + " was not found.";
        LOG_ERROR(msg);
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

const VideoComponent & Game::getVideo() const {
    return video_;
}

VideoComponent & Game::getVideo() {
    return video_;
}

const InputHandler & Game::getInput() const {
    return input_;
}

const TimeComponent & Game::getTime() const {
    return time_;
}

const TextureComponent & Game::getTextures() const {
    return textures_;
}

const PhysicsEngine & Game::getPhysics() const {
    return physics_;
}

void Game::update() {
    video_.update();
    input_.clear();
    time_.update();
    eventHandler_.process(video_.getEvents());
    pCurrentWorld_->update();
}
