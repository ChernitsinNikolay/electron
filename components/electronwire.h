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

    ElectronWire(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end);

    iterator begin();
    iterator end();

    void addPoint(const Basic::Point &point);

    void setPos(const Basic::Point &point);
    const Basic::Point &pos() const;

    std::string toString() const;

private:
    Points m_points;
    Basic::Point m_pos;

    bool parsePoints(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end);

    friend bool operator==(const ElectronWire& left, const ElectronWire& right);
};

#endif // ELECTRONWIRE_H
