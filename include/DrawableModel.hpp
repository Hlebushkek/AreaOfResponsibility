#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class DrawableModel
{
public:
    virtual int getIntValue() = 0;
    virtual std::string getStringValue() = 0;
    virtual sf::Color getColor() = 0;

    const sf::Vector2f& getPosition() const { return m_position; }
    
protected:
    sf::Vector2f m_position;
};