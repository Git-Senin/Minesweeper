#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "functions.h"

using namespace std;

bool running;
bool bombExplode;

int rows = 10;
int columns = 10;

int boardArr[10][10];

bool isNumber(string string)
{
  //check every element if its integer
    for (int i = 0; i < string.length(); i++)
        if (isdigit(string[i]) == false){
            return false;
          }
    return true;
}

int main() {
  cin.clear();
  ofstream outputFile;
  const int CHOICE1 = 1, CHOICE2 = 2, QUIT_CHOICE = 3;

  double num1;
  double num2;
  double answer1;
  double answer2;
  string choice;
  int num;

  vector<string> thanks { "Thank", "you", "for", "playing", "minesweeper." };

  do {
    system("clear");
    displayMenu();
    cin >> choice;

    while (!isNumber(choice) || ( (num = stoi(choice))<(CHOICE1) || (num = stoi(choice))>(QUIT_CHOICE) ) )  {
     cout << "Invalid input."<<endl;
      cout << "Please try again: "<<endl;
      cin >> choice;
    }

//After while loop over, choice is integer so change data type of choice to integer
    num = stoi(choice);
    switch (num) {
    case CHOICE1: {
      outputFile.open("numbers.txt");
      outputFile << "\n\tYour scores were organized in descending order"
                 << "\n";
      outputFile
          << "-------------------Start of scores-------------------------\n";

      char choice = 'y';
      while (choice == 'Y' || choice == 'y') {
        int SIZE;
        int *arr = nullptr;

        // input number of games
        system("clear");
        cout << "\n\tPlease enter the number of games you want to play: ";
        cin >> SIZE;
        arr = new int[SIZE];
        system("clear");
        for (int i = 0; i < SIZE; i++) {
          int x;
          int tstart;
          int tend;

          //  Clear Board
          clearBoard(boardArr, rows, columns);

          //  Place mines
          randomizeMines(boardArr, 10, rows, columns); // Num of Mines CHANGABLE

          // start of time
          tstart = time(0);

          // Game Loop
          bombExplode = false;
          int turnCount = 0;

          while (bombExplode == false) {
            // Game Count
            cout << "\n------------- Game " << i + 1 << " -------------\n";
            
            if (turnCount == 0) {    // On First Turn
              // Board
              displayBoard(boardArr, rows, columns);
              
              // Open initial tile and Update bombExplode
              initialOpenPrompt(boardArr, bombExplode);
              
              system("clear");
            }
            else{
              // Board
              displayBoard(boardArr, rows, columns);
              
              // Flag
              flagPrompt(boardArr);

              // Open initial tile and Update bombExplode
              openPrompt(boardArr, bombExplode);
              
              system("clear");
            }

            turnCount++;
          }

          // end of time
          tend = time(0);
          int timeElapsed = tend - tstart;
          if (bombExplode == false) {
          cout << endl << "\tScore: " << timeElapsed << " seconds\n";
          }
          // Pause
          cout << endl << "\tPress enter to continue...";
          cin.ignore();
          cin.ignore();
          system("clear");

          // store times in array
          *(arr + i) = timeElapsed;

        } // end of input

        // Displays your scores

        // Sorts the array in descending order
        int tempnum;

        int len = (arr + (SIZE)) -
                  arr; // subtract last memory address to first memory address

        for (int i = 0; i < (len - 1); i++) {
          for (int i = 0; i < (len - 1); i++) {
            if (*(arr + i) < *(arr + i + 1)) {
              tempnum = *(arr + i + 1);
              *(arr + i + 1) = *(arr + i);
              *(arr + i) = tempnum;
            }
          }
        }

        // beginning of file writing
        for (int i = 0; i < SIZE; i++) {
          outputFile << *(arr + i) << " \n";
        }

        // Displays yours scores in descending order
        cout << "\n  Your scores in descending order are\n";
        for (int i = 0; i < SIZE; i++) {
          cout << "\n  "<< *(arr + i);
        }

        cout << "\n\n  Would you like to play another session of minesweeper? (Y/N) ";
        cin >> choice;

      } // end of while loop
      outputFile
          << "-------------------End of scores-------------------------\n";
      outputFile.close();
      break;
    } // end of first case here, using brackets to contain variables.

    case CHOICE2:
      system("clear");
      displayInstructions();
      cout << endl << "  Press enter to continue...";
      cin.ignore();
      cin.ignore();
      break;
    } // end ofswitch statemrnt

  } while (num != QUIT_CHOICE);
  system("clear");
  cout << "\n\t";
  for (int i=0; i<5; i++)
    cout << thanks.at(i) << " ";

  return 0;
}