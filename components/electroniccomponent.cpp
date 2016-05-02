#include "electroniccomponent.h"

ElectronicComponent::ElectronicComponent()
{

}

ElectronicComponent::ElectronicComponent(const ElectronicComponent &ec)
{
    m_name = ec.m_name;
    m_id = ec.m_id;
}

ElectronicComponent::~ElectronicComponent()
{}

void ElectronicComponent::setName(const std::string &name)
{
    m_name = name;
}

void ElectronicComponent::setId(const uint64_t &id)
{
    m_id = id;
}
