#pragma once

#include "Engine.hpp"


namespace effect {
    template<typename Derived = void>
    class Effect : public Entity, public id::Node<Derived, entity::Entity> {
    protected:
        using Target = Entity;

    public:
        explicit Effect(const Engine &engine, const float duration = 0) : Entity(engine), time_(engine.time()) {
            timer_.setDeadline(duration);
        }

        void setTarget(const std::weak_ptr<Target> &target) noexcept {
            target_ = target;
        }

        void setDuration(const float duration) noexcept {
            timer_.setDeadline(duration);
        }

        [[nodiscard]] float getDuration() const noexcept {
            return timer_.getDeadline();
        }

        template<typename T>
        friend auto activate(std::unique_ptr<T> effect) noexcept;


        void tick() noexcept {
            timer_.tick(time_.dt());
            if (timer_.reachedDeadline()) {
                deactivate();
            } else {
                whileActive();
            }
        }

        void deactivate() noexcept {
            onEnd();
            markForRemoval(*this);
        }

    protected:
        std::weak_ptr<Target> target_{};
        utils::Timer timer_{utils::VERBOSE};

        virtual void onStart() noexcept {
        }

        virtual void whileActive() noexcept {
        }

        virtual void onEnd() noexcept {
        }

    private:
        const TimeComponent &time_;

        void onUpdate() noexcept override {
            tick();
        }
    };

    template<typename T>
    auto activate(std::unique_ptr<T> effect) noexcept {
        effect->timer_.resetTime();
        effect->onStart();
        return effect->engine.currentScene().add(std::move(effect));
    }
} // effect
