//
// Created by Andrew on 30/12/2025.
//

#ifndef BONK_GAME_RENDER_COMPONENT_HPP
#define BONK_GAME_RENDER_COMPONENT_HPP
#include <memory>
#include <vector>

#include "SFML/Graphics/Drawable.hpp"


namespace entity {
    class RenderComponent {
    public:
        explicit RenderComponent() = default;

        std::vector<std::unique_ptr<sf::Drawable>> drawables{};

        void addDrawable(std::unique_ptr<sf::Drawable> drawable) {
            drawables.push_back(std::move(drawable));
        }
    };
} // entity

#endif //BONK_GAME_RENDER_COMPONENT_HPP