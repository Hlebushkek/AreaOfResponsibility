#include "DislocationPoint.hpp"

DislocationPoint::DislocationPoint(sf::Vector2f position, int weight, std::string name, PointType type)
    : m_pointWeight(weight), m_pointName(name), m_pointType(type)
{
    this->m_position = position;
}