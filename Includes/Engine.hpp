#pragma once

#include "Audio/AudioComponent.hpp"
#include "EntityManager/EntityManager.hpp"
#include "EventHandling/EventHandler.hpp"
#include "EventHandling/InputHandler.hpp"
#include "Scene/Scene.hpp"
#include "Time/TimeComponent.hpp"
#include "Video/TextureComponent.hpp"
#include "Video/VideoComponent.hpp"


class Engine {
public:
    std::function<void()> whileRunning{};

    explicit Engine(const std::string &title);

    // SETTERS
    template<IsScene T>
    T& add(std::unique_ptr<T> scene) noexcept {
        const auto key = scene->instance_id();
        T& sceneRef = *scene;
        scenes_.emplace(key, std::move(scene));

        if (!currentScene_) currentScene_ = &sceneRef;

        return sceneRef;
    }

    template<IsScene T = EntityManager, typename... Args>
    T& make(Args&&... args) noexcept {
        auto newScene = std::make_unique<T>(*this, std::forward<Args>(args)...);
        return add(std::move(newScene));
    }

    void display(sf::Drawable &drawable) noexcept;

    void display(sf::Drawable &&drawable) noexcept;

    // GETTERS
    [[nodiscard]] EventHandler &getEventHandler() noexcept;

    [[nodiscard]] AudioComponent &getAudio() noexcept;

    [[nodiscard]] const AudioComponent &getAudio() const noexcept;

    [[nodiscard]] TextureComponent &getTextures() noexcept;

    [[nodiscard]] const TextureComponent &getTextures() const noexcept;

    [[nodiscard]] const VideoComponent &getVideo() const noexcept;

    [[nodiscard]] VideoComponent &getVideo() noexcept;

    [[nodiscard]] const InputHandler &getInput() const noexcept;

    [[nodiscard]] const TimeComponent &time() const noexcept;

    [[nodiscard]] Scene &currentScene() const noexcept;

    [[nodiscard]] std::vector<sf::Drawable *> &getDrawables() noexcept;

    void run() noexcept;

private:
    id::UMap<Scene, std::unique_ptr<Scene> > scenes_{};
    Scene *currentScene_{nullptr};
    const std::string gameTitle_{};
    std::vector<sf::Drawable *> drawables_{};

    // COMPONENTS
    EventHandler eventHandler_{};
    VideoComponent video_;
    AudioComponent audio_{};
    InputHandler input_{eventHandler_, video_};
    TimeComponent time_{};
    TextureComponent textures_{};

    void update();
};
