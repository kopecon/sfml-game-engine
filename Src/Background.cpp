//
// Created by Andrew on 13/11/2025.
//

#include "../Includes/Background.hpp"


Background::Background() = default;

Background::Background(sf::Texture &backgroundTextureRef, const sf::Vector2u &window) {
    this->pTexture = &backgroundTextureRef;
    this->pTexture->setRepeated(true);
    this->size = window;
    this->shape.setSize(static_cast<sf::Vector2f>(window));
    this->shape.setTexture(pTexture);
    this->shape.setTextureRect({{0, 0}, static_cast<sf::Vector2i>(window)});
    this->pShape = &shape;
}

void Background::loop(const Camera &camera) {
    const auto camera_center = camera.view.getCenter();
    const auto camera_right_border = camera_center.x + camera.view.getSize().x / 2.f;
    const auto camera_left_border = camera_center.x - camera.view.getSize().x / 2.f;

    // If camera is viewing outside of background
    if (camera_right_border >= shape.getPosition().x + shape.getSize().x) {
        shape.setPosition({camera_right_border-shape.getSize().x/2.f, shape.getPosition().y});
    }
    else if (camera_left_border <= shape.getPosition().x) {
        shape.setPosition({camera_left_border-shape.getSize().x/2.f, shape.getPosition().y});
    }
}

void Background::update() {
    if (looping) {
        loop(pWorld->pGame->video.camera);
    }
}