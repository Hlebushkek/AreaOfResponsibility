#include <iostream>
#include "../include/TextCircle.hpp"

TextCircle::TextCircle(std::string text, float radius, size_t pointCount)
    : m_circle(radius, pointCount), m_text(text)
{
    sf::Font font;
    if (!m_font.loadFromFile("Roboto-Light.ttf"))
        std::cout << "Can't load font" << std::endl;
    m_textObj.setFont(m_font);
    m_textObj.setCharacterSize(15);
    m_textObj.setString(m_text);
    m_textObj.setFillColor(sf::Color::Black);
}

void TextCircle::setPosition(const sf::Vector2f& position)
{
    sf::Transformable::setPosition(position);
    // sf::FloatRect textRect = m_textObj.getLocalBounds();
    // m_textObj.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f,
    //                     textRect.top  + textRect.height/2.0f));
    // m_textObj.setPosition(sf::Vector2(m_circle.getRadius(), m_circle.getRadius()));
}

void TextCircle::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    sf::RenderStates modifiedStates = states;

    modifiedStates.transform *= getTransform();

    target.draw(m_circle, modifiedStates);
    target.draw(m_textObj, modifiedStates);
}

void TextCircle::setCircleColor(sf::Color color)
{
    m_circle.setFillColor(color);
}