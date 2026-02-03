//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_BACKGROUND_HPP
#define BONK_GAME_BACKGROUND_HPP
#include <SFML/Graphics.hpp>

#include "Game/World/Entity/Entity.hpp"


namespace scenery {
    class Background final : public entity::Entity {
    public:

#pragma region constructors
        explicit Background(World &world, entityID ID, std::string name);
        [[nodiscard]] static  std::string getClassName();
#pragma endregion

        void buildRender();

        void update() override;
    };
}

#endif //BONK_GAME_BACKGROUND_HPP