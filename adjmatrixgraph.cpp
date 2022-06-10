#include "./inc/adjmatrixgraph.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(const Graph G){

    Graph copyG(G);
    int size = copyG.NumberVertices();
    AdjacencyMatrix.resize(size, std::vector<std::shared_ptr<Edge>>(size,NULL));
    std::cout <<"rozmiar: " << size << std::endl;
    Dequeue<std::shared_ptr<Vertex>> tmp_vertices = copyG.Vertices();
    AdjacencyMatrixVertex tmp_adjmatvertex;
    int i = 0;

    while(!tmp_vertices.IsEmpty()){
        tmp_adjmatvertex = AdjacencyMatrixVertex(*tmp_vertices.RemoveFirst());
        tmp_adjmatvertex.SetIndex(i);
        Vertices().InsertEnd(std::make_shared<Vertex>(tmp_adjmatvertex));
        i++;
    }

    std::cout << "i = " << i << std::endl;

    Dequeue<std::shared_ptr<Edge>> tmp_edges = copyG.Edges();
    std::shared_ptr<Edge> tmp_edge;
    int x;
    int y;
    while(!tmp_edges.IsEmpty()){

        tmp_edge = tmp_edges.RemoveFirst();
        x = tmp_edge->GetStart().GetIndex();
        y = tmp_edge->GetEnd().GetIndex();
        Edges().InsertEnd(tmp_edge);
        AdjacencyMatrix[x][y] = tmp_edge;
    }

}

std::ostream &operator << (std::ostream &out, AdjacencyMatrixGraph const &graph){

    out << "Macierz sasiedztwa: " << std::endl;

    int size = graph.NumberVertices();
    std::cout << size << std::endl;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            out << i << ", " << j << std::endl;
            out << *graph.AdjacencyMatrix[i][j] << std::endl;
        }
    }
    return out;
}