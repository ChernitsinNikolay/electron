#ifndef ELECTRONWIRE_H
#define ELECTRONWIRE_H
#include <vector>
#include "electronimage.h"

class ElectronWire
{
public:
    typedef std::vector<Basic::Point> Points;
    typedef Points::iterator iterator;

    ElectronWire();
    ElectronWire(const ElectronWire &wire);

    iterator begin();
    iterator end();

    void addPoint(const Basic::Point &point);

    void setPos(const Basic::Point &point);
    const Basic::Point &pos() const;

private:
    Points m_points;
    Basic::Point m_pos;

    friend bool operator==(const ElectronWire& left, const ElectronWire& right);
};

#endif // ELECTRONWIRE_H
