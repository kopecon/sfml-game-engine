//
// Created by Andrew on 30/12/2025.
//

#ifndef BONK_GAME_RENDER_COMPONENT_HPP
#define BONK_GAME_RENDER_COMPONENT_HPP
#include <memory>
#include <vector>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Composite.hpp"


namespace entity {
    class Entity;
}


class Render final: public sf::Drawable, public sf::Transformable  {
protected:
    std::vector<std::unique_ptr<Composite>> composites{};
    entity::Entity &entity;
    std::unique_ptr<sf::RectangleShape> boundary{};

public:
    explicit Render(entity::Entity &entity);

    void addComposite(std::unique_ptr<Composite> composite);

    void addShape(std::unique_ptr<sf::Shape> shape);

    void setFillColor(const sf::Color &color) const;

    void showBoundary(sf::Color color = sf::Color::Red);

    Composite& getComposite(const Composite &composite);

    [[nodiscard]] std::vector<std::unique_ptr<Composite>>& getComposites();

    [[nodiscard]] sf::FloatRect getLocalBounds() const;

    [[nodiscard]] sf::FloatRect getGlobalBounds() const;

    [[nodiscard]] sf::Vector2f getCenter() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void init();

    void update();
};


#endif //BONK_GAME_RENDER_COMPONENT_HPP