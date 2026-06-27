#include <unordered_map>
#include "Engine.hpp"
#include "EntityManager/EntityManager.hpp"


Engine::Engine(const std::string &title) : gameTitle_(title), video_(*this, title) {
}

void Engine::display(sf::Drawable &drawable) noexcept {
    drawables_.emplace_back(&drawable);
}

void Engine::display(sf::Drawable &&drawable) noexcept {
    drawables_.emplace_back(&drawable);
}

EventHandler &Engine::getEventHandler() noexcept {
    return eventHandler_;
}

AudioComponent &Engine::getAudio() noexcept {
    return audio_;
}

const AudioComponent &Engine::getAudio() const noexcept {
    return audio_;
}

TextureComponent &Engine::getTextures() noexcept {
    return textures_;
}

const TextureComponent &Engine::getTextures() const noexcept {
    return textures_;
}

const VideoComponent &Engine::getVideo() const noexcept {
    return video_;
}

VideoComponent &Engine::getVideo() noexcept {
    return video_;
}

const InputHandler &Engine::getInput() const noexcept {
    return input_;
}

const TimeComponent &Engine::time() const noexcept {
    return time_;
}

Scene &Engine::currentScene() const noexcept {
    assert(currentScene_ && "No scene.");
    return *currentScene_;
}

std::vector<sf::Drawable *> &Engine::getDrawables() noexcept {
    return drawables_;
}

void Engine::run() noexcept {
    const sf::RenderWindow &window = getVideo().getWindow(); // Reference the engine window

#pragma region window loop
    while (window.isOpen()) {
        update();

        if (whileRunning) {
            whileRunning();
        }
    }
#pragma endregion
}

void Engine::update() {
    time_.update();
    input_.clear();
    eventHandler_.process(video_.getEvents());
    if (currentScene_) currentScene_->update();
    video_.update();
}
