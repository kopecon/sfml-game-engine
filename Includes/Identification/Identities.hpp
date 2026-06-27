#pragma once

#include <vector>
#include <atomic>

#include "Identification/Streamable.hpp"
#include "Identification/StrongType.hpp"


namespace identity {
    template<typename Type>
    concept HasCustomName = requires(Type obj)
    {
        { Type::CustomTypeName() } -> std::same_as<std::string_view>;
    };

#define TYPE_NAME(name) static std::string_view CustomTypeName() {return name;}

    template<typename BaseType = void>
    struct TypeCounter {
        template<typename ThisType>
        [[nodiscard]] static std::size_t NextType() noexcept {
            return ++counter_;
        }

    private:
        inline static std::atomic<std::size_t> counter_{0};
        // Atomic is not really necessary since we are not running multiple threads but in the future we might.
        // If not... just size_t is ok.
    };


    template<typename Family>
    struct MemberCounter {
        [[nodiscard]] static std::size_t Next() noexcept {
            return ++counter_;
        }

    private:
        inline static std::atomic<std::size_t> counter_{0};
    };

    template<typename ThisType>
    struct TypeInfo {
        [[nodiscard]] static constexpr ID<void> TypeID() noexcept {
            static const ID<void> ID{TypeCounter<>::NextType<ThisType>()};
            return ID;
        }

        template<typename T = ThisType>
        static constexpr std::string_view TypeName() noexcept {
            if constexpr (HasCustomName<T>) {
                return T::CustomTypeName();
            }
            return MANGLED_NAME(T);
        }

        [[nodiscard]] InstanceID<ThisType> instance_id() const noexcept {
            return InstanceID<ThisType>{this->type_instance_id_};
        }

    protected:
        const std::size_t type_instance_id_{MemberCounter<ThisType>::Next()};
    };


    struct Identifiable {
        virtual ~Identifiable() = default;

        bool operator==(const Identifiable &other) const noexcept {
            return this == &other;
        }

        template<typename T>
        [[nodiscard]] bool is() const noexcept {
            return std::ranges::find(heritage_, TypeInfo<T>::TypeID().value()) != heritage_.end();
        }

        template<typename... T>
        [[nodiscard]] bool is_any() const noexcept {
            return ((is<T>()) or ...);
        }

        template<typename... T>
        [[nodiscard]] bool is_all() const noexcept {
            return ((is<T>()) and ...);
        }

        [[nodiscard]] ID<void> type_id() const noexcept {
            return ID<void>{heritage_.back()};
        }

        [[nodiscard]] ID<void> base_id() const noexcept {
            return ID<void>{heritage_.front()};
        }

        [[nodiscard]] std::vector<ID<void>> shared_ids(const Identifiable &other) const noexcept {
            std::vector<ID<void>> shared{};
            for (const auto &id : other.heritage_) {
                if (std::ranges::find(heritage_, id) != heritage_.end()) {
                    shared.emplace_back(id);
                }
            }
            return shared;
        }

        [[nodiscard]] std::string heritage() const noexcept {
            std::string heritage{};
            for (const auto &id: heritage_) {
               heritage += std::to_string(id) + "; " ;
            }
            return heritage;
        }

    protected:
        Identifiable() {
            heritage_.reserve(5);
        }

        std::vector<std::size_t> heritage_{}; // Stores all IDs in the inheritance chain
    };


    // Virtual inheritance has high performance tax
    template<typename ThisType, typename BaseType = ThisType>
    struct Node : TypeInfo<ThisType>, virtual Identifiable, virtual Streamable {
        [[nodiscard]] static constexpr ID<BaseType> NodeID() noexcept {
            return ID<BaseType>{TypeInfo<ThisType>::TypeID().value()};
        }

        [[nodiscard]] static constexpr ID<void> BaseID() noexcept {
            return ID<BaseType>{TypeInfo<BaseType>::TypeID().value()};
        }

    protected:
        Node() {
            heritage_.emplace_back(Node::NodeID().value());

            stream_ = std::string(TypeInfo<ThisType>::TypeName()) + TypeInfo<ThisType>::instance_id().as_string();
        }
    };
} // identity


template<typename T>
struct TypeTag {
    using Type = T;
};

template<typename T>
inline constexpr TypeTag<T> type{};


namespace id = identity;
