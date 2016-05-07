#include "qschememodel.h"

QSchemeModel::QSchemeModel(QObject *parent, Electron *electron) :
    QObject(parent), m_electron(electron)
{

}

ElectronItem *QSchemeModel::current() const
{
    return m_electron->current();
}
