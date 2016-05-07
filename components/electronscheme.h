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

private:
    Graph<ElectronElement, ElectronWire> m_scheme;
};

#endif // ELECTRONSCHEME_H
