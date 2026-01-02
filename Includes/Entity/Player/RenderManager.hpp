//
// Created by Andrew on 02/01/2026.
//

#ifndef BONK_GAME_RENDER_MANAGER_HPP
#define BONK_GAME_RENDER_MANAGER_HPP


namespace player {
    class Player;

    class RenderManager {
        Player &player;

    public:
        explicit RenderManager(Player &player);
    };
} // player

#endif //BONK_GAME_RENDER_MANAGER_HPP