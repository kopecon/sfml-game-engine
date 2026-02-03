//
// Created by Andrew on 01/12/2025.
//

#ifndef BONK_GAME_SCENERY_HPP
#define BONK_GAME_SCENERY_HPP

#include "Game/Components/Video/Camera.hpp"
#include "Game/World/Entity/Entity.hpp"


namespace scenery {
    class Scenery : public entity::Entity {
    public:

#pragma region constructors
        explicit Scenery(World &world, entityID ID);
        explicit Scenery(World &world, entityID ID, std::string name);
#pragma endregion

        sf::RectangleShape shape{};
        float stretchFactor = 3.f;
        const Camera *pCamera{};

        void setCamera();

        sf::Shape *getShape() override;

        void loop();

        void initShapeSize() override;

        void init() override;

        void update() override;
    };
}



#endif //BONK_GAME_SCENERY_HPP