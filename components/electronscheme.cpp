#include "electronscheme.h"
#include <iostream>
#include <QFile>

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

    std::size_t temp;
    temp = m_scheme.size();
    file.write((char*)&temp, sizeof(std::size_t));
    for(int i = 0; i < m_scheme.size(); i++) {
        ElectronElement *ee = m_scheme.vertexAt(i);
        temp = ee->name().size();
        file.write((char*)&temp, sizeof(std::size_t));
        file.write(ee->name().c_str(), ee->name().size());
        int itemp = ee->posX();
        file.write((char*)&itemp, sizeof(int));
        itemp = ee->posX();
        file.write((char*)&itemp, sizeof(int));
        const ElectronImage *ei = &ee->image();

        //file.write((char*)ee->rawSize(), sizeof(std::size_t));
        //file.write(ee->raw(), ee->rawSize());
    }
    /*file.write((char*)&m_scheme.esize(), sizeof(std::size_t));
    for(int i = 0; i < m_scheme.size(); i++) {
        ElectronWire *ew = m_scheme.edgeAt(i);
        file.write((char*)ew->rawSize(), sizeof(std::size_t));
        file.write(ew->raw(), ew->rawSize());
        file.write((char*)&m_scheme.vertexIndexFromEdgeIndex(i), sizeof(std::size_t));
        file.write((char*)&m_scheme.vertexIndexToEdgeIndex(i), sizeof(std::size_t));
    }*/
    file.close();
}

bool ElectronScheme::loadFromFile(const std::string &filename)
{
    m_scheme.clear();
    std::cout<<"lod from "<<filename<<std::endl;
    /*QFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::ReadOnly))
        return false;
    std::size_t t, from, to;
    file.read((char*)&t, sizeof(std::size_t));
    char *buf = new char[ElectronElement::rawSize()];
    for(int i = 0; i < t; i++) {
        file.read(buf, ElectronElement::rawSize());
        m_scheme.add(ElectronElement(buf));
    }
    delete[] buf;
    buf = new char[ElectronWire::rawSize()];
    file.read((char*)&t, sizeof(std::size_t));
    for(int i = 0; i < t; i++) {
        file.read(buf, ElectronWire::rawSize());
        file.read((char*)&from, sizeof(std::size_t));
        file.read((char*)&to, sizeof(std::size_t));
        m_scheme.add(ElectronWire(buf), from, to);
    }
    file->close();*/
    return true;
}

size_t ElectronScheme::wsize() const
{
    return m_scheme.esize();
}

size_t ElectronScheme::csize() const
{
    return m_scheme.size();
}
