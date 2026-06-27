#include "Game/World//Entity/Scenery/Ground.hpp"
#include "Game/Game.hpp"
#include "Game/Engines/SceneGraph/Sprite.hpp"
#include "Game/World/World.hpp"


namespace scenery {

#pragma region constructors
    Ground::Ground(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name))
        {
            buildRender();
        }

    std::string Ground::getClassName() {
        return "Ground";
    }
#pragma endregion

    void Ground::buildRender() {
        auto &topTex = game.getTextures().topGround;
        auto &bottomTex = game.getTextures().bottomGround;

        auto top = std::make_unique<Sprite>(topTex);
        top->rename("top");
        auto bottom = std::make_unique<Sprite>(bottomTex);
        bottom->rename("bottom");
        // Stretch to window size * 3 and repeat texture.
        top->getSprite().setTextureRect(
            sf::IntRect({0, 0},
                sf::Vector2i(
                    static_cast<int>(game.getVideo().getWindowSize().x)*3,
                    static_cast<int>(top->getGlobalBounds().size.y)
                )
            )
        );
        bottom->getSprite().setTextureRect(
            sf::IntRect({0, 0},
                sf::Vector2i(
                    static_cast<int>(game.getVideo().getWindowSize().x)*3,
                    static_cast<int>(bottom->getGlobalBounds().size.y)
                )
            )
        );

        bottom->move({top->getPosition().x, top->getPosition().y + top->getGlobalBounds().size.y});

        render_.add(std::move(top));
        render_.add(std::move(bottom));
        render_.setColor(color);
        render_.setOrigin({render_.getCenter().x, 0});
    }

    void Ground::update() {
        render_.loop();
    }
}
