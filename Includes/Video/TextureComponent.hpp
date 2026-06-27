#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include "SFML/Graphics/Texture.hpp"

class TextureComponent {
public:
    TextureComponent() = default;

    sf::Texture &load(const std::string &path) {
        const auto it = textures_.find(path);

        if (it == textures_.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile(path)) {
                std::cerr << "Failed to load texture from: " << path << std::endl;
            }
            return textures_.emplace(path, std::move(texture)).first->second;
        }

        return it->second;
    }

    [[nodiscard]] const sf::Texture &get(const std::string &fullPath) const {
        const auto it = textures_.find(fullPath);

        if (it == textures_.end()) {
            // Fallback load on the fly if it wasn't pre-cached
            return const_cast<TextureComponent *>(this)->load(fullPath);
        }

        return it->second;
    }

private:
    std::unordered_map<std::string, sf::Texture> textures_;
};
