#ifndef ADJLISTGRAPH_H
#define ADJLISTGRAPH_H

#include "adjlistedge.h"


class AdjacencyListGraph: public Graph{

    private:

        Dequeue<Dequeue<std::shared_ptr<Edge>>> AdjacencyList;

    public:

        AdjacencyListGraph();

        //AdjacencyListGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyListGraph const &graph);

        //Dequeue<Dequeue<AdjacencyListEdge*>> GetAdjacencyList() const {return AdjacencyList;};

        std::shared_ptr<Vertex> InsertVertex(GameState x);

        std::shared_ptr<Edge> InsertEdge(int x, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end);

        Dequeue<std::shared_ptr<Edge>> IncidentEdges(std::shared_ptr<Vertex> V) const;

        Dequeue<std::shared_ptr<Vertex>> AdjacentVertices(std::shared_ptr<Vertex> V) const;

        bool AreAdjacent(std::shared_ptr<Vertex> V1, std::shared_ptr<Vertex> V2) const;

        void RemoveEdge(std::shared_ptr<Edge> E);

};

#endif

