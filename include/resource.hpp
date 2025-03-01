#ifndef PERSIAN_SILVER_RESOURCE_HPP
#define PERSIAN_SILVER_RESOURCE_HPP

#include <SFML/Graphics.hpp>

namespace silver
{

class Glyph;

enum class ResourceType
{
    Food,
    Gold
};

class Resource
{
public:
    Resource(ResourceType type);

    static Resource* create(ResourceType type);
    void draw() const;
    void setPosition(sf::Vector2f pos);
    void setGlyph(Glyph* newGlyph);
    bool isGlyph(Glyph* newGlyph) const;
    static std::string const& name(ResourceType type);
    void setSize(float width);

protected:
    ResourceType type;
    sf::Sprite sprite;
    Glyph* glyph;
};

class Food : public Resource
{
public:
    Food();
};

class Gold : public Resource
{
public:
    Gold();
};

}

#endif