#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Game/World/Entity/Actor/Actor.hpp"
#include "Game/World/Entity/Actor/Player/Components/Movement/MovementComponent.hpp"
#include "Game/World/Entity/Actor/Player/Components/Combat/CombatComponent.hpp"
#include "Game/World/Entity/Actor/Player/Components/Render/RenderManager.hpp"


class World;


namespace player {
    class Player final : public actor::Actor {
    public:
#pragma region constructors
        explicit Player(World &world, entityID ID, const std::string &name);
#pragma endregion
        // ACTIONS
        // SETTERS
        void setEyeDryness(float value);

        // GETTERS
        [[nodiscard]] static std::string getClassName();

        [[nodiscard]] sf::Vector2f getCharacterSize() const;

        [[nodiscard]] float getEyeDryness() const;

        [[nodiscard]] MovementComponent &getMovement();

        [[nodiscard]] RenderManager &getRenderManager();

    private:
        // CHARACTERISTICS
        float height_{256.f / 1.5};
        float width_{256.f / 1.5};
        // CONDITIONS
        float eyeDryness_{};

        MovementComponent movement_{*this};
        CombatComponent combat_{*this};
        // MANAGERS
        RenderManager renderManager_{*this, render_};

        // UPDATE
        void update() override;
    };
} //player


#endif //BONK_GAME_PLAYER_HPP
