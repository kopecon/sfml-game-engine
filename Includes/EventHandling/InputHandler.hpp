#pragma once

#include <variant>
#include <unordered_map>
#include <unordered_set>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "EventHandling/EventSubscriber.hpp"


class VideoComponent;

// CHATGPT SOLUTION
class InputHandler final : public EventSubscriber {
public:
    using Button = std::variant<sf::Keyboard::Scancode, sf::Mouse::Button>;

    using ButtonSet = std::unordered_set<Button>;
    using ButtonGroup = std::vector<ButtonSet>;

    struct ButtonState {
        bool pressed{false};
        bool held{false};
        bool released{false};

        static consteval ButtonState null() noexcept {
            return {false, false, false};
        }
    };

    explicit InputHandler(EventHandler &manager, VideoComponent &video);

    void clear();

    void handleEvent(const sf::Event &event) noexcept override;

    [[nodiscard]] const ButtonState &get(Button button) const;

    [[nodiscard]] bool pressed(const ButtonGroup &group) const;

    [[nodiscard]] bool released(const ButtonGroup &group) const;

    [[nodiscard]] bool holds(const ButtonGroup &group) const;

    [[nodiscard]] sf::Vector2f mousePosition() const;

    [[nodiscard]] const ButtonSet &currentButtons() const;

private:
    const ButtonState null_{ButtonState::null()};
    std::unordered_map<Button, ButtonState> buttons_{};
    ButtonSet currentButtons_{};
    VideoComponent &video_;

    [[nodiscard]] bool buttons(const ButtonGroup &group, bool ButtonState::*member) const;
};
