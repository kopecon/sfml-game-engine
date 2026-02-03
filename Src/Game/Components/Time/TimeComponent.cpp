//
// Created by Andrew on 02/12/2025.
//

#include "Game/Components/Time/TimeComponent.hpp"
#include "SFML/System/Time.hpp"


float TimeComponent::get() const {
    return dt;
}

void TimeComponent::update() {
    dt = clock.restart().asSeconds(); // seconds since last frame
}
