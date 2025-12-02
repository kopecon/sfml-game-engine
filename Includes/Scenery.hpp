//
// Created by Andrew on 01/12/2025.
//

#ifndef BONK_GAME_SCENERY_HPP
#define BONK_GAME_SCENERY_HPP
#include "Camera.hpp"
#include "Entity.hpp"
#include "World.hpp"


class Scenery : public Entity {
public:
    explicit Scenery(const char* name) : Entity(name){};
    bool looping{false};
    Camera *pCamera{};

    void setCamera() {
        pCamera = &pWorld->pGame->video.camera;
    }

    void init(sf::Shape &shape, sf::Texture &texture) override {
        pShape = &shape;
        pTexture = &texture;
        pTexture->setRepeated(true);
        shape.setOrigin(shape.getGeometricCenter());
        shape.setTexture(&texture);
        if (shape.getGlobalBounds().size.x/3.f >= static_cast<sf::Vector2f>(texture.getSize()).x) {
            shape.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(shape.getGlobalBounds().size)));
        }
        else {
            shape.setTextureRect(sf::IntRect({0, 0}, {
                static_cast<int>(texture.getSize().x*3),
                static_cast<int>(texture.getSize().y)})
                );
        }
    }

    void loop() {
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
};


#endif //BONK_GAME_SCENERY_HPP