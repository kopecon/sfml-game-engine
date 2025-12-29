//
// Created by Andrew on 29/12/2025.
//

#ifndef BONK_GAME_RENDER_COMPONENT_HPP
#define BONK_GAME_RENDER_COMPONENT_HPP
#include "SFML/Graphics/RectangleShape.hpp"


namespace player {
    class Player;

    class RenderComponent {
    public:
        explicit RenderComponent(Player &player);

        sf::RectangleShape shape{};

        void initShapeSize();

        Player &player;
    };
} // player

#endif //BONK_GAME_RENDER_COMPONENT_HPP