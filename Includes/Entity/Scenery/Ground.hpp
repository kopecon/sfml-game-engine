//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_GROUND_HPP
#define BONK_GAME_GROUND_HPP

#include "Scenery.hpp"


class Ground final : public Scenery {
public:
    explicit Ground(World &world, std::string name);

    sf::Color color = sf::Color({40,30,100});
    const sf::Texture* getTexture() override;

    void init() override;
};


#endif //BONK_GAME_GROUND_HPP