#ifndef ELECTRONELEMENT_H
#define ELECTRONELEMENT_H
#include <string>
#include "electroncontact.h"
#include "electronimage.h"

class ElectronElement
{
public:
    typedef ElectronImage::Axis Axis;

    ElectronElement();
    ElectronElement(const ElectronElement &item);

    ElectronElement &operator=(const ElectronElement &item);

    ElectronElement(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end);

    inline bool isItem() const { return true; } //TODO

    inline void setName(const std::string &name) { m_name = name; }
    inline const std::string &name() const { return m_name; }

    inline void setImage(const ElectronImage &image) { m_image = image; }
    inline const ElectronImage &image() const { return m_image; }

    /*inline void setContact(const ElectronContact &contact) { m_contact = contact; }
    inline const ElectronContact &contact() const { return m_contact; }*/

    void rotate(float angle);
    void reflect(Axis axis);

    void setPos(int x, int y);

    inline int posX() const { return m_x; }
    inline int posY() const { return m_y; }

    std::string toString() const;

private:
    std::string m_name;
    ElectronImage m_image;
    //ElectronContact m_contact;
    int m_x, m_y;

    friend bool operator==(const ElectronElement& left, const ElectronElement& right);
};

bool operator==(const ElectronElement& left, const ElectronElement& right);


#endif // ELECTRONELEMENT_H
