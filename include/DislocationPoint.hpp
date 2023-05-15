#pragma once

#include "DrawableModel.hpp"

class DislocationPoint : public DrawableModel
{
public:
    DislocationPoint(sf::Vector2f position, int weight = 0, std::string name = "", bool isMainPoint = false);
    
    int getIntValue() override { return m_pointWeight; }
    std::string getStringValue() override { return m_isMainPoint ? m_pointName : std::to_string(m_pointWeight); }
    sf::Color getColor() override { return m_isMainPoint ? sf::Color::Red : sf::Color::Yellow; }

    bool isMainPoint() { return m_isMainPoint; }
private:
    int m_pointWeight = 0;
    std::string m_pointName = "";
    bool m_isMainPoint = false;
};