#ifndef BONK_GAME_GROUND_HPP
#define BONK_GAME_GROUND_HPP

#include "Game/World/Entity/Entity.hpp"


class ParallaxLayer;

namespace scenery {
    class Ground final : public entity::Entity {
    public:
#pragma region constructors
        explicit Ground(World &world, entityID ID, std::string name);

        [[nodiscard]] static std::string getClassName();
#pragma endregion

        sf::Color color = sf::Color({40, 30, 100});

        void update() override;

    private:
        std::vector<ParallaxLayer*> layers_{};
        void buildRender();
        void loop() const;
    };
}


#endif //BONK_GAME_GROUND_HPP
