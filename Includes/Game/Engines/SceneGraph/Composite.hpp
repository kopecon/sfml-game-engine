#ifndef BONK_GAME_COMPOSITE_HPP
#define BONK_GAME_COMPOSITE_HPP

#include <memory>
#include <string>
#include <vector>
#include <ranges>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class Animatable;
class Colorable;


class Composite : public sf::Drawable, public sf::Transformable {
public:
#pragma region constructors
    explicit Composite();
#pragma endregion

    // ACTIONS
    void play(float dt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    // SETTERS
    template <typename T>
    requires (std::is_base_of_v<Composite, T>)
    T& add(std::unique_ptr<T> composite){
        T& ref = *composite;
        children_.push_back(std::move(composite));
        return ref;
    }
    void rename(std::string name);
    void setColor(const sf::Color &color);
    void showOutline(sf::Color color = sf::Color::Red);
    // GETTERS
    virtual Animatable* asAnimatable();
    virtual Colorable* asColorable();
    [[nodiscard]] virtual sf::FloatRect getLocalBounds() const;
    [[nodiscard]] sf::FloatRect getGlobalBounds() const;
    [[nodiscard]] sf::Vector2f getCenter() const;
    [[nodiscard]] std::string_view getName() const;
    [[nodiscard]] std::vector<std::unique_ptr<Composite>>& getChildren();
    [[nodiscard]] Composite& get(std::string name) const;

protected:
    std::string name_{"composite"};
    std::vector<std::unique_ptr<Composite>> children_{};
    std::unique_ptr<sf::RectangleShape> outline_{nullptr};

    // GETTERS
    [[nodiscard]] virtual std::optional<sf::FloatRect> getSelfGlobalBounds() const;

private:
    // ACTIONS
    virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    virtual void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawOutline(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //BONK_GAME_COMPOSITE_HPP