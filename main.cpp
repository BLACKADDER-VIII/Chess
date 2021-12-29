/*
 * Author: Dhroov Pandey
 * Description: Game of chess
 */
#include <iostream>
#include <vector>
#include <cmath>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
using namespace std;

//CONSTANT VARIABLES
const int row_size = 8, col_size = 8;

//KING TRACKER
int w_k_pos[2] = {7,4},b_k_pos[2] = {0,4};  //format -> {row,column} / {file,rank}

//checking piece coordinates
vector<int> checker;
vector<int>interceptors;        //list of all squares that can intercept a check
vector<int>elig_squares;       //A list of all the squares that can capture the checker

//COORDINATE OF CURRENT SQUARE & DESTINATION SQUARE
int cor[2] = {0},des[2] = {0};  //format for cor -> (row,col) same for des

//PROMOTION
vector<int> prom_sq;

//CASTLING
bool w_k_c = 1; //white king castling condition
bool b_k_c = 1; //black king castling condition
bool w_q_r = 1; //white queen side rook castling condition
bool w_k_r = 1; //white king side rook castling condition
bool b_q_r = 1; //black queen side rook castling condition
bool b_k_r = 1; //black king side rook castling condition

//IF A PINNED PIECE IS SELECTED
bool pin_sel = 0;       //If the piece is selected, (used by make_move func)
vector<int> pin_mov;    //To determine the only valid move for the piece

//structure of board and turn
struct board{
    string board_matrix[row_size][col_size] ;
    bool turn = 0;
};

//FUNCTION DECLARATIONS

inline void display_board(const board& b);
inline void constructor_board(board& b);
inline void get_square(board& b);
inline bool is_valid(int row,int col,const board& b);
inline void make_move(board& b);
inline void print_moves(vector<int> x);
inline void print_all_game_moves();
inline bool in_check(int r,int c,const board& b);
inline bool checker_capturable(vector<int> copy,board b);
inline bool is_pinned(int row,int col,board b);
inline bool intercept(int k_r,int k_c,int ch_r,int ch_c,board b);
inline bool promotion(const board& b);

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
        cout<<"W_k_r: "<<w_k_r<<endl;
        if (b.turn) {
            curr_king[0] = b_k_pos[0];
            curr_king[1] = b_k_pos[1];
            if(cor[0] == 7 && cor[1] == 0){
                if(b.board_matrix[des[0]][des[1]][0]=='R'){
                    w_q_r = 0;
                }
            }
            if(cor[0] == 7 && cor[1] == 7){
                if(b.board_matrix[des[0]][des[1]][0]=='R'){
                    w_k_r = 0;
                }
            }
        }
        else {
            curr_king[0] = w_k_pos[0];
            curr_king[1] = w_k_pos[1];
            if(cor[0] == 0 && cor[1] == 0){
                if(b.board_matrix[des[0]][des[1]][0]=='R'){
                    b_q_r = 0;
                }
            }
            if(cor[0] == 0 && cor[1] == 7){
                if(b.board_matrix[des[0]][des[1]][0]=='R'){
                    b_k_r = 0;
                }
            }
        }
        display_board(b);
        if(!in_check(curr_king[0],curr_king[1],b)){
            get_square(b);
            make_move(b);
            print_all_game_moves();
        }
        else{
            checker.clear();
            interceptors.clear();
            elig_squares.clear();
            in_check(curr_king[0],curr_king[1],b);
            vector<int> copy = checker;     //A copy of the original checker list for this turn
            checker.clear();        //clear the vector so the next use will add the checker capturers to the list
            King k;
            k.get_moves(curr_king[0],curr_king[1],b);
            if(k.move_list.size()==0 && copy.size()>2){
                cout<<"Checkmate"<<endl;
                return 0;
            }
            else if(k.move_list.size()==0 && checker_capturable(copy,b) == 0 && intercept(curr_king[0],curr_king[1],copy[0],copy[1],b)==0){       //intercept and capture only work when there's a single attacker
                cout<<"Checkmate"<<endl;
                return 0;
            }
            //Running the intercept and checker capturable again because if the king size was greater than 0 then the previous if statement skips running them
            intercept(curr_king[0],curr_king[1],copy[0],copy[1],b);
            checker_capturable(copy,b);
            vector <int> temp_move_list;
            if(k.move_list.size()){
                temp_move_list.push_back(curr_king[0]); temp_move_list.push_back(curr_king[1]);
            }
            for(int i=0;i<elig_squares.size();i+=2){
                if(is_pinned(elig_squares[i],elig_squares[i+1],b)){
                    if(copy==checker){      //The piece isnt actually pinned since the number of checkers wont change if that square is assumed to be vaccant
                        temp_move_list.push_back(elig_squares[i]);
                        temp_move_list.push_back(elig_squares[i + 1]);
                    }
                }
            }
            for(int i=0;i<interceptors.size();i+=2){
                if(is_pinned(interceptors[i],interceptors[i+1],b)){     //Always true since king would be in check regardless of the pin
                    if(copy==checker){
                        temp_move_list.push_back(interceptors[i]);
                        temp_move_list.push_back(interceptors[i + 1]);
                    }
                }
            }
            char inp[3],inp1[3];
            while(cin){
                cout<<"King in check. Enter selection square: "<<endl;
                cin>>inp;
                if(cin.fail()){         //FIXME !!!
                    cout<<"Error in input."<<endl;
                    cin.clear();cin.ignore('\n');
                }
                int count = 0;
                for(int i = 0;i<temp_move_list.size();i++){
                    if(fabs(inp[1]-49-7) == temp_move_list[i]&&inp[0]-97==temp_move_list[i+1]){
                        count++;
                    }
                    i++;
                }
                if(count){
                    break;      //breaks the while loop
                }
                cout<<"Invalid Square, select square from valid moves list"<<endl;
                print_moves(temp_move_list);
            }
            cor[1] = (int)inp[0]-97; cor[0] = fabs(inp[1] - 49-7);
            //Making move
            temp_move_list.clear();  //Will now be used for making the move ie destination square
            bool king = 0;  //To check if king was moved, if yes then his position has to be updated
            if(b.board_matrix[cor[0]][cor[1]][0]=='K'){     //If king is selected then his moves are given
                temp_move_list = k.move_list;
                king = true;
            }
            else{
                //To determine whether the piece can intercept or capture checker, sometimes a piece can do both
                for(int i = 0; i<interceptors.size();i+=2){
                    if(interceptors[i] == cor[0] && interceptors[i+1]==cor[1]){     //Piece selected has to intercept
                        vector <int> w_mov;
                        switch(b.board_matrix[cor[0]][cor[1]][0]){
                            case 'Q':{
                                Queen U_P;
                                U_P.get_moves(cor[0],cor[1],b);
                                w_mov = U_P.move_list;
                                break;}
                            case 'B':{
                                Bishop U_P;
                                U_P.get_moves(cor[0],cor[1],b);
                                w_mov = U_P.move_list;
                                break;}
                            case 'R':{
                                Rook U_P;
                                U_P.get_moves(cor[0],cor[1],b);
                                w_mov = U_P.move_list;
                                break;}
                            case 'P':{
                                Pawn U_P;
                                U_P.get_moves(cor[0],cor[1],b);
                                w_mov = U_P.move_list;
                                break;}
                            case 'N':{
                                Knight U_P;
                                U_P.get_moves(cor[0],cor[1],b);
                                w_mov = U_P.move_list;
                                break;}
                        }
                        for(int j = 0;j<w_mov.size();j+=2){
                            string t = b.board_matrix[w_mov[j]][w_mov[j+1]];        //Value holder for original value of the square
                            b.board_matrix[w_mov[j]][w_mov[j+1]] = b.board_matrix[cor[0]][cor[1]];      //Putting that piece in the square
                            if(!in_check(curr_king[0],curr_king[1],b)){     //If that move results in escaping from check
                                temp_move_list.push_back(w_mov[j]);temp_move_list.push_back(w_mov[j+1]);
                            }
                            //Undoing the changing of the board matrix
                            b.board_matrix[w_mov[j]][w_mov[j+1]] = t;
                        }
                    }
                }
                for(int i = 0;i<elig_squares.size();i+=2){
                    if(elig_squares[i] == cor[0] && elig_squares[i+1] == cor[1]){
                        //checking if the move is already added to the list
                        bool added = false;
                        for(int l = 0;l<temp_move_list.size();l+=2){
                            if(temp_move_list[l] == copy[0] && temp_move_list[l+1]==copy[1]){
                                added = true;
                                break;
                            }
                        }
                        if(!added) {
                            temp_move_list.push_back(copy[0]);
                            temp_move_list.push_back(copy[1]);
                        }
                        break;
                    }
                }
            }
            while(cin){
                cout<<"Enter destination square: "<<endl;
                cin>>inp1;
                int count = 0;
                for(int i = 0;i<temp_move_list.size();i+=2){
                    if(fabs(inp1[1]-49-7) == temp_move_list[i]&&inp1[0]-97==temp_move_list[i+1]){
                        count++;
                    }
                }
                if(count){
                    break;      //breaks the while loop
                }
                cout<<"Invalid Square, select square from valid moves list"<<endl;
                print_moves(temp_move_list);
            }
            des[1] = inp1[0] - 97;
            des[0] = fabs(inp1[1] - 49-7);
            if(king) {              //updating king position
                if (b.turn) {
                    b_k_pos[0] = des[0];
                    b_k_pos[1] = des[1];
                    b_k_c = 0;  //black king can't castle anymore
                } else {
                    w_k_pos[0] = des[0];
                    w_k_pos[1] = des[1];
                    w_k_c = 0;  //white king can't castle anymore
                }
            }
            b.board_matrix[des[0]][des[1]] = b.board_matrix[cor[0]][cor[1]]; b.board_matrix[cor[0]][cor[1]] = "LI";
            moves.push_back(cor[0]); moves.push_back(cor[1]); moves.push_back(des[0]); moves.push_back(des[1]);
            if(promotion(b)){
                char input;
                cout<<"What piece would you like to promote to? \nEnter 'N' for knight, 'Q' for Queen, 'B' for Bishop & 'R' for Rook"<<endl;
                cin>>input;
                while(input != 'N' && input != 'R' && input!= 'Q' && input != 'B'){
                    cout<<"Invalid piece."<<endl;
                    cout<<"Enter 'N' for knight, 'Q' for Queen, 'B' for Bishop & 'R' for Rook"<<endl;
                }
                b.board_matrix[prom_sq[0]][prom_sq[1]][0] = input;
            }
            b.turn = (b.turn) ? 0 : 1;
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
#pragma clang diagnostic pop