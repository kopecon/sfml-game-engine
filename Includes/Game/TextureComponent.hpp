//
// Created by Andrew on 03/12/2025.
//

#ifndef BONK_GAME_TEXTURE_COMPONENT_HPP
#define BONK_GAME_TEXTURE_COMPONENT_HPP
#include "SFML/Graphics/Texture.hpp"


class TextureComponent {
public:
    sf::Texture player     = sf::Texture(RESOURCES_PATH "Custom/AnimationSheet_Character.png");
    sf::Texture background = sf::Texture(RESOURCES_PATH "Custom/background.jpg");
    sf::Texture bodyGround = sf::Texture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_center.png");
    sf::Texture topGround  = sf::Texture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_top.png");
};


#endif //BONK_GAME_TEXTURE_COMPONENT_HPP