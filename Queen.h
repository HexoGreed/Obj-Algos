#pragma once
#include <iostream>
#include <cstdlib> // rand , srand
#include <ctime> // time
#include <chrono> 
#include <vector>
using namespace std; // im not writing allat


//QA:







/////////////////////////



const int boardSize = 8;


void printBorad(const vector<vector<int>>& board){
	for (int i = 0; i < boardSize; i++) {
		for(int j = 0; j < boardSize; j++){
			cout << board[i][j] << " ";
		}
		cout << endl;


	}


}



//checks if the mvoe is safe VVVVV
bool CheckMove(const vector<vector<int>>& board, int row, int col) {

	for (int j = 0; j < col; ++j) {
		if (board[row][j]) {
			return false;
		}
	} // left row



	for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
		if (board[i][j]) {
			return false;
		}
	} // upper diag



	for (int i = row, j = col; i < boardSize && j >= 0; ++i, --j) {
		if (board[i][j]) {
			return false;
		}
	} // lower diag



	return true;

}



// Backtracking algo VVV

bool BAckTrack(vector<vector<int>>& board, int col) {

	if (col == boardSize) {
		return true;
	}



	for (int row = 0; row < boardSize; ++row) { // check if safe
		if (CheckMove(board, row, col)) {
			board[row][col] = 1; //queen down


			if (BAckTrack(board, col + 1)) { //recurse to place rest of the queens

				return true;
			}



			board[row][col] = 0; //remove queens if backtrack didnt work
		}




	}
	return false;// if no row worked 
}


	// random algo
	void solveRandomized(std::vector<std::vector<int>>&board) {   // las vegas algo


		while (true) {
			bool win = true;


			// clear board
			board.assign(boardSize, vector<int>(boardSize, 0));


			for (int col = 0; col < boardSize; col++) {


				vector<int> safeRows;
				for (int row = 0; row < boardSize; ++row) { // see if anything near us is safe

					if (CheckMove(board, row, col)) {
						safeRows.push_back(row);
					}
				}


				if (safeRows.empty()) { // the house always wins :(
					win = false;
					break;

				}
				else { // pick random safe
					int randIndex = rand() % safeRows.size();
					int chosenRow = safeRows[randIndex];
					board[chosenRow][col] = 1;
				}


			}




			if (win) {

				break;
			}


		}
	}
	