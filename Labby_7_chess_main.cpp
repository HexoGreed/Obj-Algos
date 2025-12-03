// Hamza S




//QA:
/*

I decided to solve the 8 queens problem using two different approaches, a deterministic backtracking algorithim and a randomized -
 - las vegas algorithim. The backtracking method explores the board row by row, placing queens and backtracking whenever something goes wrong
 (it gets cornered, is stuck, etc). This search guaruntees a solution if it exists but is a bit expensive on the computer as it may go through invalid
 configs. On the other hand the randomized algo places queens on random safe squares row by row restarting if it gets stuck.


 In terms of runtim the two algos behave differently. the backtracking offers consistant execution times because it's follows a fixed search path.
 The randomized algorithim is often slower than the backtracking because its almost completely a matter of luck. Sometimes its double the speed sometimes
 it can be quadruple. 



 backtrack time ex:
 1:0.091 ms
 2: 0.1222 ms
 3: 0.2424 ms


 random time ex:
 1: 0.0381 ms
 2:0.1118 ms
 3:  0.2796 ms

*/






#include "Queen.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>






int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    vector<vector<int>> board(boardSize, vector<int>(boardSize, 0));





    // backtrack
    cout << "Running backtracking: " << endl; // want letting me do either in the main for some reason
    auto Start_back = chrono::high_resolution_clock::now();


    if (BAckTrack(board, 0)) {
        auto end_back = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms_back = end_back - Start_back;
        printBorad(board);
        std::cout << "Backtracking Time: " << ms_back.count() << " ms" << std::endl;
    }
    else {
        cout << "No solution." << endl;
    }

    cout << "------------------------------" << endl;




    //random
    cout << "Running randomized: " << endl;
    auto Start_rand = chrono::high_resolution_clock::now();


    solveRandomized(board);




    auto end_back = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> ms_back = end_back - Start_rand;
    printBorad(board);
    std::cout << "Random Time: " << ms_back.count() << " ms" << std::endl;



    return 0;
}