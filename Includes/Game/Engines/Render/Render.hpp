//
// Created by Andrew on 30/12/2025.
//

#ifndef BONK_GAME_RENDER_COMPONENT_HPP
#define BONK_GAME_RENDER_COMPONENT_HPP
#include "Composite.hpp"



namespace entity {
    class Entity;
}


class Render {
protected:
    entity::Entity &entity_;
    std::unique_ptr<Composite> root_{nullptr};

public:
    explicit Render(entity::Entity &entity);

    void setRoot(std::unique_ptr<Composite> composite);

    Composite& getRoot() const;

    void loop() const;

    void update() const;
};


#endif //BONK_GAME_RENDER_COMPONENT_HPP