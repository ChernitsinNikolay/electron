#include "electronelement.h"

bool operator==(const ElectronElement& left, const ElectronElement& right){
    return left.m_name == right.m_name && left.m_x == right.m_x && left.m_y == right.m_y && left.m_image == right.m_image;
}

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

ElectronElement::ElectronElement(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end)
{
    for(std::vector<std::string>::iterator iter = begin; iter != end; iter++) {
        if((std::string(*iter)).compare(0, 8, "<element") == 0) {
            std::size_t found = (*iter).find("name=\"") + 6;
            std::size_t efound = (*iter).find("\"", found) - found;
            m_name = (*iter).substr(found, efound);
        } else if ((std::string(*iter)).compare(0, 10, "</element>") == 0) {
            return;
        } else if((std::string(*iter)).compare(0, 10, "<position>") == 0) {
            std::size_t sz;
            iter++;
            m_x = std::stoi(*iter, &sz);
            m_y = std::stoi((*iter).substr(sz + 1), &sz);
            iter++;
        } else if((std::string(*iter)).compare(0, 6, "<image") == 0) {
            for(std::vector<std::string>::iterator iter2 = iter + 1; iter2 != end; iter2++) {
                if((std::string(*iter2)).compare(0, 8, "</image>") == 0) {
                    ElectronImage image;
                    image.parse(iter, iter2 + 1);
                    m_image = image;
                    break;
                }
            }
        }
    }
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


std::string ElectronElement::toString() const
{
    std::string str;
    str += "<element name=\"" + m_name + "\">";
    str += "<position>";
    str += std::to_string(m_x);
    str += ";";
    str += std::to_string(m_y);
    str += "</position>";
    str += m_image.toString();
    str += "</element>";
    return str;
}

