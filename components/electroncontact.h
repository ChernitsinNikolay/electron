#ifndef ELECTRONCONTACT_H
#define ELECTRONCONTACT_H
#include <vector>
#include <string>

class ElectronContactItem
{
public:
    ElectronContactItem();

private:
    bool m_connected;
    float m_x, m_y;
};

class ElectronContact
{
public:
    typedef std::vector<std::string>::iterator vsit;
    typedef std::vector<ElectronContactItem*> vcontact;

    ElectronContact();
    virtual ~ElectronContact();

    bool parse(const vsit &begin, const vsit &end);

    ElectronContact &operator=(const ElectronContact &item);

private:
    vcontact m_contacts;
};

#endif // ELECTRONCONTACT_H
