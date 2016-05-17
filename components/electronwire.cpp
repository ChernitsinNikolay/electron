#include "electronwire.h"
#include <iostream>

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

ElectronWire::ElectronWire(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end)
{
    for(std::vector<std::string>::iterator iter = begin; iter != end; iter++) {
        if((std::string(*iter)).compare(0, 6, "<wire>") == 0) {
        } else if ((std::string(*iter)).compare(0, 7, "</wire>") == 0) {
            return;
        } else if((std::string(*iter)).compare(0, 10, "<position>") == 0) {
            std::size_t sz;
            iter++;
            m_pos.parse(*iter, &sz);
            iter++;
        } else if((std::string(*iter)).compare(0, 8, "<points>") == 0) {
            for(std::vector<std::string>::iterator iter2 = iter + 1; iter2 != end; iter2++) {
                if((std::string(*iter2)).compare(0, 9, "</points>") == 0) {
                    parsePoints(iter, iter2 + 1);
                    break;
                }
            }
        }
    }
}

bool ElectronWire::parsePoints(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end)
{
    int st = 0;
    Basic::Point point;
    std::size_t sz;
    for(std::vector<std::string>::iterator iter = begin; iter != end; iter++) {
        switch(st) {
        case 0:
            if((std::string(*iter)).compare(0, 8, "<points>") == 0)
                st = 1;
            break;

        case 1:
            if((std::string(*iter)).compare(0, 9, "</points>") == 0)
                st = 0;
            else if((std::string(*iter)).compare(0, 7, "<point>") == 0)
                st = 2;
            break;

        case 2:
            if((std::string(*iter)).compare(0, 8, "</point>") == 0)
                st = 1;
            else {
                point.parse(*iter, &sz);
                m_points.push_back(point);
            }
            break;
        }
    }
    return st == 0;
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

std::string ElectronWire::toString() const
{
    std::string str;
    str += "<wire>";
    str += "<position>";
    str += std::to_string(m_pos.x());
    str += ";";
    str += std::to_string(-m_pos.y());
    str += "</position>";
    str += "<points>";
    for(Points::const_iterator iter = m_points.begin(); iter != m_points.end(); iter++) {
        str += "<point>";
        str += std::to_string((*iter).x());
        str += ";";
        str += std::to_string(-(*iter).y());
        str += "</point>";
    }
    str += "</points>";
    str += "</wire>";
    return str;
}
