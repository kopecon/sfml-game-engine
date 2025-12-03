//
// Created by Andrew on 01/12/2025.
//

#ifndef BONK_GAME_AUDIOCOMPONENT_HPP
#define BONK_GAME_AUDIOCOMPONENT_HPP
#include "SFML/Audio/Music.hpp"


class AudioComponent {
public:
    AudioComponent():music(sf::Music(RESOURCES_PATH "Audio/Midnight Forest.mp3")) {
        music.setVolume(1);
        music.setLooping(true);
        music.setLoopPoints({sf::milliseconds(0), sf::seconds(3*60)});
    }
    sf::Music music;
};


#endif //BONK_GAME_AUDIOCOMPONENT_HPP