#include "electronimage.h"
#include <iostream>

bool operator==(const ElectronImage& left, const ElectronImage& right) {
    return left.m_rects.size() == right.m_rects.size() && left.m_arcs.size() == right.m_arcs.size()
            && left.m_lines.size() == right.m_lines.size() && left.m_arrows.size() == right.m_arrows.size()
            && left.m_strings.size() == right.m_strings.size() && left.m_joins.size() == right.m_joins.size();
}

Basic::Point::Point()
{
}

Basic::Point::Point(float x, float y)
{
    m_x = x;
    m_y = y;
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

std::string Basic::Point::toString() const
{
    std::string str;
    str += "<point>";
    str += std::to_string(m_x);
    str += ";";
    str += std::to_string(-m_y);
    str += "</point>";
    return str;
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

std::string Basic::Rectangle::toString() const
{
    std::string str;
    str += "<rectangle>";
    str += std::to_string(pos.x());
    str += ";";
    str += std::to_string(-pos.y());
    str += ";";
    str += std::to_string(width);
    str += ";";
    str += std::to_string(height);
    str += "</rectangle>";
    return str;
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
    token = rect.parse(token, idx);
    startAngle = std::stof(token, idx);
    token = token.substr(*idx + 1);
    sweepAngle = std::stof(token, idx);
    return token.size() == *idx ? "" : token.substr(*idx + 1);

}

void Basic::Arc::reflect(Axis axis)
{
}

void Basic::Arc::rotate(float angle)
{
}

std::string Basic::Arc::toString() const
{
    std::string str;
    str += "<arc>";
    str += std::to_string(rect.x());
    str += ";";
    str += std::to_string(-rect.y());
    str += ";";
    str += std::to_string(rect.w());
    str += ";";
    str += std::to_string(rect.h());
    str += ";";
    str += std::to_string(startAngle);
    str += ";";
    str += std::to_string(sweepAngle);
    str += "</arc>";
    return str;
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

std::string Basic::Line::toString() const
{
    std::string str;
    str += "<line>";
    str += std::to_string(start.x());
    str += ";";
    str += std::to_string(-start.y());
    str += ";";
    str += std::to_string(end.x());
    str += ";";
    str += std::to_string(-end.y());
    str += "</line>";
    return str;
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
    token = line.parse(token, idx);
    h = std::stof(token, idx);
    return token.size() == *idx ? "" : token.substr(*idx + 1);
}

void Basic::Arrow::reflect(Axis axis)
{
}

void Basic::Arrow::rotate(float angle)
{
}

std::string Basic::Arrow::toString() const
{
    std::string str;
    str += "<arrow>";
    str += std::to_string(line.sx());
    str += ";";
    str += std::to_string(-line.sy());
    str += ";";
    str += std::to_string(line.ex());
    str += ";";
    str += std::to_string(-line.ey());
    str += ";";
    str += std::to_string(h);
    str += "</arrow>";
    return str;
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
     token = point.parse(token, idx);
     std::copy(str.begin(),str.end(),std::back_inserter(str));
     return token;
}

void Basic::String::reflect(Axis axis)
{
}

void Basic::String::rotate(float angle)
{
}

std::string Basic::String::toString() const
{
    std::string str;
    str += "<string>";
    str += std::to_string(point.x());
    str += ";";
    str += std::to_string(-point.y());
    str += ";";
    str += this->str;
    str += "</string>";
    return str;
}

Basic::Join::Join()
{
}

Basic::Join::Join(const Join &join)
{
    pos = join.pos;
}

Basic::Join Basic::Join::operator =(const Join &join)
{
    pos = join.pos;
    return *this;
}

std::string Basic::Join::parse(std::string token, size_t *idx)
{
    token = pos.parse(token, idx);
    return token;

}

void Basic::Join::reflect(Axis axis)
{
}

void Basic::Join::rotate(float angle)
{
}

std::string Basic::Join::toString() const
{
    std::string str;
    str += "<join>";
    str += std::to_string(pos.x());
    str += ";";
    str += std::to_string(-pos.y());
    str += "</join>";
    return str;
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

std::string ElectronImage::toString() const
{
    std::string str;
    str += "<image>";
    for(Rectangles::const_iterator iter = m_rects.begin(); iter != m_rects.end(); iter++)
        str += (*iter).toString();
    for(Arcs::const_iterator iter = m_arcs.begin(); iter != m_arcs.end(); iter++)
        str += (*iter).toString();
    for(Lines::const_iterator iter = m_lines.begin(); iter != m_lines.end(); iter++)
        str += (*iter).toString();
    for(Arrows::const_iterator iter = m_arrows.begin(); iter != m_arrows.end(); iter++)
        str += (*iter).toString();
    for(Strings::const_iterator iter = m_strings.begin(); iter != m_strings.end(); iter++)
        str += (*iter).toString();
    for(Joins::const_iterator iter = m_joins.begin(); iter != m_joins.end(); iter++)
        str += (*iter).toString();
    str += "</image>";
    return str;
}
