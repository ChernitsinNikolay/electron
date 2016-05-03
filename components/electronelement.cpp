#include "electronelement.h"

ElectronElement::ElectronElement()
{

}

ElectronElement &ElectronElement::operator=(const ElectronElement &item)
{
    m_name = item.m_name;
    m_image = item.m_image;
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
