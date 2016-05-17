#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "myexception.h"
#include "myallocator.h"

//serial        +
//deserial      +
//iterator      +
//allocator     +
//algoritm
//throw         +

//template <typename Vertex, typename Edge, template <typename> class Alloc = std::allocator>
template <typename Vertex, typename Edge, template <typename> class Alloc = MyAllocator>
class Graph
{
private:
    class VertexCommunication;
    class EdgeCommunication;

public:
    class iterator;
    //class const_iterator;

    Graph();
    virtual ~Graph();

    inline void add(const Vertex &vertex) throw(AllocException);
    inline bool remove(const Vertex &vertex);
    inline void removeAt(std::size_t i) throw(OutOfRangeException);
    inline void add(const Edge &edge, std::size_t from, std::size_t to) throw(AllocException);
    //inline void remove(std::size_t from, std::size_t to);
    inline bool remove(const Edge &edge);
    inline void removeEdgeAt(std::size_t i) throw(OutOfRangeException);

    inline std::size_t size() const;
    inline std::size_t esize() const;
    inline Vertex *vertexAt(std::size_t i) const throw(OutOfRangeException);
    inline Edge *edgeAt(std::size_t i) const throw(OutOfRangeException);
    inline std::size_t indexOf(const Vertex &vertex) const;
    inline std::size_t indexOf(const Edge &edge) const;
    /*inline std::size_t edgesAt(const Vertex &vertex) const;
    inline std::size_t edgesAt(std::size_t i) const;

    inline Edge *edge(const Vertex &vertex, std::size_t n) const;
    inline Edge *edge(std::size_t vi, std::size_t ei) const;
    inline std::size_t indexOfEdgeFrom(const Edge &edge) const;
    inline std::size_t indexOfEdgeTo(const Edge &edge) const;
    inline Vertex *vertexAtEdgeFrom(const Edge &edge) const;
    inline Vertex *vertexAtEdgeTo(const Edge &edge) const;*/

    inline std::size_t vertexIndexFromEdgeIndex(std::size_t i) const throw(OutOfRangeException);
    inline std::size_t vertexIndexToEdgeIndex(std::size_t i) const throw(OutOfRangeException);

    iterator begin();
    //const_iterator begin() const;
    iterator end();
    //const_iterator end() const;

    void clear();

private:
    typedef std::vector<VertexCommunication*, Alloc<VertexCommunication*>> vertex_container;

    vertex_container v;
    std::vector<EdgeCommunication*, Alloc<EdgeCommunication*>> e;

    friend class iterator;
};

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::Graph()
{
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::~Graph()
{
    clear();
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
void Graph<Vertex, Edge, Alloc>::add(const Vertex &vertex) throw(AllocException)
{
    VertexCommunication *vc = 0;
    try {
        vc = new VertexCommunication();
        vc->vertex = new Vertex(vertex);
    } catch(std::exception) {
        delete vc;
        throw AllocException();
    }
    v.push_back(vc);
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
bool Graph<Vertex, Edge, Alloc>::remove(const Vertex &vertex)
{
    std::size_t i = indexOf(vertex);
    if(i < 0)
        return false;
    removeAt(i);
    return true;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
void Graph<Vertex, Edge, Alloc>::removeAt(std::size_t i)  throw(OutOfRangeException)
{
    if(i < 0 || i >= v.size())
        throw OutOfRangeException();
    VertexCommunication *vc = v.at(i);
    while(!vc->edgesIndex.empty())
        removeEdgeAt(vc->edgesIndex.at(0));
    for(std::size_t t = 0; t < e.size(); t++) {
        if(e.at(t)->from > i)
            --e.at(t)->from;
        if(e.at(t)->to > i)
            --e.at(t)->to;
    }
    delete vc;
    v.erase(v.begin() + i);
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
void Graph<Vertex, Edge, Alloc>::add(const Edge &edge, std::size_t from, std::size_t to) throw(AllocException)
{
    EdgeCommunication *ec = 0;
    try {
        ec = new EdgeCommunication();
        ec->edge = new Edge(edge);
    } catch(std::exception) {
        delete ec;
        throw AllocException();
    }
    ec->from = from;
    ec->to = to;
    v.at(from)->edgesIndex.push_back(e.size());
    v.at(to)->edgesIndex.push_back(e.size());
    e.push_back(ec);
}

/*template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::remove(std::size_t from, std::size_t to)
{
    removeEdgeAt(edge(from, to));
}*/

template <typename Vertex, typename Edge, template <typename> class Alloc>
bool Graph<Vertex, Edge, Alloc>::remove(const Edge &edge)
{
    std::size_t i = indexOf(edge);
    if(i < 0)
        return false;
    removeEdgeAt(i);
    return true;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
void Graph<Vertex, Edge, Alloc>::removeEdgeAt(std::size_t i) throw(OutOfRangeException)
{
    if(i < 0 || i >= e.size())
        throw OutOfRangeException();
    EdgeCommunication *ec = e.at(i);
    for(size_t t = 0; t < v.size(); t++) {
        for(std::vector<std::size_t>::iterator iter = v.at(t)->edgesIndex.begin(); iter != v.at(t)->edgesIndex.end(); iter++) {
            if(*iter == i) {
                v.at(t)->edgesIndex.erase(iter);
                iter = v.at(t)->edgesIndex.begin() - 1;
                continue;
            } else if(*iter > i) {
                --(*iter);
            }
        }
    }
    delete ec;
    e.erase(e.begin() + i);
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
std::size_t Graph<Vertex, Edge, Alloc>::size() const
{
    return v.size();
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
std::size_t Graph<Vertex, Edge, Alloc>::esize() const
{
    return e.size();
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
Vertex *Graph<Vertex, Edge, Alloc>::vertexAt(std::size_t i) const throw(OutOfRangeException)
{
    if(i < 0 || i >= v.size())
        throw OutOfRangeException();
    return v[i]->vertex;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
Edge *Graph<Vertex, Edge, Alloc>::edgeAt(std::size_t i) const throw(OutOfRangeException)
{
    if(i < 0 || i >= e.size())
        throw OutOfRangeException();
    return e[i]->edge;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
std::size_t Graph<Vertex, Edge, Alloc>::indexOf(const Vertex &vertex) const
{
    for(typename std::vector<VertexCommunication*, Alloc<VertexCommunication*>>::const_iterator iter = v.begin(); iter != v.end(); iter++)
        if((*(*iter)->vertex) == vertex)
            return std::distance(v.begin(), iter);
    return -1;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
std::size_t Graph<Vertex, Edge, Alloc>::indexOf(const Edge &edge) const
{
    for(typename std::vector<EdgeCommunication*, Alloc<EdgeCommunication*>>::const_iterator iter = e.begin(); iter != e.end(); iter++)
        if((*(*iter)->edge) == edge)
            return iter - e.begin();
    return -1;
}

/*template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::edgesAt(const Vertex &vertex) const
{
    //TODO
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::edgesAt(std::size_t i) const
{
    //TODO
}

template <typename Vertex, typename Edge>
Edge *Graph<Vertex, Edge>::edge(const Vertex &vertex, std::size_t n) const
{
    //TODO
}

template <typename Vertex, typename Edge>
Edge *Graph<Vertex, Edge>::edge(std::size_t vi, std::size_t ei) const
{
    //TODO
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::indexOfEdgeFrom(const Edge &edge) const
{
    //TODO
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::indexOfEdgeTo(const Edge &edge) const
{
    //TODO
}

template <typename Vertex, typename Edge>
Vertex *Graph<Vertex, Edge>::vertexAtEdgeFrom(const Edge &edge) const
{
    //TODO
}

template <typename Vertex, typename Edge>
Vertex *Graph<Vertex, Edge>::vertexAtEdgeTo(const Edge &edge) const
{
    //TODO
}*/

template <typename Vertex, typename Edge, template <typename> class Alloc>
std::size_t Graph<Vertex, Edge, Alloc>::vertexIndexFromEdgeIndex(std::size_t i) const throw(OutOfRangeException)
{
    if(i < 0 || i >= e.size())
        throw OutOfRangeException();
    return e.at(i)->from;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
std::size_t Graph<Vertex, Edge, Alloc>::vertexIndexToEdgeIndex(std::size_t i) const throw(OutOfRangeException)
{
    if(i < 0 || i >= e.size())
        throw OutOfRangeException();
    return e.at(i)->to;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
typename Graph<Vertex, Edge, Alloc>::iterator Graph<Vertex, Edge, Alloc>::begin()
{
    iterator b;
    b.m_iter = v.begin();
    return b;
}

/*template <typename Vertex, typename Edge, template <typename> class Alloc>
typename Graph<Vertex, Edge, Alloc>::const_iterator Graph<Vertex, Edge, Alloc>::begin() const
{
    const_iterator b;
    b.m_iter = v.cbegin();
    return b;
}*/

template <typename Vertex, typename Edge, template <typename> class Alloc>
typename Graph<Vertex, Edge, Alloc>::iterator Graph<Vertex, Edge, Alloc>::end()
{
    iterator b;
    b.m_iter = v.end();
    return b;
}

/*template <typename Vertex, typename Edge, template <typename> class Alloc>
typename Graph<Vertex, Edge, Alloc>::const_iterator Graph<Vertex, Edge, Alloc>::end() const
{
    const_iterator b;
    b.m_iter = v.cend();
    return b;
}*/

template <typename Vertex, typename Edge, template <typename> class Alloc>
void Graph<Vertex, Edge, Alloc>::clear()
{
    for(typename std::vector<VertexCommunication*, Alloc<VertexCommunication*>>::iterator iter = v.begin(); iter != v.end(); iter++)
        delete (*iter);
    for(typename std::vector<EdgeCommunication*, Alloc<EdgeCommunication*>>::iterator iter = e.begin(); iter != e.end(); iter++)
        delete (*iter);
    v.clear();
    e.clear();
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
class Graph<Vertex, Edge, Alloc>::VertexCommunication
{
public:
    VertexCommunication();
    virtual ~VertexCommunication();

private:
    std::vector<std::size_t> edgesIndex;
    Vertex *vertex;

    friend class Graph;
    friend class Graph::iterator;
};

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::VertexCommunication::VertexCommunication() :
    vertex(0) { }

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::VertexCommunication::~VertexCommunication()
{ delete vertex; }


template <typename Vertex, typename Edge, template <typename> class Alloc>
class Graph<Vertex, Edge, Alloc>::EdgeCommunication
{
public:
    EdgeCommunication();
    virtual ~EdgeCommunication();

private:
    std::size_t from;
    std::size_t to;
    Edge *edge;

    friend class Graph;
};

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::EdgeCommunication::EdgeCommunication() :
    edge(0) { }

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::EdgeCommunication::~EdgeCommunication()
{ delete edge; }

template <typename Vertex, typename Edge, template <typename> class Alloc>
class Graph<Vertex, Edge, Alloc>::iterator
{
public:
    iterator();
    iterator(const iterator &iter);

    iterator &operator=(const iterator &iter);
    bool operator!=(const iterator &iter) const;

    iterator &operator++();

    Vertex &operator*() const;

private:
    typename Graph<Vertex, Edge, Alloc>::vertex_container::iterator m_iter;

    friend class Graph;
};

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::iterator::iterator()
{ }

template <typename Vertex, typename Edge, template <typename> class Alloc>
Graph<Vertex, Edge, Alloc>::iterator::iterator(const iterator &iter)
{
    m_iter = iter.m_iter;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
typename Graph<Vertex, Edge, Alloc>::iterator &Graph<Vertex, Edge, Alloc>::iterator::operator=(const iterator &iter)
{
    m_iter = iter.m_iter;
    return *this;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
bool Graph<Vertex, Edge, Alloc>::iterator::operator!=(const iterator &iter) const
{
    return m_iter != iter.m_iter;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
typename Graph<Vertex, Edge, Alloc>::iterator &Graph<Vertex, Edge, Alloc>::iterator::operator++()
{
    ++m_iter;
    return *this;
}

template <typename Vertex, typename Edge, template <typename> class Alloc>
Vertex &Graph<Vertex, Edge, Alloc>::iterator::operator*() const
{
    return *(*m_iter)->vertex;
}

#endif // GRAPH_H
