#ifndef ELECTRONICCOMPONENT_H
#define ELECTRONICCOMPONENT_H

#include <string>

class ElectronicComponent
{
public:
    explicit ElectronicComponent();
    explicit ElectronicComponent(const ElectronicComponent &ec);
    virtual ~ElectronicComponent();

    void setName(const std::string &name);

    const std::string &getName() const { return m_name; }

private:
    std::string m_name;
};

#endif // ELECTRONICCOMPONENT_H
