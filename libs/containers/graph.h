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
    };

    std::vector<VertexCommunication> v;
    std::vector<EdgeCommunication> e;
};

template <typename Vertex, typename Edge>
Graph<Vertex, Edge>::Graph()
{
    //TODO
}

template <typename Vertex, typename Edge>
void Graph<Vertex, Edge>::add(const Vertex &vertex)
{
    //TODO
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
Vertex *Graph<Vertex, Edge>::vertexAt(std::size_t i) const
{
    return v[i];
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

#endif // GRAPH_H
