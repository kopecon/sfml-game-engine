//
// Created by Andrew on 30/12/2025.
//

#ifndef BONK_GAME_RENDER_HPP
#define BONK_GAME_RENDER_HPP

#include "Composite.hpp"


namespace entity {
    class Entity;
}


class Render final : public Composite {
    entity::Entity &entity_;

public:
    explicit Render(entity::Entity &entity);

    void loop() const;

    void update();

private:
    void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;
};
#endif //BONK_GAME_RENDER_HPP