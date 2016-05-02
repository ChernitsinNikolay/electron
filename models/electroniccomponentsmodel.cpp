#include "electroniccomponentsmodel.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stack>

#define BUFF_SIZE 1024

ElectronicComponentsModel::ElectronicComponentsModel()
{
    fetchAllComponents();
}

void ElectronicComponentsModel::fetchAllComponents()
{
    uint64_t cntr = 0;
    //simple scan file
    std::ifstream db("ComponentBase.xml");
    if(!db.is_open()) {
        std::cerr<<"Data file not open"<<std::endl;
        return;
    }
    char buf[BUFF_SIZE];
    std::vector<std::string> vlex;
    std::string lex;
    while(!db.eof()) {
        db.read(buf, BUFF_SIZE);
        for(int i = 0; i < BUFF_SIZE && buf[i] != '\0'; i++) {
            if(buf[i] == '<' || !lex.empty())
                lex += buf[i];
            if(buf[i] == '>' && !lex.empty()) {
                vlex.push_back(lex);
                lex.clear();
            }
        }
    }
    db.close();
    //simple parse data by file
    //parse(vlex.begin(), vlex.end());
    std::stack<ContainerType*> tstack;
    ContainerType *ttree = &m_elcomps;
    int st = 0;
    for(std::vector<std::string>::iterator iter = vlex.begin(); iter != vlex.end(); iter++) {
        //std::cout<<">> "<<(std::string(*iter))<<std::endl;
        switch(st) {
        case 0:     //Список элементов
            if((std::string(*iter)).compare(0, 10, "<elements>") == 0)
                st = 1;
            break;

        case 1:     //Элемент
            if((std::string(*iter)).compare(0, 8, "<element") == 0) {
                tstack.push(ttree);
                ttree = new ContainerType();
                ItemType ec;
                std::size_t found = (*iter).find("name=\"") + 6;
                std::size_t efound = (*iter).find("\"", found) - found;
                ec.setName((*iter).substr(found, efound));
                ec.setId(++cntr);
                ttree->setValue(ec);
            } else if ((std::string(*iter)).compare(0, 10, "</element>") == 0) {
                ContainerType *temp = tstack.top();
                temp->addChildren(*ttree);
                delete ttree;
                ttree = temp;
                tstack.pop();
            } else if((std::string(*iter)).compare(0, 10, "</elements") == 0) {
                st = 0;
            }
            break;
        }
    }
}

const ElectronicComponentsModel::ContainerType *ElectronicComponentsModel::findById(const uint64_t &id)
{
    return findById(id, &m_elcomps);
}

const ElectronicComponentsModel::ContainerType *ElectronicComponentsModel::findById(const uint64_t &id, const ContainerType *iter)
{
    for(size_t i = 0; i < iter->size(); i++) {
        if((*iter)[i]->value().getId() == id)
            return (*iter)[i];
    }
    for(size_t i = 0; i < iter->size(); i++) {
        const ContainerType *titer = findById(id, (*iter)[i]);
        if(titer)
            return titer;
    }
    return NULL;
}
