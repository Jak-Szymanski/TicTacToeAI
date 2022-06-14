#include "../inc/gamestategraph.h"

template<>
void Graph<GameState>::CreateFutureMovesTree(std::shared_ptr<Vertex<GameState>> V1, int i){

    if(i==0) return;

    Dequeue<GameState> possible_moves;
    auto V2 = std::make_shared<Vertex<GameState>>();   
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


template<>
int Graph<GameState>::Min(std::shared_ptr<Vertex<GameState>> V, int *alpha, int* beta){

    Dequeue<std::shared_ptr<Vertex<GameState>>> adjacent = AdjacentVertices(V);
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


template<>
int Graph<GameState>::Max(std::shared_ptr<Vertex<GameState>> V, int *alpha, int *beta){

    Dequeue<std::shared_ptr<Vertex<GameState>>> adjacent = AdjacentVertices(V);
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

template<>
int Graph<GameState>::Minimax(std::shared_ptr<Vertex<GameState>> V, int* alpha, int* beta){

    Dequeue<std::shared_ptr<Vertex<GameState>>> adjacent = AdjacentVertices(V);

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

template<>
GameState Graph<GameState>::GetMaxMove(std::shared_ptr<Vertex<GameState>> V){

    Dequeue<std::shared_ptr<Vertex<GameState>>> adjacent = AdjacentVertices(V);
    GameState GS;

    while(!adjacent.IsEmpty()){
        GS = adjacent.RemoveFirst()->GetObject();
        if(GS.GetCost() == V->GetObject().GetCost()){
            return GS;  
        }
    }
}

/* template<>
std::ostream &operator << (std::ostream &out, Graph<GameState> &graph){
    out << "Wierzcholki: " << std::endl << *graph.Vertices();
    out << "Krawedzie: " << std::endl << *graph.Edges();
    return out;
} */