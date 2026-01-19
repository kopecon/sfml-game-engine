//
// Created by Andrew on 05/01/2026.
//

#ifndef BONK_GAME_COMPOSITE_HPP
#define BONK_GAME_COMPOSITE_HPP
#include <memory>
#include <string>
#include <vector>

#include "../AnimationEngine/AnimationEngine.hpp"
#include "../AnimationEngine/AnimationSheet.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"


class Composite : public sf::Drawable, public sf::Transformable {
protected:
    std::string name_{"composite"};
    std::unique_ptr<sf::Sprite> sprite_{nullptr};
    std::unique_ptr<sf::RectangleShape> outline_{nullptr};
    std::unique_ptr<AnimationSheet> animationSheet_{nullptr};
    // AnimationEngine animator_{*this};

public:
#pragma region constructors
    explicit Composite();

    explicit Composite(std::string name);

    explicit Composite(sf::Texture &texture);

    explicit Composite(std::unique_ptr<sf::Sprite> sprite);

    explicit Composite(std::string name, sf::Texture &texture);

    explicit Composite(std::string name, std::unique_ptr<sf::Sprite> sprite);
#pragma endregion

    std::vector<std::unique_ptr<Composite>> composites{};

    void add(std::unique_ptr<Composite> composite);

    void add(std::unique_ptr<sf::Sprite> sprite, std::string name = "sprite");

    void setSprite(std::unique_ptr<sf::Sprite> sprite);

    void setColor(const sf::Color &color) const;

    void showOutline(sf::Color color = sf::Color::Red);

    [[nodiscard]] sf::FloatRect getLocalBounds() const;

    [[nodiscard]] sf::FloatRect getGlobalBounds() const;

    [[nodiscard]] sf::Vector2f getCenter() const;

    [[nodiscard]] sf::Sprite* getSprite() const;

    [[nodiscard]] std::string_view getName() const;

    [[nodiscard]] std::vector<sf::Sprite*> getAllSprites() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //BONK_GAME_COMPOSITE_HPP