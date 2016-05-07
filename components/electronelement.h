#ifndef ELECTRONELEMENT_H
#define ELECTRONELEMENT_H
#include <string>
#include "electronimage.h"

class ElectronElement
{
public:
    typedef ElectronImage::Axis Axis;

    ElectronElement();
    ElectronElement(const ElectronElement &item);

    ElectronElement &operator=(const ElectronElement &item);

    inline bool isItem() const { return true; } //TODO

    inline void setName(const std::string &name) { m_name = name; }
    inline const std::string &name() const { return m_name; }

    inline void setImage(const ElectronImage &image) { m_image = image; }
    inline const ElectronImage &image() const { return m_image; }

    void rotate(float angle);
    void reflect(Axis axis);

    void setPos(int x, int y);

    inline int posX() const { return m_x; }
    inline int posY() const { return m_y; }

private:
    std::string m_name;
    ElectronImage m_image;
    int m_x, m_y;
};


#endif // ELECTRONELEMENT_H
