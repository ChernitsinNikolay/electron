#ifndef ELECTRONELEMENT_H
#define ELECTRONELEMENT_H
#include <string>

class ElectronElement
{
public:
    ElectronElement();

    ElectronElement &operator=(const ElectronElement &item);

    inline bool isItem() const { return true; } //TODO

    inline void setName(const std::string &name) { m_name = name; }
    inline const std::string &name() const { return m_name; }

private:
    std::string m_name;
};


#endif // ELECTRONELEMENT_H
