#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Jumping::Jumping(Player &player): PlayerState(player, StateSet::ID::JUMPING) {
    using enum StateSet::ID;
    // Helpers
    // ReSharper disable once CppDFAUnreachableFunctionCall
    auto grounded = [this] {return this->player_.getPhysics().isGrounded();};
    // ReSharper disable once CppDFAUnreachableFunctionCall
    auto previous = [this] {
        return this->player_.getPreviousState().getID();
    };
    // Conditions
    auto walking  = [grounded, previous] {return grounded() && previous() == WALKING;};
    auto running  = [grounded, previous] {return grounded() && previous() == RUNNING;};
    // Edges
    addEdge(std::make_unique<Edge>(running,  RUNNING));
    addEdge(std::make_unique<Edge>(walking,  WALKING));
    addEdge(std::make_unique<Edge>(grounded, IDLE));
    addEdge(std::make_unique<Edge>(ATTACKING));
    // Actions
    addEnterAction([&player]{player.getMovement().jump();});
}
