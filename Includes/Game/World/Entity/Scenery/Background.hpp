#ifndef BONK_GAME_BACKGROUND_HPP
#define BONK_GAME_BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include "Game/World/Entity/Entity.hpp"


class ParallaxLayer;
class Sprite;

namespace scenery {
    class Background final : public entity::Entity {
    public:
#pragma region constructors
        explicit Background(World &world, entityID ID, std::string name);

        [[nodiscard]] static std::string getClassName();
#pragma endregion

        void update() override;

    private:
        std::vector<ParallaxLayer*> layers_{};
        void buildRender();
        void loop() const;
    };
}

#endif //BONK_GAME_BACKGROUND_HPP
