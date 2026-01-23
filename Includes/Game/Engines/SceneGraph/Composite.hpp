//
// Created by Andrew on 05/01/2026.
//

#ifndef BONK_GAME_COMPOSITE_HPP
#define BONK_GAME_COMPOSITE_HPP
#include <memory>
#include <string>
#include <vector>

#include "Colorable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"


class Animatable;

class Composite : public sf::Drawable, public sf::Transformable {
protected:
    std::string name_{"composite"};
    std::unique_ptr<sf::Sprite> sprite_{nullptr};
    std::unique_ptr<sf::RectangleShape> outline_{nullptr};
    std::vector<std::unique_ptr<Composite>> children_{};

public:
#pragma region constructors
    explicit Composite();
#pragma endregion

    virtual Animatable* asAnimatable();

    virtual Colorable* asColorable();

    void add(std::unique_ptr<Composite> composite);

    void rename(std::string name);

    void setColor(const sf::Color &color);

    void showOutline(sf::Color color = sf::Color::Red);

    [[nodiscard]] virtual sf::FloatRect getLocalBounds() const = 0;

    [[nodiscard]] sf::FloatRect getGlobalBounds() const;

    [[nodiscard]] sf::Vector2f getCenter() const;

    [[nodiscard]] std::string_view getName() const;

    [[nodiscard]] std::vector<std::unique_ptr<Composite>>& getChildren();

    bool play(float dt);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    [[nodiscard]] sf::FloatRect getChildrenLocalBounds() const;

    [[nodiscard]] sf::FloatRect getChildrenGlobalBounds() const;

private:
    virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    virtual void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

};


#endif //BONK_GAME_COMPOSITE_HPP