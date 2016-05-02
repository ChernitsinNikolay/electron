#ifndef ELECTRONICCOMPONENTSMODEL_H
#define ELECTRONICCOMPONENTSMODEL_H


#include "libs/containers/_tree.h"
#include "components/electroniccomponent.h"


class ElectronicComponentsModel
{
public:
    ElectronicComponentsModel();

    typedef ElectronicComponent ItemType;
    typedef Tree<ItemType> ContainerType;

    inline const size_t &size(const uint64_t &id = 0) {
        if(!id)
            return m_elcomps.size();
        const ContainerType *iter = findById(id);
        return iter ? iter->size() : 0;
    }

    inline const uint64_t &id(const uint64_t &parentId, const uint64_t &idx) {
        if(!parentId && idx < m_elcomps.size())
            return m_elcomps[idx]->value().getId();
        const ContainerType *iter = findById(parentId);
        return iter && idx < iter->size() ? (*iter)[idx]->value().getId() : 0;
    }

    inline std::string name(const uint64_t &id) {
        if(!id)
            return "";
        const ContainerType *iter = findById(id);
        return iter ? iter->value().getName() : "";
    }

private:
    void fetchAllComponents();
    const ContainerType *findById(const uint64_t &id);
    const ContainerType *findById(const uint64_t &id, const ContainerType *iter);

    ContainerType m_elcomps;
};

#endif // ELECTRONICCOMPONENTSMODEL_H
