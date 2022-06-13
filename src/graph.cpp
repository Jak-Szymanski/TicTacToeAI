#include "../inc/graph.h"

Graph::Graph(){

    VQueue = Dequeue<std::shared_ptr<Vertex>>();
    EQueue = Dequeue<std::shared_ptr<Edge>>();
}

Graph::Graph(const Graph &G){

    Node<std::shared_ptr<Vertex>> *ptr_v = G.VQueue.GetHead();
    while(ptr_v != NULL){
        Vertex tmp_v = *ptr_v->GetElem();
        VQueue.InsertEnd(std::make_shared<Vertex>(tmp_v));
        ptr_v = ptr_v->GetNext();
    }

    Node<std::shared_ptr<Edge>> *ptr_e = G.EQueue.GetHead();
    while(ptr_e != NULL){
        Edge tmp_e = *ptr_e->GetElem();
        EQueue.InsertEnd(std::make_shared<Edge>(tmp_e));
        ptr_e = ptr_e->GetNext();
    }
}

void Graph::CreateFutureMovesTree (std::shared_ptr<Vertex> V1, int i){

    if(i==0) return;

    Dequeue<GameState> possible_moves;
    auto V2 = std::make_shared<Vertex>();   
    GameState tmp_gs;

    possible_moves = V1->GetObject().GeneratePossibleMoves();

    while(!possible_moves.IsEmpty()){
        tmp_gs = possible_moves.RemoveFirst();
        V2 = InsertVertex(tmp_gs);
        InsertEdge(1,V1,V2);
        if(tmp_gs.GetCost() != BOARD_SIZE && tmp_gs.GetCost() != -BOARD_SIZE){
            CreateFutureMovesTree(V2, i-1);
        }
    }

}





std::ostream &operator << (std::ostream &out, Graph &graph){
    out << "Wierzcholki: " << std::endl << *graph.Vertices();
    out << "Krawedzie: " << std::endl << *graph.Edges();
    return out;
}



std::shared_ptr<Vertex> Graph::InsertVertex(GameState x){

    auto V = std::make_shared<Vertex>(x);

    VQueue.InsertFront(V);
    VQueue.GetHead()->GetElem()->SetPos(VQueue.GetHead());
    return V;    
}


std::shared_ptr<Edge> Graph::InsertEdge(int x, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end){

    auto E = std::make_shared<Edge>(x,start,end);

    EQueue.InsertFront(E);
    EQueue.GetHead()->GetElem()->SetPos(EQueue.GetHead());
    return E;
}


Dequeue<std::shared_ptr<Edge>> Graph::StartingEdges(std::shared_ptr<Vertex> V) const{

    Dequeue<std::shared_ptr<Edge>> dequeue;
    
    Node<std::shared_ptr<Edge>> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (*ptr->GetElem()->GetStart() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;
}

Dequeue<std::shared_ptr<Edge>> Graph::IncidentEdges(std::shared_ptr<Vertex> V) const{

    Dequeue<std::shared_ptr<Edge>> dequeue;
    
    Node<std::shared_ptr<Edge>> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (*ptr->GetElem()->GetStart() == *V || *ptr->GetElem()->GetEnd() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;    
}


Dequeue<std::shared_ptr<Vertex>> Graph::AdjacentVertices(std::shared_ptr<Vertex> V) const{

    Dequeue<std::shared_ptr<Edge>> incident = StartingEdges(V);
    Dequeue<std::shared_ptr<Vertex>> adjacent;

    while(!incident.IsEmpty()){
        adjacent.InsertFront(incident.RemoveFirst()->GetEnd());
    }
    return adjacent;
}

bool Graph::AreAdjacent(std::shared_ptr<Vertex> V1, std::shared_ptr<Vertex> V2) const {

    Node<std::shared_ptr<Edge>>* ptr = EQueue.GetHead();

    while(ptr != NULL){
        if(ptr->GetElem()->GetStart() == V1 && ptr->GetElem()->GetEnd() == V2) return true;
        ptr = ptr->GetNext();
    }
    return false;
}

void Graph::RemoveEdge(std::shared_ptr<Edge> E){

    Node<std::shared_ptr<Edge>>* ptr = E->GetPos();

    if(ptr == EQueue.GetHead()){
        EQueue.RemoveFirst();
        return;
    } 
    if(ptr == EQueue.GetTail()){
        EQueue.RemoveLast();
        return;
    }

    ptr->GetPrev()->SetNext(ptr->GetNext());
    ptr->GetNext()->SetPrev(ptr->GetPrev());
    delete ptr;
}

void Graph::RemoveVertex(std::shared_ptr<Vertex> V){

   Node<std::shared_ptr<Edge>>* ptr_e = IncidentEdges(V).GetHead();

    while(ptr_e != NULL){
        RemoveEdge(ptr_e->GetElem());
        ptr_e = ptr_e->GetNext();
    }

    Node<std::shared_ptr<Vertex>>* ptr_v = V->GetPos();

    if(ptr_v == VQueue.GetHead()){
        VQueue.RemoveFirst();
        return;
    } 
    if(ptr_v == VQueue.GetTail()){
        VQueue.RemoveLast();
        return;
    }

    ptr_v->GetPrev()->SetNext(ptr_v->GetNext());
    ptr_v->GetNext()->SetPrev(ptr_v->GetPrev());
    delete ptr_v;
}


void Graph::Delete(){

    VQueue.Delete();
    EQueue.Delete();
}



int Graph::Min(std::shared_ptr<Vertex> V, int *alpha, int* beta){

    Dequeue<std::shared_ptr<Vertex>> adjacent = AdjacentVertices(V);
    int min = 100;
    int cost;

    while(!adjacent.IsEmpty()){
        cost = adjacent.RemoveFirst()->GetObject().GetCost();
        if(cost < min){
            min = cost;
        }
    }
    
    if(min < *alpha) *alpha = min;


    V->SetCost(min);

    if(min >= *beta) return 1;
    else return 0;
}



int Graph::Max(std::shared_ptr<Vertex> V, int *alpha, int *beta){

    Dequeue<std::shared_ptr<Vertex>> adjacent = AdjacentVertices(V);
    int max = -100;
    int cost;

    while(!adjacent.IsEmpty()){
        cost = adjacent.RemoveFirst()->GetObject().GetCost();
        if(cost > max){
            max = cost;
        }
    }

    if(max > *beta) *beta = max;

    V->SetCost(max);

    if(max <= *alpha) return 1;
    else return 0;
}


int Graph::Minimax(std::shared_ptr<Vertex> V, int* alpha, int* beta){

    Dequeue<std::shared_ptr<Vertex>> adjacent = AdjacentVertices(V);

    if (adjacent.IsEmpty()){
/*         if(V->GetObject().NextMove == 1){
            Max(V, alpha, beta);
        } else {
            Min(V, alpha, beta);
        } */
        return 0;
    }

    while (!adjacent.IsEmpty()){
        if(Minimax(adjacent.RemoveFirst(), alpha, beta)==1){
            while(!adjacent.IsEmpty()){
                adjacent.RemoveFirst();
            }
            break;
        }
    }
    *beta = -100;
    *alpha = 100;

    if(V->GetObject().GetNextMove() == 1){
        return Max(V, alpha, beta);
    } else {
        return Min(V, alpha, beta);
    }
}


GameState Graph::GetMaxMove(std::shared_ptr<Vertex> V){

    Dequeue<std::shared_ptr<Vertex>> adjacent = AdjacentVertices(V);
    GameState GS;

    while(!adjacent.IsEmpty()){
        GS = adjacent.RemoveFirst()->GetObject();
        if(GS.GetCost() == V->GetObject().GetCost()){
            return GS;  
        }
    }
}