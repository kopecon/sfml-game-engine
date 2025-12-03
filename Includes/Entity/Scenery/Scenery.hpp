//
// Created by Andrew on 01/12/2025.
//

#ifndef BONK_GAME_SCENERY_HPP
#define BONK_GAME_SCENERY_HPP

#include "../../Game/Camera.hpp"
#include "../../Entity/Entity.hpp"


class Scenery : public Entity {
public:
    explicit Scenery(std::string name);
    sf::RectangleShape shape{};
    int stretchFactor = 3;
    Camera *pCamera{};

    void setCamera();

    sf::Shape *getShape() override;

    void loop();

    void initShapeSize() override;

    void init() override;

    void update() override;
};


#endif //BONK_GAME_SCENERY_HPP