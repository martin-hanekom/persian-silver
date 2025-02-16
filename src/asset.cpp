#include "asset.hpp"

Asset& Asset::get()
{
    static Asset asset;
    return asset;
}

sf::Texture& Asset::getTexture(std::string const& name)
{
    auto& textures = get().textures;
    if (textures.find(name) == textures.end())
    {
        textures[name] = sf::Texture(std::string(texturePath) + "/" + name + ".png");
        auto& texture = textures[name];
        texture.setSmooth(true);
    }

    return textures[name];
}