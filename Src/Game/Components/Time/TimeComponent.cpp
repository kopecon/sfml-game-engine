//
// Created by Andrew on 02/12/2025.
//

#include "Game/Components/Time/TimeComponent.hpp"
#include "SFML/System/Time.hpp"


float TimeComponent::dt() const {
    return dt_;
}

void TimeComponent::update() {
    dt_ = clock_.restart().asSeconds(); // seconds since last frame
}
