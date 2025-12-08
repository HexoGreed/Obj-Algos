#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

using namespace std;

atomic<bool> SolnFound(false);
mutex Out_Mutex;
vector <int> final_soln;



int countConflicts(const vector<int>& board, int row, int col, int n) {
	int count = 0;
	for (int c = 0; c < n; ++c) {
		if (c == col) continue;
		int otherRow = board[c];


		if(otherRow == row || abs(otherRow - row) == abs(c - col)) {
			++count;
		}
	}


	return count;
}



vector<int> GetConflictQueens(vector<int>& board, int n) {

	vector<int> conflictCols;

	for (int col = 0;
		col < n; ++col) {

		if (countConflicts(board, board[col], col, n) > 0) {

			conflictCols.push_back(col);

		}
	}

	return conflictCols;
}







void solverWork(int n, int maxItter, int seed) {
	mt19937 gen(seed);






	vector<int> board(n);
	for (int i = 0; i < n; ++i) {
		board[i] = i;

	}
	shuffle(board.begin(), board.end(), gen);   // put this in the loop acceidentally





	for (int iter = 0; iter < maxItter; ++iter) {
		// Check stop signal from other threads
		if (SolnFound.load()) return;

		std::vector<int> conflicts = GetConflictQueens(board, n);
		if (conflicts.empty()) {
			// Critical section to save result



			if (!SolnFound.exchange(true)) {


				final_soln = board;
				lock_guard<std::mutex> lock(Out_Mutex);
				cout << "Thread " << this_thread::get_id()
					<< " found a solution at iteration " << iter << "!\n";
			}


			return;
		}



		uniform_int_distribution<> dis_conf(0, conflicts.size() - 1);
		int var_col = conflicts[dis_conf(gen)];


		int minConflicts = 999999;
		vector<int> besestRows;



		for (int r = 0; r < n; ++r) {
			int currConflicts = countConflicts(board, r, var_col, n);

			if (currConflicts < minConflicts) {
				minConflicts = currConflicts;
				besestRows.clear();
				besestRows.push_back(r);

			}
			else if (currConflicts == minConflicts) {

				besestRows.push_back(r);
			}
		}



		if (!besestRows.empty()) {

			uniform_int_distribution<> dis_best(0, besestRows.size() - 1);
			board[var_col] = besestRows[dis_best(gen)];

		}

	} // forgot brace

}

