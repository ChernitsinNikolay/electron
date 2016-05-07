#include "electronelement.h"

ElectronElement::ElectronElement() :
    m_x(0), m_y(0)
{
}

ElectronElement::ElectronElement(const ElectronElement &item)
{
    m_name = item.m_name;
    m_image = item.m_image;
    m_x = item.m_x;
    m_y = item.m_y;
}

ElectronElement &ElectronElement::operator=(const ElectronElement &item)
{
    m_name = item.m_name;
    m_image = item.m_image;
    m_x = item.m_x;
    m_y = item.m_y;
    return *this;
}

void ElectronElement::rotate(float angle)
{
    m_image.rotate(angle);
}

void ElectronElement::reflect(Axis axis)
{
    m_image.reflect(axis);
}

void ElectronElement::setPos(int x, int y)
{
    m_x = x;
    m_y = y;
}


