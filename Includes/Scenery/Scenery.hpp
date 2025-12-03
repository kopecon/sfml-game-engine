//
// Created by Andrew on 01/12/2025.
//

#ifndef BONK_GAME_SCENERY_HPP
#define BONK_GAME_SCENERY_HPP
#include "../Game/Camera.hpp"
#include "../Entity/Entity.hpp"
#include "../World/World.hpp"


class Scenery : public Entity {
public:
    explicit Scenery(std::string name);;
    bool looping{false};
    Camera *pCamera{};

    void setCamera();

    void loop();

    void update() override;
};


#endif //BONK_GAME_SCENERY_HPP