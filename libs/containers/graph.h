#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template <typename Vertex, typename Edge>
class Graph
{
public:
    //typename std::vector<VertexCommunication>::const_iterator const_vertex_iterator;
    //typename std::vector<EdgeCommunication>::const_iterator const_edge_iterator;

    Graph();
    virtual ~Graph();

    inline void add(const Vertex &vertex);
    inline void remove(const Vertex &vertex);
    inline void removeAt(std::size_t i);
    inline void add(const Edge &edge, std::size_t from, std::size_t to);
    //inline void remove(std::size_t from, std::size_t to);
    inline void remove(const Edge &edge);
    inline void removeEdgeAt(std::size_t i);

    inline std::size_t size() const;
    inline std::size_t esize() const;
    inline Vertex *vertexAt(std::size_t i) const;
    inline Edge *edgeAt(std::size_t i) const;
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

    inline std::size_t vertexIndexFromEdgeIndex(std::size_t i) const;
    inline std::size_t vertexIndexToEdgeIndex(std::size_t i) const;

    void clear();

private:
    class VertexCommunication
    {
    public:
        VertexCommunication();
        virtual ~VertexCommunication();

    private:
        std::vector<std::size_t> edgesIndex;
        Vertex *vertex;

        friend class Graph;
    };

    class EdgeCommunication
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

    std::vector<VertexCommunication*> v;
    std::vector<EdgeCommunication*> e;
};

template <typename Vertex, typename Edge>
Graph<Vertex, Edge>::Graph()
{
}

template <typename Vertex, typename Edge>
Graph<Vertex, Edge>::~Graph()
{
    clear();
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::add(const Vertex &vertex)
{
    VertexCommunication *vc = new VertexCommunication();
    vc->vertex = new Vertex(vertex);
    v.push_back(vc);
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::remove(const Vertex &vertex)
{
    removeAt(indexOf(vertex));
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::removeAt(std::size_t i)
{
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

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::add(const Edge &edge, std::size_t from, std::size_t to)
{
    EdgeCommunication *ec = new EdgeCommunication();
    ec->edge = new Edge(edge);
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

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::remove(const Edge &edge)
{
    removeEdgeAt(indexOf(edge));
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::removeEdgeAt(std::size_t i)
{
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

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::size() const
{
    return v.size();
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::esize() const
{
    return e.size();
}

template <typename Vertex, typename Edge>
Vertex *Graph<Vertex, Edge>::vertexAt(std::size_t i) const
{
    return v[i]->vertex;
}

template <typename Vertex, typename Edge>
Edge *Graph<Vertex, Edge>::edgeAt(std::size_t i) const
{
    return e[i]->edge;
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::indexOf(const Vertex &vertex) const
{
    for(typename std::vector<VertexCommunication*>::const_iterator iter = v.begin(); iter != v.end(); iter++)
        if((*(*iter)->vertex) == vertex)
            return std::distance(v.begin(), iter);
    return -1;
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::indexOf(const Edge &edge) const
{
    for(typename std::vector<EdgeCommunication*>::const_iterator iter = e.begin(); iter != e.end(); iter++)
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

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::vertexIndexFromEdgeIndex(std::size_t i) const
{
    return e.at(i)->from;
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::vertexIndexToEdgeIndex(std::size_t i) const
{
    return e.at(i)->to;
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::clear()
{
    for(typename std::vector<VertexCommunication*>::iterator iter = v.begin(); iter != v.end(); iter++)
        delete (*iter);
    for(typename std::vector<EdgeCommunication*>::iterator iter = e.begin(); iter != e.end(); iter++)
        delete (*iter);
    v.clear();
    e.clear();
}

template <typename Vertex, typename Edge>
Graph<Vertex, Edge>::VertexCommunication::VertexCommunication() :
    vertex(0) { }

template <typename Vertex, typename Edge>
Graph<Vertex, Edge>::VertexCommunication::~VertexCommunication()
{ delete vertex; }

template <typename Vertex, typename Edge>
Graph<Vertex, Edge>::EdgeCommunication::EdgeCommunication() :
    edge(0) { }

template <typename Vertex, typename Edge>
Graph<Vertex, Edge>::EdgeCommunication::~EdgeCommunication()
{ delete edge; }

#endif // GRAPH_H
