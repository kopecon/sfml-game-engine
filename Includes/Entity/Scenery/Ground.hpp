//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_GROUND_HPP
#define BONK_GAME_GROUND_HPP

#include "Scenery.hpp"


namespace scenery {
    class Ground final : public Scenery {
    public:

#pragma region constructors
        explicit Ground(World &world, entityID ID);
        explicit Ground(World &world, entityID ID, std::string name);
        [[nodiscard]] std::string className() const override;
#pragma endregion

        sf::Color color = sf::Color({40,30,100});
        sf::Texture* getTexture() override;

        void buildRender() override;
    };
}


#endif //BONK_GAME_GROUND_HPP