#pragma once

#include "DrawableModel.hpp"

class DislocationPoint : public DrawableModel
{
public:
    enum class PointType { A, B, Regular };

public:
    DislocationPoint(sf::Vector2f position, int weight = 0, std::string name = "", PointType type = PointType::Regular);
    
    int getIntValue() override { return m_pointWeight; }

    std::string getStringValue() override
    {
        switch (m_pointType)
        {
        case PointType::Regular:
            return std::to_string(m_pointWeight);
        default:
            return m_pointName;
        }
    }

    sf::Color getColor() override
    {
        switch (m_pointType)
        {
        case PointType::A:
            return sf::Color::Magenta;
        case PointType::B:
            return sf::Color::Blue;
        case PointType::Regular:
            return sf::Color::Yellow;
        default:
            return sf::Color::Black;
        }
    }

    PointType getPointType() { return m_pointType; }

private:
    int m_pointWeight = 0;
    std::string m_pointName = "";
    PointType m_pointType = PointType::Regular;
};