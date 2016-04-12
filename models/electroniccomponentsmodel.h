#ifndef ELECTRONICCOMPONENTSMODEL_H
#define ELECTRONICCOMPONENTSMODEL_H


#include "libs/containers/tree.h"
#include "components/electroniccomponent.h"

class ElectronicComponentsModel
{
public:
    explicit ElectronicComponentsModel();

private:
    void fetchAllComponents();
    //std::vector::iterator parse(const std::vector<std::string>::iterator &start, const std::vector::iterator &end);

protected:
    Tree<ElectronicComponent> m_elcomps;
};

#endif // ELECTRONICCOMPONENTSMODEL_H
