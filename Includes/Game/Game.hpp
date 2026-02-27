#ifndef BONK_GAME_GAME_HPP
#define BONK_GAME_GAME_HPP

#include "Game/Components/Video/VideoComponent.hpp"
#include "Game/Components/Audio/AudioComponent.hpp"
#include "Game/Engines/EventHandling/EventHandler.hpp"
#include "Game/Engines/EventHandling/InputHandler.hpp"
#include "Game/Engines/PhysicsEngine.hpp"
#include "Game/Components/Video/TextureComponent.hpp"
#include "Game/Components/Time/TimeComponent.hpp"
#include "Game/World/World.hpp"


class Game {
public:
#pragma region constructors
    explicit Game(const std::string &title);
#pragma endregion

    // SETTERS
    World& createWorld(std::string name);
    // GETTERS
    [[nodiscard]] EventHandler& getEventHandler();
    [[nodiscard]] AudioComponent& getAudio();
    [[nodiscard]] const VideoComponent& getVideo() const;
    [[nodiscard]] VideoComponent& getVideo();
    [[nodiscard]] const InputHandler& getInput() const;
    [[nodiscard]] const TimeComponent& getTime() const;
    [[nodiscard]] const TextureComponent& getTextures() const;
    [[nodiscard]] const PhysicsEngine& getPhysics() const;
    [[nodiscard]] World* getWorld(std::string name);
    [[nodiscard]] World& getCurrentWorld() const;
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
