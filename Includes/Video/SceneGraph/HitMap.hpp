#pragma once

#include "Video/SceneGraph/Sprite.hpp"
#include "utils.hpp"


namespace render {
    class HitMap : public Sprite, public id::Node<HitMap>, public utils::Verbose {
        // Custom comparator for sf::IntRect to use it as a map key
        struct IntRectLess {
            bool operator()(const sf::IntRect &a, const sf::IntRect &b) const {
                if (a.position.x != b.position.x) return a.position.x < b.position.x;
                if (a.position.y != b.position.y) return a.position.y < b.position.y;
                if (a.size.x != b.size.x) return a.size.x < b.size.x;
                return a.size.y < b.size.y;
            }
        };

        using ZoneCode = std::uint8_t;

        using PixelTotals = std::unordered_map<ZoneCode, unsigned>;

        struct Region {
            Region(const HitMap &hitMap, const sf::IntRect &rect);

            sf::IntRect rect{}; // Current hit map texture rectangle
            sf::FloatRect localBounds{}; // Rectangle bounding nonempty pixels
            PixelTotals pixelTotals{};

        private:
            void init(const HitMap &hitMap);
        };

        using Regions = std::map<sf::IntRect, Region, IntRectLess>;

        static constexpr size_t MaxPossibleCodes = std::numeric_limits<ZoneCode>::max() + 1;
        static constexpr ZoneCode ExpectedNumOfCodes = 10; // Using this instead of max for space-saving.

    public:
        struct Zone {
            ZoneCode code{0};
            sf::Color color{};
        };

        using Zones = std::initializer_list<Zone>;

        static constexpr Zones DefaultColorCodes{
            {0, sf::Color::Transparent}, // empty
            {1, sf::Color::Red},
            {2, sf::Color::Green},
            {3, sf::Color::Blue}
        };

        struct Overlap {
            using OverlapCount = std::array<float, ExpectedNumOfCodes>;
            OverlapCount thisOverlap{};
            OverlapCount otherOverlap{};

            void normalize(const PixelTotals &thisTotals, const PixelTotals &otherTotals) noexcept;

        private:
            static void normalizeZone(OverlapCount &target, const PixelTotals &totals) noexcept;
        };

        explicit HitMap(const sf::Texture &texture, const Sprite &guide, Zones codes = DefaultColorCodes);

        const Region &setRegion(sf::IntRect rect) noexcept;

        [[nodiscard]] ZoneCode get(sf::Vector2u pixel) const noexcept;

        [[nodiscard]] sf::FloatRect getHitMapBounds() const noexcept;

        [[nodiscard]] Overlap getOverlap(const HitMap &other) const noexcept;

        void update() noexcept;

    private:
        std::vector<ZoneCode> pixelCodes_; // 1D representation of the 2D hit map

        const Sprite &guide_; // Visible sprite equivalent of the hit map
        Regions regions_; // Selected hit map regions (matching the guide's texture rectangles)
        Region *pCurrentRegion_{nullptr};
        unsigned width_{};
        unsigned height_{};

        [[nodiscard]] static constexpr uint32_t packColor(const sf::Color &c) noexcept;
    };
} // render
