#include "electronimage.h"

Basic::Point::Point()
{
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

void Basic::Rectangle::reflect(Axis axis)
{
}

void Basic::Rectangle::rotate(float angle)
{
}

Basic::Arc::Arc()
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

void Basic::Line::reflect(Axis axis)
{
}

void Basic::Line::rotate(float angle)
{
}

Basic::Arrow::Arrow()
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

void Basic::String::reflect(Axis axis)
{
}

void Basic::String::rotate(float angle)
{
}

Basic::Join::Join()
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
    std::copy(item.m_rects.begin(), item.m_rects.end(), m_rects.begin());
    std::copy(item.m_arcs.begin(), item.m_arcs.end(), m_arcs.begin());
    std::copy(item.m_lines.begin(), item.m_lines.end(), m_lines.begin());
    std::copy(item.m_arrows.begin(), item.m_arrows.end(), m_arrows.begin());
    std::copy(item.m_strings.begin(), item.m_strings.end(), m_strings.begin());
    std::copy(item.m_joins.begin(), item.m_joins.end(), m_joins.begin());
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
