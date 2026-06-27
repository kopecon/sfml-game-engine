#ifndef BONK_GAME_ACT_READY_HPP
#define BONK_GAME_ACT_READY_HPP


class InputHandler;


namespace evaluation {
    class Evaluable {
    public:
        virtual ~Evaluable() = default;
        [[nodiscard]] virtual InputBindings &bindings() = 0;
        [[nodiscard]] virtual const InputBindings &bindings() const = 0;
        [[nodiscard]] virtual float getTime() const = 0;
    };
}
#endif //BONK_GAME_ACT_READY_HPP
