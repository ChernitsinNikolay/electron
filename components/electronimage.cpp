#include "electronimage.h"
#include <iostream>

Basic::Point::Point()
{
}

Basic::Point Basic::Point::operator =(const Point &point)
{
    m_x = point.m_x;
    m_y = point.m_y;
    return *this;
}

std::string Basic::Point::parse(std::string token, size_t *idx)
{
    m_x = std::stof(token, idx);
    token = token.substr(*idx + 1);
    m_y = std::stof(token, idx);
    return token.size() == *idx ? "" : token.substr(*idx + 1);
}

void Basic::Point::reflect(Axis axis)
{
}

void Basic::Point::rotate(float angle)
{
}

Basic::Rectangle::Rectangle()
{
}

Basic::Rectangle Basic::Rectangle::operator =(const Rectangle &rect)
{
    pos = rect.pos;
    width = rect.width;
    height = rect.height;
    return *this;
}

std::string Basic::Rectangle::parse(std::string token, size_t *idx)
{
    token = pos.parse(token, idx);
    width = std::stof(token, idx);
    token = token.substr(*idx + 1);
    height = std::stof(token, idx);
    return token.size() == *idx ? "" : token.substr(*idx + 1);
}

void Basic::Rectangle::reflect(Axis axis)
{
}

void Basic::Rectangle::rotate(float angle)
{
}

Basic::Arc::Arc()
{
}

Basic::Arc Basic::Arc::operator =(const Arc &arc)
{
    rect = arc.rect;
    startAngle = arc.startAngle;
    sweepAngle = arc.sweepAngle;
    return *this;
}

std::string Basic::Arc::parse(std::string token, size_t *idx)
{
}

void Basic::Arc::reflect(Axis axis)
{
}

void Basic::Arc::rotate(float angle)
{
}

Basic::Line::Line()
{
}

Basic::Line Basic::Line::operator =(const Line &line)
{
    start = line.start;
    end = line.end;
    return *this;
}

std::string Basic::Line::parse(std::string token, size_t *idx)
{
    token = start.parse(token, idx);
    token = end.parse(token, idx);
    return token;
}

void Basic::Line::reflect(Axis axis)
{
}

void Basic::Line::rotate(float angle)
{
}

Basic::Arrow::Arrow()
{
}

Basic::Arrow Basic::Arrow::operator =(const Arrow &arrow)
{
    line = arrow.line;
    h = arrow.h;
    return *this;
}

std::string Basic::Arrow::parse(std::string token, size_t *idx)
{
}

void Basic::Arrow::reflect(Axis axis)
{
}

void Basic::Arrow::rotate(float angle)
{
}

Basic::String::String()
{
}

Basic::String Basic::String::operator =(const String &string)
{
    point = string.point;
    str = string.str;
    return *this;
}

std::string Basic::String::parse(std::string token, size_t *idx)
{
}

void Basic::String::reflect(Axis axis)
{
}

void Basic::String::rotate(float angle)
{
}

Basic::Join::Join()
{
}

Basic::Join Basic::Join::operator =(const Join &join)
{
    pos = join.pos;
    return *this;
}

std::string Basic::Join::parse(std::string token, size_t *idx)
{
}

void Basic::Join::reflect(Axis axis)
{
}

void Basic::Join::rotate(float angle)
{
}

ElectronImage::ElectronImage()
{
}

ElectronImage &ElectronImage::operator=(const ElectronImage &item)
{
    std::copy(item.m_rects.begin(), item.m_rects.end(), std::back_inserter(m_rects));
    std::copy(item.m_arcs.begin(), item.m_arcs.end(), std::back_inserter(m_arcs));
    std::copy(item.m_lines.begin(), item.m_lines.end(), std::back_inserter(m_lines));
    std::copy(item.m_arrows.begin(), item.m_arrows.end(), std::back_inserter(m_arrows));
    std::copy(item.m_strings.begin(), item.m_strings.end(), std::back_inserter(m_strings));
    std::copy(item.m_joins.begin(), item.m_joins.end(), std::back_inserter(m_joins));
    return *this;
}

void ElectronImage::rotate(float angle)
{
    for(Rectangles::iterator iter = m_rects.begin(); iter != m_rects.end(); iter++)
        (*iter).rotate(angle);
    for(Arcs::iterator iter = m_arcs.begin(); iter != m_arcs.end(); iter++)
        (*iter).rotate(angle);
    for(Lines::iterator iter = m_lines.begin(); iter != m_lines.end(); iter++)
        (*iter).rotate(angle);
    for(Arrows::iterator iter = m_arrows.begin(); iter != m_arrows.end(); iter++)
        (*iter).rotate(angle);
    for(Strings::iterator iter = m_strings.begin(); iter != m_strings.end(); iter++)
        (*iter).rotate(angle);
    for(Joins::iterator iter = m_joins.begin(); iter != m_joins.end(); iter++)
        (*iter).rotate(angle);
}

void ElectronImage::reflect(Axis axis)
{
    for(Rectangles::iterator iter = m_rects.begin(); iter != m_rects.end(); iter++)
        (*iter).reflect(axis);
    for(Arcs::iterator iter = m_arcs.begin(); iter != m_arcs.end(); iter++)
        (*iter).reflect(axis);
    for(Lines::iterator iter = m_lines.begin(); iter != m_lines.end(); iter++)
        (*iter).reflect(axis);
    for(Arrows::iterator iter = m_arrows.begin(); iter != m_arrows.end(); iter++)
        (*iter).reflect(axis);
    for(Strings::iterator iter = m_strings.begin(); iter != m_strings.end(); iter++)
        (*iter).reflect(axis);
    for(Joins::iterator iter = m_joins.begin(); iter != m_joins.end(); iter++)
        (*iter).reflect(axis);
}

bool ElectronImage::parse(const vsit &begin, const vsit &end)
{
    int st = 0;
    Basic::ImageItem *basic = 0;
    size_t sz;
    for(vsit iter = begin; iter != end; iter++) {
        switch(st) {
        case 0:
            if((std::string(*iter)).compare(0, 7, "<image>") == 0)
                st = 1;
            break;

        case 1:
            if((std::string(*iter)).compare(0, 8, "</image>") == 0)
                st = 0;
            else if((std::string(*iter)).compare(0, 11, "<rectangle>") == 0)
                st = 2;
            else if((std::string(*iter)).compare(0, 5, "<arc>") == 0)
                st = 3;
            else if((std::string(*iter)).compare(0, 6, "<line>") == 0)
                st = 4;
            else if((std::string(*iter)).compare(0, 7, "<arrow>") == 0)
                st = 5;
            else if((std::string(*iter)).compare(0, 8, "<string>") == 0)
                st = 6;
            else if((std::string(*iter)).compare(0, 6, "<join>") == 0)
                st = 7;
            break;

        case 2:     //rectangle
            basic = new Basic::Rectangle();
            basic->parse(*iter, &sz);
            m_rects.push_back(*((Basic::Rectangle*)basic));
            delete basic;
            st = 8;
            break;

        case 3:     //arc
            basic = new Basic::Arc();
            basic->parse(*iter, &sz);
            m_arcs.push_back(*((Basic::Arc*)basic));
            delete basic;
            st = 8;
            break;

        case 4:     //line
            basic = new Basic::Line();
            basic->parse(*iter, &sz);
            m_lines.push_back(*((Basic::Line*)basic));
            delete basic;
            st = 8;
            break;

        case 5:     //arrow
            basic = new Basic::Arrow();
            basic->parse(*iter, &sz);
            m_arrows.push_back(*((Basic::Arrow*)basic));
            delete basic;
            st = 8;
            break;

        case 6:     //string
            basic = new Basic::String();
            basic->parse(*iter, &sz);
            m_strings.push_back(*((Basic::String*)basic));
            delete basic;
            st = 8;
            break;

        case 7:     //join
            basic = new Basic::Join();
            basic->parse(*iter, &sz);
            m_joins.push_back(*((Basic::Join*)basic));
            delete basic;
            st = 8;
            break;

        case 8:
            if((std::string(*iter)).compare(0, 12, "</rectangle>") == 0)
                st = 1;
            else if((std::string(*iter)).compare(0, 6, "</arc>") == 0)
                st = 1;
            else if((std::string(*iter)).compare(0, 7, "</line>") == 0)
                st = 1;
            else if((std::string(*iter)).compare(0, 8, "</arrow>") == 0)
                st = 1;
            else if((std::string(*iter)).compare(0, 9, "</string>") == 0)
                st = 1;
            else if((std::string(*iter)).compare(0, 7, "</join>") == 0)
                st = 1;
            else {
                std::cerr<<"PARSE ERROR"<<std::endl;
                return false;
            }
            break;
        }
    }
    /*if((std::string(*begin)).compare(0, 7, "<image>") == 0
            && (std::string(*end)).compare(0, 8, "</image>") == 0) {

    }*/
    return st == 0;
}
