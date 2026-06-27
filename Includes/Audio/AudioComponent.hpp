#pragma once

#include "SFML/Audio/Music.hpp"

class AudioComponent {
public:
    AudioComponent() = default;

    [[nodiscard]] sf::Music& getMusic() noexcept { return music_; }

    [[nodiscard]] const sf::Music& getMusic() const noexcept { return music_; }

private:
    sf::Music music_;
};