//
// Created by Andrew on 01/12/2025.
//

#include "../../Includes/Scenery/Scenery.hpp"

Scenery::Scenery(std::string name): Entity(std::move(name)) {}

void Scenery::setCamera() {
    pCamera = &pWorld->pGame->video.camera;
}

void Scenery::loop() {
    if (pCamera == nullptr) setCamera();
    else {
        const auto camera_center = pCamera->view.getCenter();
        const auto camera_right_border = camera_center.x + pCamera->view.getSize().x / 2.f;
        const auto camera_left_border = camera_center.x - pCamera->view.getSize().x / 2.f;

        // If camera is viewing outside of background
        if (camera_right_border >= pShape->getPosition().x + pShape->getGlobalBounds().size.x) {
            pShape->setPosition({camera_right_border-pShape->getGlobalBounds().size.x/2.f, pShape->getPosition().y});
        }
        else if (camera_left_border <= pShape->getPosition().x) {
            pShape->setPosition({camera_left_border-pShape->getGlobalBounds().size.x/2.f, pShape->getPosition().y});
        }
    }
}

void Scenery::update() {
    if (looping) {
        loop();
    }
}
