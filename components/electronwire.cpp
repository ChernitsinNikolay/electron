#include "electronwire.h"

bool operator==(const ElectronWire& left, const ElectronWire& right) {
    return left.m_pos.x() == right.m_pos.x() && left.m_pos.y() == right.m_pos.y()
            && left.m_points.size() == right.m_points.size();
}

ElectronWire::ElectronWire()
{

}

ElectronWire::ElectronWire(const ElectronWire &wire)
{
    std::copy(wire.m_points.begin(), wire.m_points.end(), std::back_inserter(m_points));
    m_pos = wire.m_pos;
}

ElectronWire::iterator ElectronWire::begin()
{
    return m_points.begin();
}

ElectronWire::iterator ElectronWire::end()
{
    return m_points.end();
}

void ElectronWire::addPoint(const Basic::Point &point)
{
    m_points.push_back(point);
}

void ElectronWire::setPos(const Basic::Point &point)
{
    m_pos = point;
}

const Basic::Point &ElectronWire::pos() const
{
    return m_pos;
}
