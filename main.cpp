/*
 * Author: Dhroov Pandey
 */
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//CONSTANT VARIABLES
const int row_size = 8, col_size = 8;

//KING TRACKER
int w_k_pos[2] = {7,4},b_k_pos[2] = {0,4};  //format -> {row,column} / {file,rank}

//COORDINATE OF CURRENT SQUARE & DESTINATION SQUARE
int cor[2] = {0},des[2] = {0};  //format for cor -> (row,col) same for des

//structure of board and turn
struct board{
    string board_matrix[row_size][col_size] ;
    bool turn = 0;
};

//FUNCTION DECLARATIONS

inline void display_board(const board& b);
inline void constructor_board(board& b);
inline void get_square(const board& b);
inline bool is_valid(int row,int col,const board& b);
inline void make_move(board& b);
inline void print_moves(vector<int> x);
inline void print_all_game_moves();
inline bool in_check(int r,int c,const board& b);

//Moves Database
vector <int> moves;      //TO BE PRINTED AT THE END OF THE GAME

//HEADER FILE
#include "Pieces_logic.h"
#include "King.h"

//MAIN FUNCTION
int main() {
    board b;
    constructor_board(b);
    int curr_king[2] = {0,0};
    while (cin) {
        if (b.turn) {
            curr_king[0] = b_k_pos[0];
            curr_king[1] = w_k_pos[1];
        }
        else {
            curr_king[0] = w_k_pos[0];
            curr_king[1] = w_k_pos[1];
        }
        if(!in_check(curr_king[0],curr_king[1],b)){
            display_board(b);
            get_square(b);
            make_move(b);
            print_all_game_moves();
        }
        else{
            cout<<"King in check"<<endl;
            break;
        }
    }
    return 0;
}

//FUNCTION DEFINITIONS

#include "Func_implementation.h"

//FUNCTION DOCUMENTATION

/*
 * Function Name: constructor_board
 * parameters: a structure of type board by reference
 * return: Void function
 * Description: Sets up the black and white pieces in the board matrix of structure board instance
 */

/*
 * Function name: display_board
 * parameters: a structure of type board
 * return: void function
 * description: displays the board matrix and prints which side has the turn
 */

/*
 * Function Name: get_square
 * parameters: none
 * return: void
 * description: gets the user input for cursor selected square and assigns the coordinates to global array cor
 */

/*
 * Function Name: is_valid
 * parameters: coordinates for row and column in form of 2 integers
 * return: boolean
 * description: checks if the given coordinates are within the bounds of board matrix
 */

/*
 * Function Name: make_move
 * parameters: object of structure board by reference
 * return: void
 * description: takes the destination for player's piece and replaces the object on that square with the player's piece while vacating the original square
 */

/*
 * Function Name: print_moves
 * parameters: A vector of valid moves
 * return: Void
 * description: Takes the vector containing valid move from piece classes and prints the moves in notation format
 */

/*
 * Function Name: print_all_game_moves
 * parameters: None
 * return: Void
 * description: Uses the vector moves that keeps record of all the moves played to display them at the end of the game
 */

/*
 * Function Name: in_check
 * parameters: row,columns integers and board class object
 * return : boolean value regarding whether the coordinate square (row,column) is in check
 * description: determines whether the passed square on board matrix will be in check from the enemy pieces
 */