#ifndef PERSIAN_SILVER_ASSET_HPP
#define PERSIAN_SILVER_ASSET_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "resource.hpp"

namespace silver
{

class Asset
{
public:
    Asset(Asset const&) = delete;
    Asset(Asset&&) = delete;
    Asset& operator=(Asset const&) = delete;
    Asset& operator=(Asset&&) = delete;

    static Asset& get();

    static sf::Texture const& getTexture(std::string const& type);
    static sf::Font& getFont();

private:
    Asset() = default;
    ~Asset() = default;

    static constexpr char const* texturePath{"assets/"};

    std::unordered_map<std::string, sf::Texture> textures;
};

}

#endif