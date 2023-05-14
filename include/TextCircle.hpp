#pragma once

#include <SFML/Graphics.hpp>

class TextCircle : public sf::Drawable, public sf::Transformable
{
public:
    TextCircle(std::string text, float radius = (0.0F), size_t pointCount = 30UL);
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void setPosition(const sf::Vector2f& position);

    void setCircleColor(sf::Color color);
private:
    std::string m_text;
    sf::Font m_font;
    sf::Text m_textObj;

    sf::CircleShape m_circle;
};