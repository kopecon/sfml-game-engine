//
// Created by Andrew on 02/12/2025.
//

#include "../../Includes/Game/TimeComponent.hpp"
#include "SFML/System/Time.hpp"


float TimeComponent::get() const {
    return dt;
}

void TimeComponent::update() {
    dt = clock.restart().asSeconds(); // seconds since last frame
}
