#ifndef ELECTRON_H
#define ELECTRON_H
#include "electronelement.h"
#include "libs/containers/tree.h"

typedef ElectronElement ElectronItem;
typedef Tree<ElectronItem> ElectronTree;

class Electron
{
public:
    Electron();

    inline ElectronTree *tree() const { return m_tree; }

private:
    bool xmlParse();

    ElectronTree *m_tree;
};

#endif // ELECTRON_H
