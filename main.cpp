#include "graph.h"
#include "edge.h"

#include <windows.h>

int main(){

    const int size=3;
    GameState<size> tablica;
    int x;
    int y;

    Vertex<size> *V1 = new Vertex<size>();
    Graph<size> graph;
    std::cout << "Rozmiar planszy: " << size << std::endl;
    
    while(1){
        std::cout << "Ruch gracza: " << std::endl;
        if (tablica.NextMove == -1) {
            std::cout << "X";
            std::cout << std::endl << "Podaj ruch" << std::endl;

            std::cin >> x;
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

            tablica.ChangeMove();
            tablica.DetermineCost();
        }
        else{
            std::cout << "O";
            std::cout << std::endl << "Ruch komputera: " << std::endl;
            V1 = graph.InsertVertex(tablica);
            graph.CreateFutureMovesTree(V1, SEARCH_DEPTH);   
            graph.Minimax(V1);
            tablica.InsertBoard(graph.GetMaxMove(V1)); 
            tablica.ChangeMove(); 
            graph.Delete();
           // Sleep(1000);       
        } 

        std::cout << tablica << std::endl;
        int result = tablica.CheckWinner();
        if (result == 1){
            std::cout << "Wygrany: Komputer " << std::endl;
            break;
        } 
        if (result == -1){
            std::cout << "Wygrany: Gracz " << std::endl;
            break;
        }
        if (result == DRAW){
            std::cout << "Remis! " << std::endl;
            break;
        }        
    }
}
