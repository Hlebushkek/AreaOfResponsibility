#include "DislocationPoint.hpp"

DislocationPoint::DislocationPoint(sf::Vector2f position, int weight, std::string name, bool isMainPoint)
    : m_pointWeight(weight), m_pointName(name), m_isMainPoint(isMainPoint)
{
    this->m_position = position;
}