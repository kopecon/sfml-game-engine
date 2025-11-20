//
// Created by Andrew on 13/11/2025.
//

#include "../Includes/Background.hpp"

#include <iostream>

namespace scenery {
    Ground::Ground() = default;

    Ground::Ground(sf::Texture &groundTextureRef, sf::Texture &topGroundTextureRef, const sf::RectangleShape &backgroundShape) {
        this->pTexture = &groundTextureRef;
        this->size = backgroundShape.getSize();
        this->pTexture->setRepeated(true);
        this->body.setSize(size);
        this->body.setTexture(pTexture);
        this->body_texture_chunk = {{0, 0}, static_cast<sf::Vector2i>(body.getSize())};
        this->body.setTextureRect(body_texture_chunk);
        this->body.setFillColor(sf::Color({40,30,100}));
        this->body.setPosition({0,backgroundShape.getSize().y-backgroundShape.getSize().y/6.f});

        this->pTextureTop = &topGroundTextureRef;
        this->pTextureTop->setRepeated(true);
        this->top.setSize({size.x, static_cast<float>(pTextureTop->getSize().y)});
        this->top.setTexture(pTextureTop);
        this->top_texture_chunk = {{0, 0}, static_cast<sf::Vector2i>(top.getSize())};
        this->top.setTextureRect(top_texture_chunk);
        this->top.setFillColor(sf::Color({40,30,100}));
        this->top.setPosition({0,body.getPosition().y - top.getSize().y});
    }

    void Ground::loop(const tools::Camera &camera) {
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
    Background::Background() = default;

    Background::Background(sf::Texture &backgroundTextureRef, sf::Texture &groundTextureRef, sf::Texture &topGroundTextureRef,
            const sf::Vector2u &size) {
        this->pTexture = &backgroundTextureRef;
        this->size = size;
        this->pTexture->setRepeated(true);
        this->shape.setSize(static_cast<sf::Vector2f>(size));
        this->shape.setTexture(pTexture);
        this->texture_chunk = {{0, 0}, static_cast<sf::Vector2i>(size)};
        this->shape.setTextureRect(texture_chunk);
        this->floor = Ground(groundTextureRef, topGroundTextureRef,shape);
    }

    void Background::loop(const tools::Camera &camera) {
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
        floor.loop(camera);
    }
}
