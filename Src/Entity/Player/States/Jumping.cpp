#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Jumping::Jumping(Player &player): PlayerState(player, StateSet::ID::JUMPING) {
    using enum StateSet::ID;
    // Helpers
    // ReSharper disable once CppDFAUnreachableFunctionCall (used in conditions)
    auto grounded = [this] {return this->player_.getPhysics().isGrounded();};
    // ReSharper disable once CppDFAUnreachableFunctionCall (used in conditions)
    auto previous = [this] {
        return this->player_.getPreviousState().getID();
    };
    // CONDITIONS
    auto running  = [grounded, previous] {return grounded() && previous() == RUNNING;};
    auto walking  = [grounded, previous] {return grounded() && previous() == WALKING;};
    // EDGES
    makeEdge(attack   , ATTACKING);
    makeEdge(running  , RUNNING  );
    makeEdge(walking  , WALKING  );
    makeEdge(grounded , BRAKING  );
    // ACTIONS
    addEnterAction([&player]{player.getMovement().jump();});
}
