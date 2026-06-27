//
// Created by Andrew on 22/01/2026.
//

#ifndef BONK_GAME_SPRITE_HPP
#define BONK_GAME_SPRITE_HPP
#include "SFML/Graphics/Sprite.hpp"
#include "Game/Engines/SceneGraph/Colorable.hpp"
#include "Game/Engines/SceneGraph/Composite.hpp"


class Sprite : public Composite, public Colorable {
protected:
    std::unique_ptr<sf::Sprite> sprite_{nullptr};
public:
    explicit Sprite(const sf::Texture &texture);

    Colorable* asColorable() override;

    void applyColor(sf::Color color) override;

    [[nodiscard]] sf::Sprite& getSprite();

    [[nodiscard]] const sf::Sprite& getSprite() const;

private:
    std::optional<sf::FloatRect> getSelfGlobalBounds() const override;

    void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //BONK_GAME_SPRITE_HPP