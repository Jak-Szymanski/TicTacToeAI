#include "graph.h"

int main(){

    const int size = 3;
    GameState<size> tablica;
    int x;
    int y;

    Vertex<size> *V1 = new Vertex<size>();
    Vertex<size> *V2 = new Vertex<size>();
    Graph<size> graph;
    tablica.InsertChar(0,0);

/*     Vertex<size> V3(tablica);

    std::cout << "V3: " << std::endl <<  V3 << std::endl; */
    V1 = graph.InsertVertex(tablica);
    //std::cout << *V1 << std::endl;
    
    while(1){
        std::cout << "Ruch gracza: " << std::endl;
        if (tablica.NextMove == -1) std::cout << "X";
        else std::cout << "O";
        
        std::cout << std::endl << "Podaj ruch" << std::endl;
        std::cin >> x;
        if(x == 10){
           std::cout << graph << std::endl;
        } else {
        if(x==12){
           std::cout << tablica.GeneratePossibleMoves() << std::endl;
        }
        std::cin >> y;


        try {tablica.InsertChar(x,y);}
        catch (const int error_type){
            if (error_type == SPACE_TAKEN_ERR){
                std::cout << "Pole zajete, sprobuj jeszcze raz" << std::endl;
                continue;
            } 
            if(error_type == OUTSIDE_BOARD_ERR){
                std::cout << "Niepoprawne pole, sprobuj jeszcze raz" << std::endl;
                continue;
            }
        }

        V2 = graph.InsertVertex(tablica);
        graph.InsertEdge(1,V1,V2);
        
        //std::cout << *V2 << std::endl;
        std::cout << tablica << std::endl;
        if (tablica.CheckWinner() != 0){
            std::cout << "Wygrany!!! " << tablica.CheckWinner() << std::endl;
        }
        std::cout << "Koszt: " << tablica.DetermineCost() << std::endl;
        std::cout << std::endl;
        
        }
    }
}