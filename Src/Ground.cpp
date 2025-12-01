//
// Created by Andrew on 27/11/2025.
//

#include "../Includes/Ground.hpp"


Ground::Ground() = default;

Ground::Ground(sf::Texture &groundTextureRef, sf::Texture &topGroundTextureRef, const sf::Vector2u &window, const float &groundLevel) {
    // TOP
    this->pTextureTop = &topGroundTextureRef;
    this->pTextureTop->setRepeated(true);
    this->top.setSize({static_cast<float>(window.x), static_cast<float>(pTextureTop->getSize().y)});
    this->top.setTexture(pTextureTop);
    this->top.setTextureRect({{0, 0}, static_cast<sf::Vector2i>(top.getSize())});
    this->top.setFillColor(sf::Color({40,30,100}));
    this->top.setPosition({0, groundLevel});
    // BODY
    this->pTexture = &groundTextureRef;
    this->pTexture->setRepeated(true);
    this->size = {static_cast<float>(window.x), groundLevel-top.getSize().y};
    this->body.setSize(static_cast<sf::Vector2f>(window));
    this->body.setTexture(pTexture);
    this->body.setTextureRect({{0, 0}, static_cast<sf::Vector2i>(body.getSize())});
    this->body.setFillColor(sf::Color({40,30,100}));
    this->body.setPosition({0, groundLevel+top.getSize().y});
    this->pShapes.emplace(pShapes.end(), &body);
    this->pShapes.emplace(pShapes.end(), &top);
}

void Ground::loop(const Camera &camera) {
    const auto camera_center = camera.view.getCenter();
    const auto camera_right_border = camera_center.x + camera.view.getSize().x / 2.f;
    const auto camera_left_border = camera_center.x - camera.view.getSize().x / 2.f;

    // If camera is viewing outside of background
    if (camera_right_border >= body.getPosition().x + body.getSize().x) {
        body.setPosition({camera_right_border-body.getSize().x/2.f, body.getPosition().y});
        top.setPosition({body.getPosition().x, top.getPosition().y});
    }
    else if (camera_left_border <= body.getPosition().x) {
        body.setPosition({camera_left_border-body.getSize().x/2.f, body.getPosition().y});
        top.setPosition({body.getPosition().x, top.getPosition().y});
    }
}

void Ground::update() {
    if (looping) {
        loop(pWorld->pGame->video.camera);
    }
}
