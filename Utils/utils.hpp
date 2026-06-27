#pragma once

#include <string>
#include <vector>
#include <memory>

#include "logger.hpp"


template<typename T>
struct Token {
    Token() = default;

    // Perfect Forwarding Factory Constructor
    template<typename... Args>
        requires(std::is_constructible_v<T, Args...>)
    explicit Token(Args &&... args)
        : data_(std::make_unique<T>(std::forward<Args>(args)...)) {
    }

    // Force Move-Only Semantics (Standard C++ way)
    Token(const Token &) = delete;

    Token(Token &&) noexcept = default;

    Token &operator=(const Token &) = delete;

    Token &operator=(Token &&) noexcept = default;

    // Pointer ergonomics
    T *operator->() const { return data_.get(); }
    T &operator*() const { return *data_; }
    explicit operator bool() const { return data_ != nullptr; }

    void consume() noexcept { data_.reset(); }

private:
    std::unique_ptr<T> data_{nullptr};
};


namespace utils {
    enum Verbosity { SILENT, VERBOSE };

    class Verbose {
    public:
        Verbose() = default;

        explicit Verbose(const Verbosity verbosity) : verbose_(verbosity) {
        }

        explicit Verbose(std::vector<Verbose *> &&subModules) : subModules_(std::move(subModules)) {
        }

        virtual ~Verbose() = default;

        virtual void setVerbose(const bool value) noexcept {
            verbose_ = value;
            for (const auto &subModule: subModules_) {
                subModule->setVerbose(value);
            }
        }

    protected:
        [[nodiscard]] bool verbose() const noexcept {
            return verbose_;
        }

    private:
        bool verbose_{false};
        std::vector<Verbose *> subModules_{};
    };


    struct StopWatch : Verbose {
        StopWatch() = default;

        explicit StopWatch(Verbosity verbosity);

        void setTime(float time) noexcept;

        [[nodiscard]] float getTime() const noexcept;

        void tick(float dt) noexcept;

        void togglePause() noexcept;

        void pause() noexcept;

        void unpause() noexcept;

        void resetTime() noexcept;

    private:
        bool pause_{false};
        float currentTime_{0.f}; // [s]
    };

    struct Timer final : StopWatch {
        explicit Timer(const float deadline = 0.f)
            : deadline_(deadline) {
        }

        void setDeadline(float deadline) noexcept;

        [[nodiscard]] bool reachedDeadline() const noexcept;

        [[nodiscard]] float getDeadline() const noexcept;

    private:
        float deadline_{0.f}; // [s] If deadline = 0 -> treat as "inf".
    };


    inline StopWatch::StopWatch(const Verbosity verbosity) : Verbose(verbosity) {
    }

    inline void StopWatch::setTime(const float time) noexcept {
        currentTime_ = time;
    }

    inline float StopWatch::getTime() const noexcept {
        return currentTime_;
    }

    inline void StopWatch::togglePause() noexcept {
        pause_ = !pause_;
    }

    inline void StopWatch::pause() noexcept {
        pause_ = true;
    }

    inline void StopWatch::unpause() noexcept {
        pause_ = false;
    }

    inline void StopWatch::resetTime() noexcept { currentTime_ = 0.f; }

    inline void StopWatch::tick(const float dt) noexcept {
        if (!pause_) {
            DISP(std::to_string(currentTime_), verbose());
            currentTime_ += dt;
        }
    }

    inline void Timer::setDeadline(const float deadline) noexcept {
        deadline_ = deadline;
    }

    inline bool Timer::reachedDeadline() const noexcept {
        if (static_cast<bool>(deadline_)) {
            return getTime() >= deadline_;
        }
        return false;
    }

    inline float Timer::getDeadline() const noexcept {
        return deadline_;
    }

    template<typename T>
    inline constexpr bool always_false_v = false;
}
