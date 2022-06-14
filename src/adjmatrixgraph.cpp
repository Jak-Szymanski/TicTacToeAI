#include "../inc/adjmatrixgraph.h"

/* AdjacencyMatrixGraph::AdjacencyMatrixGraph(const Graph G){

    Graph copyG(G);
    int size = copyG.NumberVertices();
    AdjacencyMatrix.resize(size, std::vector<std::shared_ptr<Edge>>(size,NULL));
    Dequeue<std::shared_ptr<Vertex>>* tmp_vertices = copyG.Vertices();
    int i = 0;
    //Node<std::shared_ptr<Vertex>>* ptr = tmp_vertices.GetHead();
    std::shared_ptr<AdjacencyMatrixVertex> tmp_adjmatvertex;
    std::shared_ptr<Edge> tmp_edge;



    while(!tmp_vertices->IsEmpty()){
        AdjacencyMatrixVertex tmp_adjmatvertex(*tmp_vertices->RemoveFirst());
        tmp_adjmatvertex.SetIndex(i);
        Dequeue<Edge> tmp_adjedges = copyG.IncidentEdges(std::make_shared<AdjacencyMatrixVertex>(tmp_adjmatvertex));
        while(!tmp_adjedges.IsEmpty()){
            tmp_edge = std::make_shared<Edge>(tmp_adjedges.RemoveFirst());
            tmp_edge->SetStart(std::make_shared<AdjacencyMatrixVertex>(tmp_adjmatvertex));
        }
        std::cout << "indeks: " << tmp_adjmatvertex.GetIndex();
        Vertices()->InsertEnd(std::make_shared<Vertex>(tmp_adjmatvertex));
        i++;
    }

    Dequeue<std::shared_ptr<Edge>>* tmp_edges = copyG.Edges();
    int x;
    int y;
    while(!tmp_edges->IsEmpty()){

        tmp_edge = tmp_edges->RemoveFirst();
    //          tmp_edge->SetStart(std::dynamic_pointer_cast<AdjacencyMatrixVertex>(tmp_edge->GetStart()));
        // tmp_edge->SetEnd(std::dynamic_pointer_cast<AdjacencyMatrixVertex>(tmp_edge->GetEnd())); 
        x = tmp_edge->GetStart()->GetIndex();
        y = tmp_edge->GetEnd()->GetIndex();
        Edges()->InsertEnd(tmp_edge);
        AdjacencyMatrix[x][y] = tmp_edge;
        std::cout << x << " , " << y << std::endl;
        std::cout << *AdjacencyMatrix[x][y];
    }

} */

