#include "electron.h"
#include <fstream>
#include <stack>
#include <iostream>

#define BUF_SIZE 1024

Electron::Electron() :
    m_current(0), m_scheme(new ElectronScheme)
{
    xmlParse();
}

Electron::~Electron()
{
    delete m_scheme;
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
            if(buf[i] == '<') {
                if(!lex.empty()) {
                    vlex.push_back(lex);
                    lex.clear();
                }
                lex += buf[i];
            } else if(buf[i] == '>') {
                lex += buf[i];
                if(!lex.empty()) {
                    vlex.push_back(lex);
                    lex.clear();
                } else {
                    std::cerr<<"SCANER ERROR"<<std::endl;
                }
            } else if(buf[i] != '\n' && buf[i] != '\t'){
                lex += buf[i];
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
            } else if((std::string(*iter)).compare(0, 6, "<image") == 0) {
                for(std::vector<std::string>::iterator iter2 = iter + 1; iter2 != vlex.end(); iter2++) {
                    if((std::string(*iter2)).compare(0, 8, "</image>") == 0) {
                        ElectronImage image;
                        image.parse(iter, iter2 + 1);
                        ttree->value().setImage(image);
                        break;
                    }
                }
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
    if(item.isItem()) {
        delete m_current;
        m_current = new ElectronItem(item);
        return true;
    }
    return false;
}

void Electron::rotateCurrent(float angle)
{
    m_current->rotate(angle);
}

void Electron::reflectCurrent(ElectronAxis axis)
{
    m_current->reflect(axis);
}
