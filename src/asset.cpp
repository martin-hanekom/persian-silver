#include "asset.hpp"

namespace silver
{

Asset& Asset::get()
{
    static Asset asset;
    return asset;
}

sf::Texture const& Asset::getTexture(std::string const& type)
{
    auto& textures = get().textures;
    if (textures.find(type) == textures.cend())
    {
        textures[type] = sf::Texture(std::string(texturePath) + "/" + type + ".png");
        auto& texture = textures[type];
        //texture.setSmooth(true);
    }

    return textures[type];
}

sf::Font& Asset::getFont()
{
    static sf::Font font("assets/arial.ttf");
    return font;
}

}