#include "Engine.hpp"
#include "EntityManager/EntityManager.hpp"
#include "Video/VideoComponent.hpp"
#include "math.hpp"


VideoComponent::VideoComponent(Engine &engine, const std::string &title)
    : EventSubscriber(engine.getEventHandler()),
      engine_(engine),
      windowTitle_(title),
      window_(videoMode_, title, sf::Style::Default, windowState_, settings_) {
    window_.setFramerateLimit(fps_);
    initWindowSprite();
    // window_.setVerticalSyncEnabled(true);
}


void VideoComponent::recreateWindow() noexcept {
    window_.create(sf::VideoMode(videoMode_), windowTitle_, sf::Style::Default, windowState_, settings_);
}

const sf::RenderWindow &VideoComponent::getWindow() const noexcept {
    return window_;
}

sf::Vector2u VideoComponent::getWindowSize() const noexcept {
    return window_.getSize();
}

sf::Vector2f VideoComponent::getWindowToScreenRatio() const {
    return utils::math::hd::divide(getWindowSize(), getScreenSize());
}

sf::Vector2u VideoComponent::getScreenSize() noexcept {
    return sf::VideoMode::getDesktopMode().size;
}

const Camera &VideoComponent::getCamera() const noexcept {
    return camera_;
}

Camera &VideoComponent::getCamera() noexcept {
    return camera_;
}

sf::Vector2f VideoComponent::windowToWorld(const sf::Vector2i pos) const noexcept {
    // Map window pixels to the internal 640x320 resolution
    const sf::Vector2f texturePixel = windowSprite_.getInverseTransform().transformPoint(sf::Vector2f(pos));

    // Map internal resolution to the Camera's world coordinates
    return renderTexture_.mapPixelToCoords(sf::Vector2i(texturePixel));
}

std::vector<sf::Event> &VideoComponent::getEvents() noexcept {
    return frameEvents_;
}

sf::RenderTexture &VideoComponent::renderTexture() {
    return renderTexture_;
}

void VideoComponent::update() noexcept {
    // Save current events into frameEvents_.
    pollEvents();

    camera_.update();

    beginFrame();

    draw();

    endFrame();
}

void VideoComponent::initWindowSprite() noexcept {
    const auto winSize = static_cast<sf::Vector2f>(window_.getSize());
    const auto scale2D = utils::math::hd::divide(winSize, GAME_RESOLUTION);

    auto scale = static_cast<float>(std::min(scale2D.x, scale2D.y));

    windowSprite_.setScale({scale, scale});

    const sf::Vector2f offset = (winSize - static_cast<sf::Vector2f>(GAME_RESOLUTION) * scale) / 2.f;

    windowSprite_.setPosition(offset);
}

void VideoComponent::beginFrame() noexcept {
    renderTexture_.clear();
}

// -------------------------------------------------------------------------------------------------------------    DRAW
void VideoComponent::draw() noexcept {
    for (const auto &entity_weak: engine_.currentScene().findAll() | std::views::values) {
        if (!entity_weak.lock()) return;
            auto &entity = *entity_weak.lock();
        if (entity.has<entity::RenderComponent>()) {
            auto &render = entity.render();
            render.update();
            renderTexture_.draw(render);
        }

        if (entity.has<entity::ColliderComponent>()) {
            auto &collider = entity.collider();
            collider.update();
            if (collider.visible_ or entity::ColliderComponent::visibleAll_) renderTexture_.draw(collider.hitbox());
        }
    }

    for (const auto &drawable: engine_.getDrawables()) {
        renderTexture_.draw(*drawable);
    }
}

// -------------------------------------------------------------------------------------------------------------    DRAW

void VideoComponent::endFrame() noexcept {
    renderTexture_.display();
    window_.clear();
    windowSprite_.setTexture(renderTexture_.getTexture());
    window_.draw(windowSprite_);
    window_.display();
}

void VideoComponent::handleClosing() noexcept {
    // Pre-closing procedures implement here. (saving etc...)
    window_.close();
}

void VideoComponent::handlePressedKey(const sf::Event::KeyPressed &keyPressed) noexcept {
    switch (keyPressed.scancode) {
        case sf::Keyboard::Scancode::Escape: {
            handleClosing();
            break;
        }
        case sf::Keyboard::Scancode::U: {
            if (windowState_ == sf::State::Windowed) {
                windowState_ = sf::State::Fullscreen;
            } else if (windowState_ == sf::State::Fullscreen) {
                windowState_ = sf::State::Windowed;
            }
            // Recreate the window
            recreateWindow();
        }
        default: {
        }
    }
}

void VideoComponent::pollEvents() noexcept {
    frameEvents_.clear();
    while (const std::optional event = window_.pollEvent()) {
        if (!event) return;
        frameEvents_.push_back(*event);
    }
}

void VideoComponent::handleEvent(const sf::Event &event) noexcept {
    if (event.is<sf::Event::Closed>()) {
        handleClosing();
    }
    if (const auto keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        handlePressedKey(*keyPressed);
    }
}
