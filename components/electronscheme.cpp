#include "electronscheme.h"
#include <fstream>
#include <iostream>
#include <QFile>

#define BUF_SIZE 1024

ElectronScheme::ElectronScheme()
{

}

ElectronElement *ElectronScheme::addItem(const ElectronElement &item)
{
    m_scheme.add(item);
    return m_scheme.vertexAt(m_scheme.size() - 1);
}

void ElectronScheme::deleteItem(const ElectronElement &item)
{
    m_scheme.remove(item);
}

ElectronWire *ElectronScheme::addWire(const ElectronWire &wire, const ElectronElement &from, const ElectronElement &to)
{
    m_scheme.add(wire, m_scheme.indexOf(from), m_scheme.indexOf(to));
    return m_scheme.edgeAt(m_scheme.esize() - 1);
}

void ElectronScheme::deleteWire(const ElectronWire &wire)
{
    m_scheme.remove(wire);
}

ElectronWire *ElectronScheme::wireAt(size_t i) const
{
    return m_scheme.edgeAt(i);
}

ElectronElement *ElectronScheme::chipAt(size_t i) const
{
    return m_scheme.vertexAt(i);
}

void ElectronScheme::newScheme()
{
    m_scheme.clear();
}

void ElectronScheme::saveToFile(const std::string &filename)
{
    std::cout<<"save to "<<filename<<std::endl;
    QFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
    file.write("<scheme>");
    file.write("<vertexs>");
    for(size_t i = 0; i < m_scheme.size(); i++) {
        file.write(m_scheme.vertexAt(i)->toString().c_str());
    }
    file.write("</vertexs>");
    file.write("<edges>");
    for(size_t i = 0; i < m_scheme.esize(); i++) {
        file.write("<connect>");
        file.write("<connected>");
        file.write(std::to_string(m_scheme.vertexIndexFromEdgeIndex(i)).c_str());
        file.write(";");
        file.write(std::to_string(m_scheme.vertexIndexToEdgeIndex(i)).c_str());
        file.write("</connected>");
        file.write(m_scheme.edgeAt(i)->toString().c_str());
        file.write("</connect>");
    }
    file.write("</edges>");
    file.write("</scheme>");
    file.close();
}

bool ElectronScheme::loadFromFile(const std::string &filename)
{
    m_scheme.clear();
    std::cout<<"lod from "<<filename<<std::endl;

    std::ifstream db(filename);
    if(!db.is_open())
        return false;

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
    int st = 0;
    std::size_t from, to, sz;
    ElectronWire ew;
    for(std::vector<std::string>::iterator iter = vlex.begin(); iter != vlex.end(); iter++) {
        switch(st) {
        case 0:     //Схема
            if((std::string(*iter)).compare(0, 9, "<scheme>") == 0)
                st = 1;
            break;

        case 1:     //Элементы
            if((std::string(*iter)).compare(0, 9, "<vertexs>") == 0)
                st = 2;
            else if((std::string(*iter)).compare(0, 7, "<edges>") == 0)
                st = 3;
            else if((std::string(*iter)).compare(0, 9, "</scheme>") == 0)
                st = 0;
            break;

        case 2:     //Элемент
            if((std::string(*iter)).compare(0, 10, "</vertexs>") == 0)
                st = 1;
            else if((std::string(*iter)).compare(0, 8, "<element") == 0)
                for(std::vector<std::string>::iterator iter2 = iter + 1; iter2 != vlex.end(); iter2++) {
                    if((std::string(*iter2)).compare(0, 10, "</element>") == 0) {
                        m_scheme.add(ElectronElement(iter, iter2 + 1));
                        break;
                    }
                }
            break;

        case 3:     //Провода
            if((std::string(*iter)).compare(0, 8, "</edges>") == 0)
                st = 1;
            else if((std::string(*iter)).compare(0, 9, "<connect>") == 0)
                st = 4;
            break;

        case 4:
            if((std::string(*iter)).compare(0, 10, "</connect>") == 0) {
                st = 3;
                m_scheme.add(ew, from, to);
            } else if((std::string(*iter)).compare(0, 11, "<connected>") == 0) {
                iter++;
                from = std::stoi(*iter, &sz);
                to = std::stoi((*iter).substr(sz + 1), &sz);
                iter++;
            } else if((std::string(*iter)).compare(0, 6, "<wire>") == 0)
                for(std::vector<std::string>::iterator iter2 = iter + 1; iter2 != vlex.end(); iter2++) {
                    if((std::string(*iter2)).compare(0, 7, "</wire>") == 0) {
                        ew = ElectronWire(iter, iter2 + 1);
                        break;
                    }
                }
            break;
        }
    }

    if(st == 0)
        return true;

    return false;
}

size_t ElectronScheme::wsize() const
{
    return m_scheme.esize();
}

size_t ElectronScheme::csize() const
{
    return m_scheme.size();
}
