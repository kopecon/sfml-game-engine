//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_GROUND_HPP
#define BONK_GAME_GROUND_HPP

#include "Scenery.hpp"


class Ground final : public Scenery {
public:
    explicit Ground(World &world, entityID ID);
    explicit Ground(World &world, entityID ID, std::string name);

    sf::Color color = sf::Color({40,30,100});
    sf::Texture* getTexture() override;

    void init() override;
};


#endif //BONK_GAME_GROUND_HPP