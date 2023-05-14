#pragma once

#include <SFML/Graphics.hpp>

class TextCircle : public sf::Drawable, public sf::Transformable
{
public:
    TextCircle(float radius = (0.0F), size_t pointCount = 30UL, int int_value = 0, std::string text = "");
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(const sf::Vector2f& position);
    void setOrigin(const sf::Vector2f& position);

    void setCircleColor(sf::Color color);

    const int& getValue() const { return m_int_value; }
    const std::string& getText() const { return m_text; }
private:
    int m_int_value;
    std::string m_text;
    sf::Font m_font;
    sf::Text m_textObj;

    sf::CircleShape m_circle;
};