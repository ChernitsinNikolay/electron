#include "electronscheme.h"

ElectronScheme::ElectronScheme()
{

}

ElectronElement *ElectronScheme::addItem(const ElectronElement &item)
{
    m_scheme.add(item);
    return m_scheme.vertexAt(m_scheme.size() - 1);
}
