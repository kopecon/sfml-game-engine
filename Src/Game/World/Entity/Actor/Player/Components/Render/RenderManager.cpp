#include "Game/Game.hpp"
#include "Game/Engines/SceneGraph/RectangleShape.hpp"
#include "Game/World/Entity/Actor/Player/Components/Render/RenderManager.hpp"
#include "Game/World/Entity/Actor/Player/Components/Render/PlayerSprite.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"


namespace player {
    RenderManager::RenderManager(Player &player, Render &render)
        : player_(player),
          render_(render),
          mainSprite_(render.add(std::make_unique<PlayerSprite>(player))) {
        // RENDER
        render_.setOrigin({
            render_.getCenter().x,
            render_.getCenter().y + 0.5f * render_.getGlobalBounds().size.y
        });
        // player_.getRender().showOutline(sf::Color::Blue);
    }

    PlayerSprite &RenderManager::getMainSprite() const {
        return mainSprite_;
    }
} // player
