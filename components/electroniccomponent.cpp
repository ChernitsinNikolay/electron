#include "electroniccomponent.h"

ElectronicComponent::ElectronicComponent()
{

}

ElectronicComponent::ElectronicComponent(const ElectronicComponent &ec)
{
    m_name = ec.m_name;
}

ElectronicComponent::~ElectronicComponent()
{}

void ElectronicComponent::setName(const std::string &name)
{
    m_name = name;
}
