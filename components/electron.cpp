#include "electron.h"
#include <fstream>
#include <stack>
#include <iostream>

#define BUF_SIZE 1024

Electron::Electron()
{
    xmlParse();
}

bool Electron::xmlParse()
{
    std::ifstream db("ComponentBase.xml");
    if(!db.is_open()) {
        std::cerr<<"Data file not open"<<std::endl;
        return false;
    }
    char buf[BUF_SIZE];
    std::vector<std::string> vlex;
    std::string lex;
    std::streamsize bytes;
    while(!db.eof()) {
        db.read(buf, BUF_SIZE);
        bytes = db.gcount();
        for(int i = 0; i < bytes; i++) {
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
    std::stack<ElectronTree*> tstack;
    ElectronTree *ttree = &m_tree;
    int st = 0;
    for(std::vector<std::string>::iterator iter = vlex.begin(); iter != vlex.end(); iter++) {
        switch(st) {
        case 0:     //Список элементов
            if((std::string(*iter)).compare(0, 10, "<elements>") == 0)
                st = 1;
            break;

        case 1:     //Элемент
            if((std::string(*iter)).compare(0, 8, "<element") == 0) {
                tstack.push(ttree);
                ttree = new ElectronTree();
                ElectronItem ec;
                std::size_t found = (*iter).find("name=\"") + 6;
                std::size_t efound = (*iter).find("\"", found) - found;
                ec.setName((*iter).substr(found, efound));
                ttree->setValue(ec);
            } else if ((std::string(*iter)).compare(0, 10, "</element>") == 0) {
                ElectronTree *temp = tstack.top();
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

    if(st == 0)
        return true;

    return false;
}

bool Electron::setCurrent(const ElectronItem &item)
{
    if(item.isItem())
        m_current = item;
}
