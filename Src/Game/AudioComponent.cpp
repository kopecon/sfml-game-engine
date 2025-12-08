//
// Created by Andrew on 01/12/2025.
//

#include "../../Includes/Game/AudioComponent.hpp"

AudioComponent::AudioComponent():music(sf::Music(RESOURCES_PATH "Audio/Midnight Forest.mp3")) {
    music.setVolume(1);
    music.setLooping(true);
    music.setLoopPoints({sf::milliseconds(0), sf::seconds(3*60)});
}
