#ifndef ELECTRONWIRE_H
#define ELECTRONWIRE_H
#include <vector>
#include "electronimage.h"

class ElectronWire
{
public:
    typedef std::vector<Basic::Point> Points;

    ElectronWire();

private:
    Points m_points;
};

#endif // ELECTRONWIRE_H
