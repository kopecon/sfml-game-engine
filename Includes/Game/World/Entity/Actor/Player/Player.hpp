#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Game/World/Entity/Actor/Actor.hpp"
#include "Game/World/Entity/Actor/Player/Components/Combat/CombatComponent.hpp"
#include "Game/World/Entity/Actor/Player/Components/Render/RenderManager.hpp"


class World;


namespace player {
    struct Stats {
        sf::Vector2f size{};
        float eyeDryness{};
    };

    class Player final : public actor::Actor {
    public:
#pragma region constructors
        explicit Player(World &world, entityID ID, const std::string &name);
#pragma endregion
        // GETTERS
        [[nodiscard]] static std::string getClassName();

        [[nodiscard]] Stats& stats();

        [[nodiscard]] RenderManager &getRenderManager();

    private:
        // CHARACTERISTICS
        Stats stats_{
            {
                static_cast<float>(VideoComponent::GAME_RESOLUTION.y) / 5,
                static_cast<float>(VideoComponent::GAME_RESOLUTION.y) / 5
            }, 0};

        CombatComponent combat_{*this};
        // MANAGERS
        RenderManager renderManager_{*this, render_};

        // UPDATE
        void update() override;
    };
} //player


#endif //BONK_GAME_PLAYER_HPP
