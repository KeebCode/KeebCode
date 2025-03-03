/*
Name: Weini Li
Class: CSCI 135
Professor Tong yi 
Program: Project 3
*/

//Project 3

#include <string>
#include <iostream> 
#include <cstdlib>
#include <ctime> 
#include <iomanip>
#include <vector> 
#include "Board.hpp"

using namespace std;

class Location{
    public:
        int row;
        int col;
};

//3A
void Board:: allocateMemory(){
    panel = new int* [numRows];
    for(int row = 0; row < numRows; row++){
        panel[row] = new int [numCols];
        for(int col = 0; col < numCols; col++){
            panel[row][col];
        }
    }
}

Board:: Board(){
    max = 0; 
    target = 32; 
    numRows = 3;
    numCols = 3;
    panel = new int* [numRows];
    for(int row = 0; row < numRows; row++){
        panel[row] = new int [numCols];
        for(int col = 0; col < numCols; col++){
            panel[row][col] = 0;
        }
    }
}

Board:: Board(int m) : Board(m ,m){
    if(m >= 1){
        numRows = m; 
        numCols = m;
    }
    else{
        numRows = 3;
        numCols = 3;
    }
    max = 0; 
    target = 32;
    
    panel = new int* [numRows];
    for(int row = 0; row < numRows; row++){
        panel[row] = new int [numCols];
        for(int col = 0; col < numCols; col++){
            panel[row][col] = 0;
        }
    }
    

}

//taught in class 
Board:: Board(int m, int n){
    if(!(m >= 1 && n >= 1)){
        numRows = 3;
        numCols = 3;
    }
    else{
        numRows = m;
        numCols = n;
    }
    max = 0;
    target = 32;
    // panel = new int*[numRows]; 
    // for(int row = 0; row < numRows; row++){    
    //     panel[row] = new int[numCols];
    // }
    // clear();
    panel = new int* [numRows];
    for(int row = 0; row < numRows; row++){
        panel[row] = new int [numCols];
        for(int col = 0; col < numCols; col++){
            panel[row][col] = 0;
        }
    }
}

void Board:: clear(){
    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){
            panel[row][col] = 0;
        }
    }
}

Board:: ~Board(){
    for(int row = 0; row < numRows; row++){
        delete[] panel[row];
        panel[row] = nullptr;
    }
    delete[] panel;
    panel = nullptr;

}

void Board::print() const{         
    for (int i = 0; i < numRows; i++){
        cout << "+";
        for(int j = 0; j < numCols; j++){
            cout << "----+";
        }
        cout << endl << "|";
        for(int j = 0; j < numCols; j++){
            if(panel[i][j] != 0){
                cout << setw(4) << panel[i][j] << "|";     //setw means set field width from iomanip (IO Manipulators)
            }
            else{
                cout << "    |";
            }
        }
        cout << endl;
    }
    cout << "+";
    for(int i = 0; i < numCols; i++){
        cout << "----+";
    }
    cout << endl;

}

int Board:: getNumRows() const{
    return numRows;
}
int Board:: getNumCols() const{
    return numCols;
}
int Board:: getTarget() const{
    return target;
}
int Board:: getMax() const{
    return max;
}

//3B

void Board::selectRandomCell(int& row, int& col){
    vector<Location> zeros;
    Location cell;
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            if(panel[i][j] == 0){
                cell.row = i;      //to access the vector libary, use .(name)
                cell.col = j;
                zeros.push_back(cell);
            }
        }
    }

    if(zeros.size() > 0){
        int index = rand() % zeros.size();
        row = zeros[index].row;
        col = zeros[index].col;
        panel[row][col] = 1;
        print();
    }

    if(zeros.size() == 0 || zeros.size() == 1){
        if(noAdjacentSameValue()){
            if(max <  target){
                cout << "Game over. Try again." << endl;
            }
            else{
                cout << "Congratulations!" << endl;
            }
            exit(0);
        }
        else 
            return;
    }

}

// void Board::selectRandomCell(int& row, int& col)
// {
//     vector<Location> zeros;
//     Location cell;
//      for(int i = 0; i < numRows; i++)
//      {
//          for(int j = 0; j < numCols; j++)
//          {
//              if (panel[i][j] == 0)
//              {
//                 cell.row = i;
//                 cell.col = j;
//                 zeros.push_back(cell);
//             }
//          }
//      }

//      if (!zeros.empty())
//      {
//          int index = rand() % zeros.size(); 
//          row = zeros[index].row;
//          col = zeros[index].col;
//          panel[row][col] = 1;
//          print();
//      }
//      if (zeros.size()<=1)
//      {
//          if (noAdjacentSameValue()) 
//          {
//              if (max<target)
//              {
//                  cout<<"Game over. Try again." << endl;
//              } 
//              else
//              {
//                  cout<<"Congratulations!" << endl;
//              }
//              exit(0); 
//           } 
//      }
// }

bool Board::noAdjacentSameValue() const{
    // for(int i = 0; i < numCols; i++){
    //     for(int j = 0; j < numCols - 1; j++){
    //         if(panel[i][j] == panel[i][j+1]){
    //             return false;
    //         }
    //         if(panel[i][j] != panel[i][j+1]){
    //             for(int j = 0; j < numCols; j++){
    //                 for(int i = 0; i < numRows - 1; i++){
    //                     if(panel[i][j] == panel[i+1][j]){
    //                         return false;
    //                     }
    //                     else if(max < target){
    //                         return true;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols - 1; j++){
            if(panel[i][j] == panel[i][j+1]){
                return false;
            }
        }
    }   
       
    for(int j = 0; j < numCols; j++){
        for(int i = 0; i < numRows - 1; i++){
            if(panel[i][j] == panel[i+1][j]){
                return false;
            }
        }
    }

    //if(max < target){
        return max < target;
    

}


//3C
//given?
void merge(vector<int>& result){
        int i = 0;
        int size = result.size();
        while(i < size){
            if(i+1 < size && result[i+1] == result[i]){
                result[i] *= 2;
                result[i+1] = 0;
                i += 2;
            }
            else{
                i++;
            }
        }
}
void Board:: pressUp(){
    for(int col =  0; col < numCols; col++){
        vector<int> nonZeros;
        for(int row = 0; row < numRows; row++){
            if(panel[row][col] != 0){
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros);
        int row = 0;
        for(int i=0; i < nonZeros.size(); i++){
            if(nonZeros[i] != 0){
                panel[row][col] = nonZeros[i];
                row++;
            }
        }
        while(row < numRows){
            panel[row][col] = 0;
            row++;
        }
    }
    int row;
    int col;
    selectRandomCell(row, col);
}
void Board:: pressDown(){
    for(int col =  0; col < numCols; col++){
        vector<int> nonZeros;
        for(int row = numRows-1; row >= 0; row--){
            if(panel[row][col] != 0){
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros);
        int row = numRows - 1; 
        for(int i=0; i < nonZeros.size(); i++){
            if(nonZeros[i] != 0){
                panel[row--][col] = nonZeros[i];
            }
        }
        for(; row >= 0; row--){
            panel[row][col] = 0;
        }
    }
    int row;
    int col;
    selectRandomCell(row, col);
}
void Board:: pressLeft(){
    for(int row = 0; row < numRows; row++){
        vector<int> nonZeros;
        for(int col = 0; col < numCols; col++){
            if(panel[row][col] != 0){
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros);
        int col = 0; 
        for(int i=0; i < nonZeros.size(); i++){
            if(nonZeros[i] != 0){
                panel[row][col] = nonZeros[i];
                col++;
            }
        }
        while(col < numCols){
            panel[row][col] = 0;
            col++;
        }
        
    }
    int row;
    int col;
    selectRandomCell(row,col);
}
void Board:: pressRight(){
    for(int row = 0; row < numRows; row++){
        vector<int> nonZeros;
        for(int col = numCols-1; col >=0; col--){
            if(panel[row][col] != 0){
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros);
        int col = numCols - 1; 
        for(int i=0; i < nonZeros.size(); i++){
            if(nonZeros[i] != 0){
                panel[row][col--] = nonZeros[i];
            }
        }
        for(; col >= 0; col--){
            panel[row][col] = 0;
        }
    }
    int row;
    int col;
    selectRandomCell(row, col);
}


// void printSeparateLine(int numCols){
//     cout << "+";
//     for(int i = 0; i < numCols; i++){
//         cout << "----+";
//     }
//     cout << endl;
// }

void Board::start(){
    int round = 1;
    int row = 0, col = 0;
    int row2 = 0, col2 = 0;
    selectRandomCell(row, col);
    selectRandomCell(row2, col2);
    char ch;
    while(true){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    if(panel[i][j] > max){
                        this->max = panel[i][j];
                    }
                }
            }
        if(max >= target){
            cout << "Congratulation!" << endl;
            break;
        }
        ch = getchar();
        if(ch == 'S'){
            break;
        }
        if(ch == '\033'){
            getchar();
            switch(getchar()){
                case 'A':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press UP. " << "Goal: " << target << endl;
                    pressUp();
                    round++;
                    break;
                case 'B':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press DOWN. " << "Goal: " << target << endl;
                    pressDown();
                    round++;
                    break;
                case 'C':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press RIGHT. " << "Goal: " << target << endl;
                    pressRight();
                    round++;
                    break;
                case 'D':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press LEFT. " << "Goal: " << target << endl;
                    pressLeft();
                    round++;
                    break;
            }
        }
    }
}