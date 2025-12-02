//
// Created by Andrew on 27/11/2025.
//

#include "../Includes/Ground.hpp"
#include "../Includes/World.hpp"

Ground::Ground(const char* name) : Scenery(name){}

Ground::Ground(const char* name, const sf::Vector2u &windowSize, sf::Texture &bodyTexture, sf::Texture &topTexture) :
Scenery(name) {
    // TOP
    top.setSize({
        static_cast<float>(windowSize.x*3),
        static_cast<float>(topTexture.getSize().y)});
    Scenery::init(top, topTexture);
    top.setFillColor(sf::Color({40,30,100}));
    // BODY
    body.setSize({
        static_cast<float>(windowSize.x*3),
        static_cast<float>(bodyTexture.getSize().y)});
    Scenery::init(body, bodyTexture);
    body.setFillColor(sf::Color({40,30,100}));

    pShapes.emplace(pShapes.end(), &body);
    pShapes.emplace(pShapes.end(), &top);
    pTextures.emplace(pTextures.end(), &topTexture);
    pTextures.emplace(pTextures.end(), &bodyTexture);
}

void Ground::setGroundLevel() {
    top.setPosition({top.getPosition().x, pWorld->groundLevel+top.getSize().y/2.f});
    body.setPosition({body.getPosition().x, top.getPosition().y+top.getSize().y});
}

void Ground::update() {
    if (looping) {
        loop();
    }
}
