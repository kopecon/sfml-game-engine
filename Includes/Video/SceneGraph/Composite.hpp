#pragma once

#include <memory>
#include <ranges>
#include <utility>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Identification/Maps.hpp"
#include "Identification/Identities.hpp"


class Animatable;
class Colorable;

namespace render {
    class Composite : public sf::Drawable, public sf::Transformable, public id::Node<Composite> {
        class Outline final : public sf::RectangleShape {
        public:
            explicit Outline(sf::FloatRect bounds = {{0.f, 0.f}, {0.f, 0.f}});

            bool visible{false}; // Sets visibility for this instance.
            static constexpr bool visibleAll{false}; // Sets visibility for every outline objet.
        };

    public:
        bool visible{true}; // This sets visibility to the whole composite

#pragma region constructors
        explicit Composite();

        // Add Move Constructor
        Composite(Composite &&other) noexcept;

        // Add Move Assignment
        Composite &operator=(Composite &&other) noexcept;

        // Disable Copying (standard for Scene Graphs to prevent pointer chaos)
        Composite(const Composite &) = delete;

        Composite &operator=(const Composite &) = delete;

#pragma endregion
        // ACTIONS
        void play(float dt) noexcept;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const noexcept override;

        // SETTERS
        template<typename T>
            requires (std::is_base_of_v<Composite, T>)
        T &add(std::unique_ptr<T> composite) noexcept;

        void recolor(const sf::Color &color) noexcept;

        void resize(sf::Vector2f targetSize) noexcept;

        void fit(sf::Vector2f size) noexcept;

        void cover(sf::Vector2f size) noexcept;

        void showOutline(sf::Color color = sf::Color::Red) const noexcept;

        void toggleOutline() const noexcept;

        // GETTERS
        virtual Animatable *asAnimatable() noexcept;

        virtual Colorable *asColorable() noexcept;

        [[nodiscard]] virtual sf::FloatRect getLocalBounds() const noexcept;

        [[nodiscard]] sf::FloatRect getGlobalBounds() const noexcept;

        [[nodiscard]] sf::Transform getGlobalTransform() const noexcept;

        [[nodiscard]] sf::Vector2f getCenter() const noexcept;

        [[nodiscard]] id::OMap<Composite, std::unique_ptr<Composite> > &getChildren() noexcept;

        [[nodiscard]] bool contains(sf::Vector2f pos) const noexcept;

        [[nodiscard]] std::vector<sf::Vector2f> getNormals() noexcept;

        template<typename T>
        [[nodiscard]] T &get(TypeTag<T> type) const noexcept;

        [[nodiscard]] virtual Transformable &kernel() noexcept;

        [[nodiscard]] virtual const Transformable &kernel() const noexcept;

        [[nodiscard]] float circumcircleRadius() const noexcept;

    protected:
        id::OMap<Composite, std::unique_ptr<Composite> > children_{};
        std::vector<sf::Vector2f> normals_{};
        std::unique_ptr<Outline> outline_{std::make_unique<Outline>()};

        // GETTERS
        [[nodiscard]] virtual std::optional<sf::FloatRect> getSelfGlobalBounds() const noexcept;

    private:
        Composite *parent_{nullptr};

        // ACTIONS
        virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const noexcept = 0;

        virtual void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const noexcept;

        virtual void drawOutline(sf::RenderTarget &target, sf::RenderStates states) const noexcept;

        virtual void updateNormals() noexcept;
    };

    template<typename T> requires (std::is_base_of_v<Composite, T>)
    T &Composite::add(std::unique_ptr<T> composite) noexcept {
        assert(composite.get() != this && "Cannot add myself as a child!");
        assert(composite->parent_ == nullptr && "This child already has a parent!");
        T &ref = *composite;
        ref.parent_ = this;
        children_.emplace(Node<T, Composite>::NodeID(), std::move(composite));
        return ref;
    }

    template<typename T>
    T &Composite::get(TypeTag<T> type) const noexcept {
        const auto key = Node<T, Composite>::NodeID();
        if (children_.contains(key)) {
            auto &base = *children_.at(key);
            return static_cast<T &>(base);
        }
        for (const auto &child: children_ | std::views::values) {
            return child->get(type);
        }
        assert(false && "Composite not found!\n");
        std::unreachable();
    }
} // render
