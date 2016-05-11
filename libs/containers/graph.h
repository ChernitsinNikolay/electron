#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template <typename Vertex, typename Edge>
class Graph
{
public:
    Graph();
    virtual ~Graph();

    inline void add(const Vertex &vertex);
    inline void remove(const Vertex &vertex);
    inline void removeAt(std::size_t i);
    inline void add(const Edge &edge, std::size_t from, std::size_t to);
    inline void remove(std::size_t from, std::size_t to);

    inline std::size_t size() const;
    inline Vertex *vertexAt(std::size_t i) const;
    inline std::size_t indexOf(const Vertex &vertex) const;
    inline std::size_t edgesAt(const Vertex &vertex) const;
    inline std::size_t edgesAt(std::size_t i) const;

    inline Edge *edge(const Vertex &vertex, std::size_t n) const;
    inline Edge *edge(std::size_t vi, std::size_t ei) const;
    inline std::size_t indexOfEdgeFrom(const Edge &edge) const;
    inline std::size_t indexOfEdgeTo(const Edge &edge) const;
    inline Vertex *vertexAtEdgeFrom(const Edge &edge) const;
    inline Vertex *vertexAtEdgeTo(const Edge &edge) const;

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
    for(typename std::vector<VertexCommunication*>::iterator iter = v.begin(); iter != v.end(); iter++)
        delete (*iter);
    for(typename std::vector<EdgeCommunication*>::iterator iter = e.begin(); iter != e.end(); iter++)
        delete (*iter);
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
    //TODO
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::removeAt(std::size_t i)
{
    //TODO
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::add(const Edge &edge, std::size_t from, std::size_t to)
{
    //TODO
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::remove(std::size_t from, std::size_t to)
{
    //TODO
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::size() const
{
    return v.size();
}

template <typename Vertex, typename Edge>
Vertex *Graph<Vertex, Edge>::vertexAt(std::size_t i) const
{
    return v[i]->vertex;
}

template <typename Vertex, typename Edge>
std::size_t Graph<Vertex, Edge>::indexOf(const Vertex &vertex) const
{
    //TODO
}

template <typename Vertex, typename Edge>
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
