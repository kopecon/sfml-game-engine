//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_GROUND_HPP
#define BONK_GAME_GROUND_HPP

#include "../Entity.hpp"


namespace scenery {
    class Ground final : public entity::Entity {
    public:

#pragma region constructors
        explicit Ground(World &world, entityID ID, std::string name);
        [[nodiscard]] static std::string getClassName();
#pragma endregion

        sf::Color color = sf::Color({40,30,100});

        void buildRender();

        void update() override;
    };
}


#endif //BONK_GAME_GROUND_HPP