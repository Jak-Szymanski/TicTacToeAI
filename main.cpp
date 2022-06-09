#include "./inc/graph.h"

#include <windows.h>
#include <chrono>

int main(){
 
    int x;
    int y;
    int* alpha = new int(100);
    int* beta = new int(-100);
    int zapis = 0;

    std::ofstream outputfile("test.csv");

    Vertex *V1 = new Vertex();
    Graph graph;


    std::cout << "Podaj rozmiar planszy: " << std::endl;
    std::cin >> BOARD_SIZE;

    std::cout << "Czy robić zapis? "<< std::endl;
    std::cin >> zapis;

    GameState tablica;

    
    while(1){
        std::cout << "Ruch gracza: " << std::endl;
        if (tablica.GetNextMove() == -1) {
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
            auto start = std::chrono::steady_clock::now();
            graph.CreateFutureMovesTree(V1, SEARCH_DEPTH); 
            graph.Minimax(V1, alpha, beta);
            auto end = std::chrono::steady_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;

            tablica.InsertBoard(graph.GetMaxMove(V1)); 
            tablica.ChangeMove();      

            if(zapis){
            outputfile << tablica << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl << std::endl;
            }
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
    delete alpha;
    delete beta;
    delete V1;
}
