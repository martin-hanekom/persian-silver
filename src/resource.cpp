#include "resource.hpp"
#include "asset.hpp"
#include "screen.hpp"
#include "tile.hpp"

namespace silver
{

Resource::Resource(ResourceType type)
    : type(type), sprite(Asset::getTexture(Resource::name(type)))
{
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
}

Resource* Resource::create(ResourceType type)
{
    switch (type)
    {
        case ResourceType::Food:
            return new Food();
        case ResourceType::Gold:
            return new Gold();
        default:
            return nullptr;
    }
}

void Resource::draw() const
{
    Screen::draw(sprite);
}

void Resource::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Resource::setGlyph(Glyph* newGlyph)
{
    glyph = newGlyph;
    if (nullptr != glyph)
    {
        sprite.setPosition(glyph->getPosition());
        setSize(glyph->getResourceWidth());
        if (!glyph->isResource(this))
        {
            glyph->setResource(this);
        }
    }
}

bool Resource::isGlyph(Glyph* newGlyph) const
{
    return glyph == newGlyph;
}

std::string const& Resource::name(ResourceType type)
{
    static std::unordered_map<ResourceType, std::string> const resourceMap = {
        {ResourceType::Food, "food"},
        {ResourceType::Gold, "gold"}
    };

    return resourceMap.at(type);
}

void Resource::setSize(float width)
{
    auto newScale = width / sprite.getLocalBounds().size.x;
    sprite.setScale({newScale, newScale});
}

Food::Food() : Resource(ResourceType::Food)
{
}

Gold::Gold() : Resource(ResourceType::Gold)
{
}

}