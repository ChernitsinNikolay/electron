#ifndef ELECTRONICCOMPONENT_H
#define ELECTRONICCOMPONENT_H

#include <string>

class ElectronicComponent
{
public:
    ElectronicComponent();
    ElectronicComponent(const ElectronicComponent &ec);
    virtual ~ElectronicComponent();

    void setName(const std::string &name);
    void setId(const uint64_t &id);

    const std::string &getName() const { return m_name; }
    const uint64_t &getId() const { return m_id; }

private:
    std::string m_name;
    uint64_t m_id;
};

#endif // ELECTRONICCOMPONENT_H
