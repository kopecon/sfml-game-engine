#include "Video/SceneGraph/HitMap.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "logger.hpp"


namespace render {
    HitMap::Region::Region(const HitMap &hitMap, const sf::IntRect &rect) : rect(rect) {
        init(hitMap);
    }

    void HitMap::Region::init(const HitMap &hitMap) {
        // Calculate pixel totals per zone and the local bounds bounding nonempty pixels

        int minX = rect.size.x, maxX = 0;
        int minY = rect.size.y, maxY = 0;
        bool foundAny = false;

        for (int y = 0; y < rect.size.y; ++y) {
            for (int x = 0; x < rect.size.x; ++x) {
                auto texX = static_cast<unsigned>(x + rect.position.x);
                auto texY = static_cast<unsigned>(y + rect.position.y);

                if (texX < hitMap.width_ && texY < hitMap.height_) {
                    const ZoneCode c = hitMap.get({texX, texY});
                    if (c == 0) continue; // Skip "empty" pixels

                    // Update bounds
                    if (x < minX) minX = x;
                    if (x > maxX) maxX = x;
                    if (y < minY) minY = y;
                    if (y > maxY) maxY = y;

                    pixelTotals[c]++;
                    foundAny = true;
                }
            }
        }

        if (foundAny) {
            localBounds = sf::FloatRect{
                {static_cast<float>(minX), static_cast<float>(minY)}, // Position
                {static_cast<float>(maxX - minX + 1), static_cast<float>(maxY - minY + 1)} // Size
                // Adding +1 to include the end pixel in the boundary
            };
        } else {
            localBounds = sf::FloatRect({0, 0}, {0, 0});
        }
    }

    void HitMap::Overlap::normalize(const PixelTotals &thisTotals, const PixelTotals &otherTotals) noexcept {
        normalizeZone(thisOverlap, thisTotals);
        normalizeZone(otherOverlap, otherTotals);
    }

    void HitMap::Overlap::normalizeZone(OverlapCount &target, const PixelTotals &totals) noexcept {
        for (unsigned code = 0; code < target.size(); code++) {
            const auto count = target[code];

            if (count == 0) continue;

            const auto max = static_cast<float>(totals.at(code));
            auto normalized = count / max;
            constexpr float decimal = 100.f;
            normalized = std::round(normalized * decimal) / decimal;
            target[code] = normalized;
        }
    }

    HitMap::HitMap(const sf::Texture &texture, const Sprite &guide, const Zones codes) : Sprite(texture),
        guide_(guide) {
        // This constructor was mainly made by ChatGPT

        const sf::Image img = texture.copyToImage();
        const auto size = img.getSize();

        width_ = size.x;
        height_ = size.y;
        pixelCodes_.resize(width_ * height_, 0);

        // Build lookup table
        std::unordered_map<uint32_t, ZoneCode> lookup;
        for (const auto &[code, color]: codes) {
            lookup[packColor(color)] = code;
        }

        // Scan hit map texture and encode pixel codes into the container
        for (unsigned y = 0; y < height_; ++y) {
            for (unsigned x = 0; x < width_; ++x) {
                sf::Color pixel = img.getPixel({x, y});

                auto it = lookup.find(packColor(pixel));
                if (it != lookup.end()) {
                    const auto code = it->second;
                    const auto location = y * width_ + x;
                    pixelCodes_[location] = code; // container
                }
            }
        }

        setRegion({}); // Initialize with empty region
    }

    const HitMap::Region &HitMap::setRegion(const sf::IntRect rect) noexcept {
        // Check if we already have this region cached
        const auto it = regions_.find(rect);

        if (it != regions_.end()) {
            pCurrentRegion_ = &it->second;
            return it->second;
        }

        // Create new region
        Region region{*this, rect};

        // Cache new region
        auto [insertedIt, success] = regions_.emplace(rect, region);
        sprite_->setTextureRect(insertedIt->second.rect);
        pCurrentRegion_ = &insertedIt->second;
        return insertedIt->second;
    }

    HitMap::ZoneCode HitMap::get(const sf::Vector2u pixel) const noexcept {
        return pixelCodes_[pixel.y * width_ + pixel.x];
    }

    sf::FloatRect HitMap::getHitMapBounds() const noexcept {
        const sf::FloatRect localBounds = pCurrentRegion_->localBounds;
        const sf::FloatRect globalBounds = guide_.getGlobalTransform().transformRect(localBounds);
        return globalBounds;
    }

    HitMap::Overlap HitMap::getOverlap(const HitMap &other) const noexcept {
        // Pipeline designed by Gemini

        // A stands for THIS hit map.
        // B stands for OTHER hit map.
        const auto &[rectA, hitBoxA, zoneTotalPixelsA] = *pCurrentRegion_;
        const auto &[rectB, hitBoxB, zoneTotalPixelsB] = *other.pCurrentRegion_;


        const auto globalTransformA = guide_.getGlobalTransform();
        const auto globalTransformB = other.guide_.getGlobalTransform();

        Overlap overlap{};

        // Scan through the selected region A
        for (int y = 0; y < rectA.size.y; ++y) {
            for (int x = 0; x < rectA.size.x; ++x) {
                const sf::Vector2u pixelOnSpriteA{
                    static_cast<unsigned>(x + rectA.position.x),
                    static_cast<unsigned>(y + rectA.position.y)
                };

                const auto hitCodeA = get(pixelOnSpriteA);
                if (hitCodeA == 0) continue; // Skip "empty" pixels

                // Mapping point in A to point in B ((x, y) + 0.5f to get the CENTER of the pixel)
                const sf::Vector2f pointInA(static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f);
                const sf::Vector2f pointInGlobal = globalTransformA.transformPoint(pointInA);
                const sf::Vector2f pointInB = globalTransformB.getInverse().transformPoint(pointInGlobal);


                const bool pointBIsInTheSelectedRegionB = pointInB.x >= 0 && pointInB.y >= 0
                                                          && pointInB.x < static_cast<float>(rectB.size.x)
                                                          && pointInB.y < static_cast<float>(rectB.size.y);

                // Scan through the selected region B
                if (pointBIsInTheSelectedRegionB) {
                    const sf::Vector2u pixelOnSpriteB{
                        static_cast<unsigned>(pointInB.x) + rectB.position.x,
                        static_cast<unsigned>(pointInB.y) + rectB.position.y
                    };

                    const auto hitCodeB = other.get(pixelOnSpriteB);
                    if (hitCodeB == 0) continue; // Skip "empty" pixels

                    overlap.thisOverlap[hitCodeA]++;
                    overlap.otherOverlap[hitCodeB]++;
                }
            }
        }

        overlap.normalize(zoneTotalPixelsA, zoneTotalPixelsB);

        const auto report = "overlap other: "
                      + std::to_string(overlap.otherOverlap.at(1))
                      + " "
                      + std::to_string(overlap.otherOverlap.at(2))
                      + " "
                      + std::to_string(overlap.otherOverlap.at(3));

        DISP(report, verbose());

        return overlap;
    }

    void HitMap::update() noexcept {
        const auto &guideRect = guide_.getSprite().getTextureRect();
        // Switch regions if the animation frame changed
        if (pCurrentRegion_->rect != guideRect) {
            setRegion(guideRect);
        }
    }

    constexpr uint32_t HitMap::packColor(const sf::Color &c) noexcept {
        // ChatGPT performance shenanigans
        return (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
    }
} // render
