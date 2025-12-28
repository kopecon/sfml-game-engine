//
// Created by Andrew on 01/12/2025.
//

#include "../../../Includes/Entity/Scenery/Scenery.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


Scenery::Scenery(World &world, std::string name): Entity(world, std::move(name)) {}

void Scenery::setCamera() {
    pCamera = &game.video.camera;
}

sf::Shape * Scenery::getShape() {
    return &shape;
}

void Scenery::loop() {
    if (pCamera == nullptr) setCamera();
    else {
        const auto cameraCenter = pCamera->view.getCenter();
        const auto cameraRBorder = cameraCenter.x + pCamera->view.getSize().x / 2.f;
        const auto cameraLBorder = cameraCenter.x - pCamera->view.getSize().x / 2.f;

        // If camera is viewing outside of background
        if (cameraRBorder >= pShape->getPosition().x + pShape->getGlobalBounds().size.x/2.f) {
         pShape->setPosition({
             cameraRBorder-pCamera->view.getSize().x/2.f+pShape->getGlobalBounds().size.x/stretchFactor,
             pShape->getPosition().y});
        }
        else if (cameraLBorder <= pShape->getPosition().x - pShape->getGlobalBounds().size.x/2.f) {
         pShape->setPosition({
             cameraLBorder+pCamera->view.getSize().x/2.f-pShape->getGlobalBounds().size.x/stretchFactor,
             pShape->getPosition().y});
        }
    }
}

void Scenery::initShapeSize() {
    shape.setSize(static_cast<sf::Vector2f>(pTexture->getSize()));
}

void Scenery::init() {
    Entity::init();
    // pTexture->setRepeated(true); //FIXME
    pShape->setTextureRect(sf::IntRect({0,0}, {static_cast<sf::Vector2i>(shape.getGlobalBounds().size)}));
}

void Scenery::update() {
    loop();
}