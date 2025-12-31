//
// Created by Andrew on 01/12/2025.
//

#include "../../../Includes/Entity/Scenery/Scenery.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


namespace scenery {

#pragma region constructors
    Scenery::Scenery(World &world, const entityID ID) :
        Entity(world, ID)
    {}

    Scenery::Scenery(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name))
    {}
#pragma endregion

    void Scenery::setCamera() {
        pCamera = &game.video.camera;
    }

    sf::Shape * Scenery::getShape() {
        return &shape;
    }

    void Scenery::loop() {
        // FIXME: There is sometimes space between border and ground edge when looping.
        if (pCamera == nullptr) setCamera();
        else {
            const auto cameraCenter = pCamera->view.getCenter();
            const auto cameraWidth = pCamera->view.getSize().x;

            const auto cameraRBorder = cameraCenter.x + cameraWidth / 2.f;
            const auto cameraLBorder = cameraCenter.x - cameraWidth / 2.f;

            for (const auto &pShape : render.getShapes()) {
                const float shapeWidth = pShape->getLocalBounds().size.x;
                // If camera is viewing outside of background
                if (cameraRBorder > position.x + shapeWidth/2.f) {
                    position = {
                        cameraRBorder-cameraWidth/2.f,
                        position.y};
                }
                else if (cameraLBorder < position.x - shapeWidth/2.f) {
                    position = {
                        cameraLBorder+cameraWidth/2.f,
                        position.y};
                }
            }
        }
    }

    void Scenery::initShapeSize() {
        shape.setSize(static_cast<sf::Vector2f>(pTexture->getSize()));
    }

    void Scenery::init() {
        Entity::init();
    }

    void Scenery::update() {
        loop();
        render.update();
    }
}
