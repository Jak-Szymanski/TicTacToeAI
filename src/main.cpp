#include "../inc/adjlistgraph.h"
#include "../inc/adjmatrixgraph.h"
//#include "../inc/gamestategraph.h"

#include <windows.h>
#include <chrono>

int main(){
 
    int x;
    int y;
    int* alpha = new int(100);
    int* beta = new int(-100);

/*     std::vector<std::vector<int>> test;
    test.resize(3,std::vector<int>(3,0));
    test[0][1] = test[1][0] = test[2][2] = 1;
    test[0][2] = test[1][2] = test[2][0] = 2;
    test.erase(test.begin());
    for(int i=0; i<2;i++){
        for(int j=0; j<3; j++){
            std::cout << test[i][j] << " ";
        }
        std::cout << std::endl;
    } */

    auto V1 = std::make_shared<Vertex<GameState>>(); 
                             auto V2 = std::make_shared<Vertex<GameState>>();  
    auto Vdelete = std::make_shared<Vertex<GameState>>();  

    // Graph<GameState> graph;
    AdjacencyListGraph<GameState> graph;
    // AdjacencyMatrixGraph<GameState> graph;




    std::cout << "Podaj rozmiar planszy: " << std::endl;
    std::cin >> BOARD_SIZE;


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


/*             std::shared_ptr<Edge<GameState>> E;
            V1 = graph.InsertVertex(tablica);
            tablica.InsertChar(2,2);
            Vdelete = graph.InsertVertex(tablica);
            graph.InsertEdge(1, V1, Vdelete);

            V1 = graph.InsertVertex(tablica);
            tablica.InsertChar(0,0);
            V2 = graph.InsertVertex(tablica);
            graph.InsertEdge(1, V1, V2);
            
            V1= graph.InsertVertex(tablica);
            tablica.InsertChar(0,2);
            V2 = graph.InsertVertex(tablica);
            E = graph.InsertEdge(1, V1, V2); */

            
            //graph.RemoveVertex(Vdelete);
            // std::cout << graph;

            // return 0;

            //std::cout << std::endl << std::endl << std::endl << *graph.Edges();
            
            // return 0;

            auto start = std::chrono::steady_clock::now();
            graph.CreateFutureMovesTree(V1, SEARCH_DEPTH); 
                //std::cout << graph;
            graph.Minimax(V1, alpha, beta);
            auto end = std::chrono::steady_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;

            tablica.InsertBoard(graph.GetMaxMove(V1)); 
            tablica.ChangeMove();   
                                                                            // graph.Delete();

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
}
