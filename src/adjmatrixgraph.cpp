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

std::shared_ptr<Vertex> AdjacencyMatrixGraph::InsertVertex(GameState x){

    auto V = std::make_shared<AdjacencyMatrixVertex>(x);

    int new_size = NumberVertices() + 1;
    V->SetIndex(new_size-1);
    AdjacencyMatrix.resize(new_size, std::vector<std::shared_ptr<Edge>>(new_size, NULL));
    for (auto &row: AdjacencyMatrix) row.resize(new_size, NULL);
    Vertices()->InsertFront(V);
    Vertices()->GetHead()->GetElem()->SetPos(Vertices()->GetHead());
    return V;

}

std::shared_ptr<Edge> AdjacencyMatrixGraph::InsertEdge(int x, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end){
    
    auto E = std::make_shared<Edge>(x,start,end);

    Edges()->InsertFront(E);
    Edges()->GetHead()->GetElem()->SetPos(Edges()->GetHead());
    int i = start->GetIndex();
    int j = end->GetIndex();
    AdjacencyMatrix[i][j] = E;
    // AdjacencyMatrix[j][i] = E;
    return E;
}

Dequeue<std::shared_ptr<Edge>> AdjacencyMatrixGraph::StartingEdges(std::shared_ptr<Vertex> V) const {

    int j = V->GetIndex();
    Dequeue<std::shared_ptr<Edge>> tmp_incident;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[j][i]);
    }
    return tmp_incident;
}

 Dequeue<std::shared_ptr<Edge>> AdjacencyMatrixGraph::IncidentEdges(std::shared_ptr<Vertex> V) const {

    int j = V->GetIndex();
    Dequeue<std::shared_ptr<Edge>> tmp_incident;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[j][i]);
        if(AdjacencyMatrix[i][j] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[i][j]);
    }
    return tmp_incident; 
 }


Dequeue<std::shared_ptr<Vertex>> AdjacencyMatrixGraph::AdjacentVertices(std::shared_ptr<Vertex> V) const {

    int j = V->GetIndex();
    Dequeue<std::shared_ptr<Vertex>> tmp_adjacent;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_adjacent.InsertEnd(AdjacencyMatrix[j][i]->GetEnd());
    }
    return tmp_adjacent;

}

bool AdjacencyMatrixGraph::AreAdjacent(std::shared_ptr<Vertex> V1, std::shared_ptr<Vertex> V2) const{

    return AdjacencyMatrix[V1->GetIndex()][V2->GetIndex()] != NULL;
}

void AdjacencyMatrixGraph::RemoveEdge(std::shared_ptr<Edge> E){

    AdjacencyMatrix[E->GetStart()->GetIndex()][E->GetEnd()->GetIndex()] = NULL;

    Node<std::shared_ptr<Edge>>* ptr = E->GetPos();

    if(ptr == Edges()->GetHead()){
        Edges()->RemoveFirst();
        return;
    } 
    if(ptr == Edges()->GetTail()){
        Edges()->RemoveLast();
        return;
    }

    ptr->GetPrev()->SetNext(ptr->GetNext());
    ptr->GetNext()->SetPrev(ptr->GetPrev());
    delete ptr;
}

void AdjacencyMatrixGraph::RemoveVertex(std::shared_ptr<Vertex> V){

   Node<std::shared_ptr<Edge>>* ptr_e = IncidentEdges(V).GetHead();

    while(ptr_e != NULL){
        RemoveEdge(ptr_e->GetElem());
        ptr_e = ptr_e->GetNext();
    }

    int index = V->GetIndex();
    AdjacencyMatrix.erase(AdjacencyMatrix.begin() + index);

    for(int i=0; i<AdjacencyMatrix.size(); i++){
        if(AdjacencyMatrix[i].size() > index){
            AdjacencyMatrix[i].erase(AdjacencyMatrix[i].begin() + index);
        }
    }


    Node<std::shared_ptr<Vertex>>* ptr_v = V->GetPos();

    if(ptr_v->GetNext() == NULL){
        Vertices()->SetTail(ptr_v->GetPrev());
    } else{
        ptr_v->GetNext()->SetPrev(ptr_v->GetPrev());   
    }
    if(ptr_v->GetPrev() == NULL){
        Vertices()->SetHead(ptr_v->GetNext());
    } else {
        ptr_v->GetPrev()->SetNext(ptr_v->GetNext());
    }

    Node<std::shared_ptr<Vertex>>* next = ptr_v->GetNext();

    while(next != NULL){
        next->GetElem()->SetIndex(next->GetElem()->GetIndex() - 1);
        next = next->GetNext();
    }
    delete ptr_v;
}

std::ostream &operator << (std::ostream &out, AdjacencyMatrixGraph const &graph){

    out << "Macierz sasiedztwa: " << std::endl;

    int size = graph.NumberVertices();

    if (size == 0){
        out << "Macierz jest pusta" << std::endl;
        return out;
    }
    std::cout << "rozmiar " << size << std::endl;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            out << i << ", " << j << std::endl;
            if (graph.AdjacencyMatrix[i][j] == NULL){
                out << "Brak krawedzi" << std::endl;
            } else {
                out << *graph.AdjacencyMatrix[i][j] << std::endl;
            }
        }
    }
    return out;
}