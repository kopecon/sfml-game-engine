//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_GAME_HPP
#define BONK_GAME_GAME_HPP

#include "VideoComponent.hpp"
#include "AudioComponent.hpp"
#include "Engines/EventHandling/EventHandler.hpp"
#include "Engines/PhysicsEngine.hpp"
#include "TextureComponent.hpp"
#include "TimeComponent.hpp"
#include "../World/World.hpp"


class Game {
public:
#pragma region constructors
    explicit Game(const std::string &title);
#pragma endregion

    // SETTERS
    World& createWorld(std::string name);
    // GETTERS
    EventHandler& getEventHandler();
    AudioComponent& getAudio();
    VideoComponent& getVideo();
    InputHandler& getInput();
    TimeComponent& getTime();
    TextureComponent& getTextures();
    PhysicsEngine& getPhysics();
    World* getWorld(std::string name);
    World& getCurrentWorld() const;
    // UPDATE
    void update();

private:
    // LIST OF ADDED WORLDS
    std::unordered_map<std::string, std::unique_ptr<World>> worlds_{};
    // WORLD ACCESS
    World *pCurrentWorld_{nullptr};
    // META DATA
    const std::string title_{};
    // COMPONENTS
    EventHandler eventHandler_{};
    VideoComponent video_;
    AudioComponent audio_{};
    InputHandler input_{eventHandler_};
    TimeComponent time_{};
    TextureComponent textures_{};
    PhysicsEngine physics_{};
};

#endif //BONK_GAME_GAME_HPP
