#include <iostream>
#include "TextCircle.hpp"
#include "DrawableModel.hpp"

sf::Font TextCircle::m_font;

TextCircle::TextCircle(DrawableModel* model, float radius, size_t pointCount)
    : m_circle(radius, pointCount)
{
    std::cout << "TextCircle init" << std::endl;
    m_model = model;

    if (m_font.getInfo().family.empty())
        if (!m_font.loadFromFile("../resources/ARCADECLASSIC.TTF"))
            std::cout << "Can't load font" << std::endl;

    m_textObj.setFont(m_font);
    m_textObj.setCharacterSize(20);
    m_textObj.setFillColor(sf::Color::Black);
    m_textObj.setString(m_model->getStringValue());

    sf::FloatRect textBounds = m_textObj.getLocalBounds();
    m_textObj.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);

    m_circle.move(-m_circle.getRadius(), -m_circle.getRadius());

    this->setPosition(m_model->getPosition());
    this->setCircleColor(m_model->getColor());
}

void TextCircle::setPosition(const sf::Vector2f& position)
{
    sf::Transformable::setPosition(position);
}

void TextCircle::setOrigin(const sf::Vector2f& position)
{
    sf::Transformable::setOrigin(position);
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
