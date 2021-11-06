/*
 * Author: Dhroov Pandey
 * Description: Game of chess
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//CONSTANT VARIABLES
const int row_size = 8, col_size = 8;

//KING TRACKER
int w_k_pos[2] = {7,4},b_k_pos[2] = {0,4};  //format -> {row,column} / {file,rank}

//checking piece coordinates
vector<int> checker;
vector<int>interceptors;
vector<int>elig_squares;       //A list of all the squares that can capture the checker

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
inline bool checker_capturable(vector<int> copy,const board& b);
inline bool is_pinned(int row,int col,board b);
inline bool intercept(int k_r,int k_c,int ch_r,int ch_c,board b);

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
            curr_king[1] = b_k_pos[1];
        }
        else {
            curr_king[0] = w_k_pos[0];
            curr_king[1] = w_k_pos[1];
        }
        display_board(b);
        if(!in_check(curr_king[0],curr_king[1],b)){
            get_square(b);
            make_move(b);
            print_all_game_moves();
        }
        else{
            checker.clear();
            in_check(curr_king[0],curr_king[1],b);
            vector<int> copy = checker;
            checker.clear();        //clear the vector so the next use will add the checker capturers to the list
            King k;
            k.get_moves(curr_king[0],curr_king[1],b);       //FIXME ADD INTERCEPT CONDITION AND ADJUST CURR_CHECKER TO VECTOR FORM
            if(k.move_list.size()==0 && copy.size()>2){
                cout<<"Checkmate"<<endl;
                return 0;
            }
            else if(k.move_list.size()==0 && checker_capturable(copy,b) == 0 && !intercept(curr_king[0],curr_king[1],copy[0],copy[1],b)){       //intercept and capture only work when there's a single attacker
                cout<<"Checkmate"<<endl;
                return 0;
            }
            get_square(b);
            while(b.board_matrix[cor[0]][cor[1]][0] != 'K'){        //FIXME!!! ADD INTERCEPT PIECES AND CAPTURE PIECES TOO
                cout<<"King is in check! Invalid square"<<endl;
                get_square(b);
            }
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