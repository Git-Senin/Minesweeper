#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//For usleep();
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// ----------------------------------------------------------------------

void displayInstructions();
void displayMenu();
void randomizeMines (int arr[][10], int numOfMines, int rows, int columns);
void displayBoard(int arr[][10], int row, int columns);
int toNum(char letter);
void flag(int arr[][10], int row, char column);
void flagPrompt(int boardArr[][10]);
int countOfBombs(int board[][10], int row, char column);
void open(int arr[][10], int row, char column, bool &explosion);
void openPrompt(int boardArr[][10], bool &gameEnd);
void displayBoom();
void clearBoard(int arr[][10], int row, int columns);

void check_7 (int board[][10], int row, char column, int &count);
void check_8 (int board[][10], int row, char column, int &count);
void check_9 (int board[][10], int row, char column, int &count);
void check_4 (int board[][10], int row, char column, int &count);
void check_6 (int board[][10], int row, char column, int &count);
void check_1 (int board[][10], int row, char column, int &count);
void check_2 (int board[][10], int row, char column, int &count);
void check_3 (int board[][10], int row, char column, int &count);

// ----------------------------------------------------------------------

void displayInstructions() {
  cout << "\n\tWelcome to Minesweeper!\n";
  cout << "===========================================================================================\n";
  cout << "-The objective of the game is to clear the board without hitting any bombs.\n";
  cout << "-There are 10 bombs on the 10x10 board.\n";
  cout << "-You will dig up one tile at a time, if the tile is a bomb, you lose.\n";
  cout << "-If the tile is not a bomb, the tile will be replaced with a number indicating how many bombs are in adjacent tiles. \n";
  cout << "-If you are sure a certain tile is a bomb, you can 'flag' it and the tile will appear as 'P'.\n";
  cout << "===========================================================================================\n\n";
}

void displayMenu() {
  cout << "\n\tWelcome to Minesweeper!\n"
     << "------------------------------\n"
     << "\t1. Play game\n"
     << "\t2. Instructions\n"
     << "\t3. Quit the Program\n"
     << "------------------------------\n"
     << "\n\tEnter your choice (1-3): ";
}

void randomizeMines (int arr[][10], int numOfMines, int rows, int columns) {

    int count = 0;
    int rPos, cPos, randomPos;

    srand(time(NULL));                          //  Randomize Seed

    while (count < numOfMines)                  //  Until all mines placed
    {
        randomPos = rand() % (rows * columns);  //  Random in rangeof BoardSize(100)
        rPos = randomPos / rows;                //  RowPosition dividedBy 10

        randomPos = rand() % (rows * columns);  //  Random in rangeof BoardSize(100)
        cPos = randomPos / columns;

        if (arr[rPos][cPos] != 1){              //  If Not Mine
            arr[rPos][cPos] = 1;                //  Make mine
            count++;                            //  Count + 1
        }
    }
}

void displayBoard(int arr[][10], int row, int columns) {

    cout << "\n\t\t" << "a b c d e f g h i j" << endl << endl;

    for (size_t i = 0; i < row; i++) {      // Iterate Through Board
        for (size_t j = 0; j < columns; j++){

          if (j == 0) {

            cout << "\t";
            cout << setw(2) << right << i + 1;  // Nums on Left
            cout << "\t";

          } 

          switch (arr[i][j]){   //  Contents of Arr
            case 0:  
                cout << "/ ";   //  Closed Tile Empty 
                break;
            case 1:
                cout << "/ ";   //  Closed Tile Bomb
                break;
            case 10:
                cout << "  ";   //  Bomb Count : 0
                break;
            case 11:
                cout << "1 ";   //  Bomb Count : 1
                break;
            case 12:
                cout << "2 ";   //  Bomb Count : 2
                break;
            case 13:
                cout << "3 ";   //  Bomb Count : 3
                break;    
            case 14:
                cout << "4 ";   //  Bomb Count : 4
                break;
            case 15:
                cout << "5 ";   //  Bomb Count : 5
                break;
            case 16:
                cout << "6 ";   //  Bomb Count : 6
                break;
            case 17:
                cout << "7 ";   //  Bomb Count : 7
                break;
            case 18:
                cout << "8 ";   //  Bomb Count : 8
                break;
            case 20:            //  Flagged Tile
                cout << "P ";
                break;
            case 21:            //  Flagged Bomb
                cout << "P ";
                break;
            default:            //  Shown if Error
                cout << ". ";
                break;
          }
          
          if(j == columns - 1){ // End of Row
            cout << endl;
          }
        }
    }
    cout << endl;
}

int toNum(char letter) {

    int x = 0;

    char letters[10] = {'a','b','c','d','e','f','g','h','i','j'};

    for(size_t i = 0; i <= 9; i++) {
        if(letter == letters[i]) {
            x = i;
            return x;
        }
    }

    return {};
}

void flag(int arr[][10], int row, char column){
    if(arr[row - 1][toNum(column)] == 1){
        arr[row - 1][toNum(column)] += 20;
    }
    if(arr[row - 1][toNum(column)] == 0){
        arr[row - 1][toNum(column)] += 20;
    }
}

void flagPrompt(int boardArr[][10]){
  string wantFlag;
	bool useFlag;
	cout << "\n  Would you like to flag? (y/n) ";
	cin >> wantFlag;
	if(wantFlag == "y") useFlag = true;
	else if(wantFlag == "n") useFlag = false; 
	else useFlag = false;
	
	char flagColumn;
	int flagRow;
	if (useFlag) {
		cout << "\n  Which tile would you like to flag? (ex. g6) ";
		cin >> flagColumn;
		cin >> flagRow;
		flag(boardArr, flagRow, flagColumn);
	}
}

int countOfBombs(int board[][10], int row, char column){
    int count = 0;

    int unopenedBomb = 1;
    int flaggedBomb = 21;

    if(row == 0 && toNum(column) == 0){                               // 7 WORKING
      check_6(board, row, column, count);
      check_2(board, row, column, count);
      check_3(board, row, column, count);
    }
    if(row == 0 && toNum(column) > 0 && toNum(column) < 9){           // 8 WORKING
      check_4(board, row, column, count);
      check_6(board, row, column, count);

      check_1(board, row, column, count);
      check_2(board, row, column, count);
      check_3(board, row, column, count);
    }
    if(row == 0 && toNum(column) == 9){                               // 9 WORKING
		  check_4(board, row, column, count);

      check_1(board, row, column, count);
		  check_2(board, row, column, count);
    }
    if(row > 0 && row < 9 && toNum(column) == 0){                     // 4 WORKING
   		check_8(board, row, column, count);	
  		check_9(board, row, column, count); 
  
  		check_6(board, row, column, count); 
  
  		check_1(board, row, column, count); 
  		check_2(board, row, column, count);	
    }
    if(row > 0 && row < 9 && toNum(column) > 0 && toNum(column) < 9){ // 5 WORKING
  		check_1(board, row, column, count); 
  		check_2(board, row, column, count);	
  		check_3(board, row, column, count); 
  
  		check_4(board, row, column, count); 
  		check_6(board, row, column, count); 
  
  		check_7(board, row, column, count); 
  		check_8(board, row, column, count);	
  		check_9(board, row, column, count); 
    }
    if(row > 0 && row < 9 && toNum(column) == 9){                     // 6 WORKING
  		check_7(board, row, column, count); 
  		check_8(board, row, column, count);
          
  		check_4(board, row, column, count); 
  
  		check_1(board, row, column, count); 
  		check_2(board, row, column, count);	
    }
    if(row == 9 && toNum(column) == 0){                               // 1 WORKING
  		check_8(board, row, column, count);	
  		check_9(board, row, column, count);

      check_6(board, row, column, count);
    }
    if(row == 9 && toNum(column) > 0 && toNum(column) < 9){           // 2 WORKING
  		check_4(board, row, column, count); 
  		check_6(board, row, column, count);

      check_7(board, row, column, count); 
  		check_8(board, row, column, count);	
  		check_9(board, row, column, count); 
    }
    if(row == 9 && toNum(column) == 9){                               // 3 WORKING
		  check_4(board, row, column, count); 

      check_7(board, row, column, count); 
		  check_8(board, row, column, count);
    }
    return count;
}

void open(int arr[][10], int row, char column, bool &explosion){
    if(arr[row -1][toNum(column)] == 1 || arr[row -1][toNum(column)] == 21){
        explosion = true;
        displayBoom(); //Game End
    }
    if(arr[row - 1][toNum(column)] == 0 || arr[row - 1][toNum(column)] == 20){   // If Unopened Tile
        arr[row - 1][toNum(column)] = countOfBombs(arr, row - 1, column) + 10;
        if(arr[row - 1][toNum(column)] == 0){
            arr[row - 1][toNum(column)] = 3;
        }
    }
}

void initialOpenPrompt(int boardArr[][10], bool &gameEnd){
  char openColumn;
  int openRow;
  cout << "\n  Which tile would you like to open? (ex. c4) ";
  cin >> openColumn;
  cin >> openRow;
  boardArr[openRow][toNum(openColumn)] = 0;
  open(boardArr, openRow, openColumn, gameEnd);
}
void openPrompt(int boardArr[][10], bool &gameEnd){
    char openColumn;
    int openRow;
    cout << "\n  Which tile would you like to open? (ex. c4) ";
    cin >> openColumn;
    cin >> openRow;
    open(boardArr, openRow, openColumn, gameEnd);
}

void displayBoom() {
  
    cout << "\n\t";
    for (char c: "B O O O O M ! ! !") {
        cout << c << std::flush;
        usleep(80000);
    }
    cout << endl; 
    cout << "\n\n\t\t\t";
    cout << "- GAME OVER -";
    cout << "\n";
}

void clearBoard(int arr[][10], int row, int columns) {
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < columns; j++) {
            arr[i][j] = 0;                              // Itterate and Fill with 0
        }
    }
}

// Check Functions Increase count
void check_6 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) + 1] == flaggedBomb || board[row][toNum(column) + 1] == unopenedBomb){
        count += 1;
    }

}
void check_4 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) - 1] == flaggedBomb || board[row][toNum(column) - 1] == unopenedBomb){ 
        count += 1;
    }

}
void check_7 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) - 11] == flaggedBomb || board[row][toNum(column) - 11] == unopenedBomb){
        count += 1;
    }

}
void check_8 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) - 10] == flaggedBomb || board[row][toNum(column) - 10] == unopenedBomb){
        count += 1;
    }

}
void check_9 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) - 9] == flaggedBomb || board[row][toNum(column) - 9] == unopenedBomb){
        count += 1;
    }

}
void check_1 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) + 9] == flaggedBomb || board[row][toNum(column) + 9] == unopenedBomb){
        count += 1;
    }

}
void check_2 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) + 10] == flaggedBomb || board[row][toNum(column) + 10] == unopenedBomb){
            count += 1;
    }

}
void check_3 (int board[][10], int row, char column, int &count) {

    int unopenedBomb = 1;
    int flaggedBomb = 21;

	if(board[row][toNum(column) + 11] == flaggedBomb || board[row][toNum(column) + 11] == unopenedBomb){
        count += 1;
    }

}