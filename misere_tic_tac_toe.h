#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"

Player<char>* globalplayers1[2];

template <typename T>
class Misere_tic_tac_toe_Board:public Board<T> {
public:
    Misere_tic_tac_toe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Misere_tic_tac_toe_Player : public Player<T> {
public:
    Misere_tic_tac_toe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Misere_tic_tac_toe_Random_Player : public RandomPlayer<T>{
public:
    Misere_tic_tac_toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Misere_tic_tac_toe_Board<T>::Misere_tic_tac_toe_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Misere_tic_tac_toe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Misere_tic_tac_toe_Board<T>::display_board() {
    int r = 0;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n" << r << " |";
        r++;
        for (int j = 0; j < this->columns; j++) {  // Adjust the column limit per row
            cout << setw(2) << this->board[i][j] << " |";
        }
    }
    cout << endl;
    cout << setw(5);
    for(int c = 0; c < this->columns; c++) {
        cout << c << setw(4);
    }
    cout << endl;
    cout << string(15, '-') << endl;
}

// Returns true if there is any winner
template <typename T>
bool Misere_tic_tac_toe_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] == 'X') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] == 'X')) {
            *globalplayers1[0] = *globalplayers1[1];
            return true;
        }
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] == 'O') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] == 'O')) {
            *globalplayers1[1] = *globalplayers1[0];
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] == 'X') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] == 'X')) {
        *globalplayers1[0] = *globalplayers1[1];
        return true;
    }
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] == 'O') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] == 'O')) {
        *globalplayers1[1] = *globalplayers1[0];
        return true;
    }


    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Misere_tic_tac_toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Misere_tic_tac_toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Misere_tic_tac_toe_Player<T>::Misere_tic_tac_toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_tic_tac_toe_Player<T>::getmove(int& x, int& y) {
    cout << this->name << ", it's your turn (" << this->symbol << ").";
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Misere_tic_tac_toe_Random_Player<T>::Misere_tic_tac_toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Misere_tic_tac_toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H