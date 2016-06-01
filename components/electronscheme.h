#ifndef ELECTRONSCHEME_H
#define ELECTRONSCHEME_H
#include "components/electronelement.h"
#include "components/electronwire.h"
#include "libs/containers/graph.h"

class ElectronScheme
{
public:
    ElectronScheme();

    ElectronElement *addItem(const ElectronElement &item);
    void deleteItem(const ElectronElement &item);
    ElectronWire *addWire(const ElectronWire &wire, const ElectronElement &from, const ElectronElement &to);
    void deleteWire(const ElectronWire &wire);

    ElectronWire *wireAt(size_t i) const;
    ElectronElement *chipAt(size_t i) const;

    void newScheme();
    void saveToFile(const std::string &filename);
    bool loadFromFile(const std::string &filename);

    size_t size() const;
    size_t wsize() const;
    size_t csize() const;

private:
    typedef Graph<ElectronElement, ElectronWire> _Graph;
    _Graph m_scheme;
};

#endif // ELECTRONSCHEME_H
