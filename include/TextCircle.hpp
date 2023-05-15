#pragma once

#include <SFML/Graphics.hpp>

class DrawableModel;

class TextCircle : public sf::Drawable, public sf::Transformable
{
public:
    TextCircle(DrawableModel* model, float radius = (0.0F), size_t pointCount = 30UL);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(const sf::Vector2f& position);
    void setOrigin(const sf::Vector2f& position);

    void setCircleColor(sf::Color color);

    DrawableModel* getModel() { return m_model; }
private:
    DrawableModel* m_model;

    static sf::Font m_font;
    sf::Text m_textObj;
    std::string str;

    sf::CircleShape m_circle;
};