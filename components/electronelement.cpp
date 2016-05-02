#include "electronelement.h"

ElectronElement::ElectronElement()
{

}

ElectronElement &ElectronElement::operator=(const ElectronElement &item)
{
    m_name = item.m_name;
    return *this;
}
