#include <iostream>
#include "../include/TextCircle.hpp"

TextCircle::TextCircle(float radius, size_t pointCount, int int_value, std::string text)
    : m_circle(radius, pointCount), m_int_value(int_value), m_text(text)
{
    sf::Font font;
    if (!m_font.loadFromFile("Roboto-Light.ttf"))
        std::cout << "Can't load font" << std::endl;
    
    m_textObj.setFont(m_font);
    m_textObj.setCharacterSize(15);
    m_textObj.setFillColor(sf::Color::Black);
    
    if (text.empty())
        m_textObj.setString(std::to_string(int_value));
    else
        m_textObj.setString(m_text);

    m_circle.move(-m_circle.getRadius(), -m_circle.getRadius());
    m_textObj.move(-m_circle.getRadius() / 2., -m_circle.getRadius());
}

void TextCircle::setPosition(const sf::Vector2f& position)
{
    sf::Transformable::setPosition(position);
    // sf::FloatRect textRect = m_textObj.getLocalBounds();
    // m_textObj.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f,
    //                     textRect.top  + textRect.height/2.0f));
    // m_textObj.setPosition(sf::Vector2(m_circle.getRadius(), m_circle.getRadius()));
}

void TextCircle::setOrigin(const sf::Vector2f& position)
{
    sf::Transformable::setOrigin(position);
    // sf::FloatRect textRect = m_textObj.getLocalBounds();
    // m_textObj.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f,
    //                     textRect.top  + textRect.height/2.0f));
    // m_textObj.setPosition(sf::Vector2(m_circle.getRadius(), m_circle.getRadius()));
}

void TextCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_circle, states);
    target.draw(m_textObj, states);
}

void TextCircle::setCircleColor(sf::Color color)
{
    m_circle.setFillColor(color);
}
