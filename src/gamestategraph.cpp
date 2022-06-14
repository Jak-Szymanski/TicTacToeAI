#include "../inc/gamestategraph.h"


/*Stwórz graf zawierający potencjalne przyszłe ruchy obu członków, zaczynając od stanu opisanego wierzchołkiem V1
  szukając o i ruchów do przodu*/
template<>
void Graph<GameState>::CreateFutureMovesTree(Vertex<GameState>* V1, int i){

    if(i==0) return;

    Dequeue<GameState> possible_moves;
    auto V2 = new Vertex<GameState>();   
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

/*Wykonaj na wierzchołku V algorytm Min z algorytmu Minimax
  Zwróć 1 jeżeli będzie musiało nastąpić cięcie beta, 0 jeżeli nie
  Wpisz odpowiednie wartości alfa i beta do argumentów*/
template<>
int Graph<GameState>::Min(Vertex<GameState>* V, int *alpha, int* beta){

    Dequeue<Vertex<GameState>*> adjacent = AdjacentVertices(V);
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

/*Wykonaj na wierzchołku V algorytm Max z algorytmu Minimax
  Zwróć 1 jeżeli będzie musiało nastąpić cięcie alfa, 0 jeżeli nie
  Wpisz odpowiednie wartości alfa i beta do argumentów*/
template<>
int Graph<GameState>::Max(Vertex<GameState>* V, int *alpha, int *beta){

    Dequeue<Vertex<GameState>*> adjacent = AdjacentVertices(V);
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

/*Wykonuj rekursywnie algorytm minimax z alfa-beta cięciami na wierzchołku V i każdym jego kolejnym wierzchołku
  Wartość alfa powinna teoretycznie być równa nieskonczoności a beta minus nieskonczoności
  Są one na każdym poziomie przechodzenia przez ruchy ustawiane na wartości 100 i -100 */
template<>
int Graph<GameState>::Minimax(Vertex<GameState>* V, int* alpha, int* beta){

    Dequeue<Vertex<GameState>*> adjacent = AdjacentVertices(V);

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

/*Zwróć ruch o największej wartości (czyli ruch najlepszy dla komputera po wykonaniu algorytmu minimax)*/
template<>
GameState Graph<GameState>::GetMaxMove(Vertex<GameState>* V){

    Dequeue<Vertex<GameState>*> adjacent = AdjacentVertices(V);
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