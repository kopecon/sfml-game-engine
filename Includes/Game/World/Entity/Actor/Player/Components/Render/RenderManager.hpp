#ifndef BONK_GAME_RENDER_MANAGER_HPP
#define BONK_GAME_RENDER_MANAGER_HPP


namespace player {
    class PlayerSprite;
    class Player;

    class RenderManager {
    public:
        explicit RenderManager(Player &player, Render& render);
        [[nodiscard]] PlayerSprite& getMainSprite() const;

    private:
        //REFERENCES
        Player &player_;
        Render &render_;
        PlayerSprite &mainSprite_;
    };
} // player

#endif //BONK_GAME_RENDER_MANAGER_HPP