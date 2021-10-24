/*
 * Author: Dhroov Pandey
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//CONSTANT VARIABLES
const int row_size = 8, col_size = 8;

//COORDINATE OF CURRENT SQUARE & DESTINATION SQUARE
int cor[2] = {0},des[2] = {0};  //format for cor -> (row,col) same for des

//structure of board and turn
struct board{
    string board_matrix[row_size][col_size] ;
    bool turn = 0;
};

//FUNCTION DECLARATIONS

void display_board(const board& b);
void constructor_board(board& b);
void get_square(const board& b);
bool is_valid(int row,int col,const board& b);
void make_move(board& b);
void print_moves(vector<int> x);
void print_all_game_moves();
bool in_check(int r,int c,const board& b);

//Moves Database
vector <int> moves;      //TO BE PRINTED AT THE END OF THE GAME

//HEADER FILE
#include "Pieces_logic.h"
#include "King.h"

//MAIN FUNCTION
int main() {
    board b;
    constructor_board(b);
    while(cin){
        display_board(b);
        get_square(b);
        make_move(b);
        print_all_game_moves();
    }
    return 0;
}

//FUNCTION DEFINITIONS
void display_board(const board& b){
    cout<<"Board: "<<endl;
    cout<<"\tWhite End"<<endl;
    for(auto& i: b.board_matrix){
        for(string j: i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"\tBlack End"<<endl;
    string t = (b.turn)? "BLACK":"WHITE";
    cout<<"Turn of :"<<t<<endl;
}

void constructor_board(board& b){
    //initializing blank board
    for(int i = 0;i< row_size;i++){
        for(int j = 0;j<col_size;j++){
            b.board_matrix[i][j] = "LI";
        }
    }
    //white pieces setup
    b.board_matrix[0][0] = "Rw";
    b.board_matrix[0][1] = "Nw";
    b.board_matrix[0][2] = "Bw";
    b.board_matrix[0][3] = "Kw";
    b.board_matrix[0][4] = "Qw";
    b.board_matrix[0][5] = "Bw";
    b.board_matrix[0][6] = "Nw";
    b.board_matrix[0][7] = "Rw";
    for(int i = 0;i<col_size;i++){
        b.board_matrix[1][i] = "Pw";
    }
    //black pieces setup
    b.board_matrix[7][0] = "Rb";
    b.board_matrix[7][1] = "Nb";
    b.board_matrix[7][2] = "Bb";
    b.board_matrix[7][3] = "Kb";
    b.board_matrix[7][4] = "Qb";
    b.board_matrix[7][5] = "Bb";
    b.board_matrix[7][6] = "Nb";
    b.board_matrix[7][7] = "Rb";
    for(int i = 0;i<col_size;i++){
        b.board_matrix[6][i] = "Pb";
    }
}

void get_square(const board& b){
    do{
        cout<<"Enter selection square: "<<endl;
        char inp[3];
        cin>>inp;
        cor[1] = inp[0]-97; cor[0] = inp[1] - 49;
        char t = (b.turn)? 'b':'w';
        vector<int> temp_move_list;     //this list checks whether the selected piece has any valid moves
        switch(b.board_matrix[cor[0]][cor[1]][0]){
            case 'Q':{
                Queen U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'B':{
                Bishop U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'R':{
                Rook U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'P':{
                Pawn U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'N':{
                Knight U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
                case 'K':{
                    King U_P;
                    U_P.get_moves(cor[0],cor[1],b);
                    temp_move_list = U_P.move_list;
                }
        }
        if(b.board_matrix[cor[0]][cor[1]][1] != t){
            cout<<"Invalid Square"<<endl;
        }
        else if(temp_move_list.size()==0){
            cout<<"No Valid moves for the piece on that square"<<endl;
        }
        else{
            break;
        }
    }
    while(cin);
}

bool is_valid(int row,int col,const board& b){
    if(!(row>=0 && row<row_size &&col>=0 && col<col_size)){
        return false;
    }
    char t = (b.turn)? 'b':'w';
    if(b.board_matrix[row][col][1] == t){
        return false;
    }
    return true;
}

void make_move(board& b){
    cout<<"Enter destination square"<<endl;
    char inp[3];
    while(cin) {
        cin >> inp;
        vector<int> temp_move_list;
        switch(b.board_matrix[cor[0]][cor[1]][0]){
            case 'Q':{
                Queen U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'B':{
                Bishop U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'R':{
                Rook U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'P':{
                Pawn U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
            case 'N':{
                Knight U_P;
                U_P.get_moves(cor[0],cor[1],b);
                temp_move_list = U_P.move_list;
                break;}
        }
        int count = 0;
        for(int i = 0;i<temp_move_list.size();i++){
            if(inp[1]-49 == temp_move_list[i]&&inp[0]-97==temp_move_list[i+1]){
                count++;
            }
            i++;
        }
        if(count){
            break;
        }
        cout<<"Invalid Square, select square from valid moves list"<<endl;
        print_moves(temp_move_list);
    }
    des[1] = inp[0] - 97;
    des[0] = inp[1] - 49;
    b.board_matrix[des[0]][des[1]] = b.board_matrix[cor[0]][cor[1]]; b.board_matrix[cor[0]][cor[1]] = "LI";
    moves.push_back(cor[0]); moves.push_back(cor[1]); moves.push_back(des[0]); moves.push_back(des[1]);
    b.turn = (b.turn) ? 0 : 1;
}

void print_moves(vector<int> x){
    cout<<"Valid Moves are: "<<endl;
    char file;
    int rank;
    int loop_var = 0;
    while(loop_var<x.size()){
        file = static_cast<char>(x[loop_var+1]+97);
        rank = x[loop_var] + 1;
        cout<<file<<rank<<" ";
        loop_var+=2;
    }
    cout<<endl;
}

void print_all_game_moves(){
    int loop_var = 0;
    while(loop_var<moves.size()){
        printf("%c%d to %c%d\n", moves[loop_var+1]+97,moves[loop_var]+1,moves[loop_var+3]+97,moves[loop_var+2]+1);
        loop_var+=4;
    }
}

bool in_check(const int r,const int c,const board& b){
    char turn_opp = (b.turn)? 'w':'b';      //gives the opposite piece
    int adder = 1;
    //checking for bishop and queen
    while(b.board_matrix[r+adder][c+adder]=="LI"){
        adder++;
    }
    if(is_valid(r+adder,c+adder,b)){
        if((b.board_matrix[r+adder][c+adder][0] == 'B' || b.board_matrix[r+adder][c+adder][0] == 'Q')&&b.board_matrix[r+adder][c+adder][1]==turn_opp){
            return true;
        }
    }
    adder = 1;
    while(b.board_matrix[r+adder][c-adder]=="LI"){
        adder++;
    }
    if(is_valid(r+adder,c-adder,b)){
        if((b.board_matrix[r+adder][c-adder][0] == 'B' || b.board_matrix[r+adder][c-adder][0] == 'Q')&&b.board_matrix[r+adder][c-adder][1]==turn_opp){
            return true;
        }
    }
    adder = 1;
    while(b.board_matrix[r-adder][c+adder]=="LI"){
        adder++;
    }
    if(is_valid(r-adder,c+adder,b)){
        if((b.board_matrix[r-adder][c+adder][0] == 'B' || b.board_matrix[r-adder][c+adder][0] == 'Q')&&b.board_matrix[r-adder][c+adder][1]==turn_opp){
            return true;
        }
    }
    adder = 1;
    while(b.board_matrix[r-adder][c-adder]=="LI"){
        adder++;
    }
    if(is_valid(r-adder,c-adder,b)){
        if((b.board_matrix[r-adder][c-adder][0] == 'B' || b.board_matrix[r-adder][c-adder][0] == 'Q')&&b.board_matrix[r-adder][c-adder][1]==turn_opp){
            return true;
        }
    }
    //checking for Rook
    adder = 1;
    while(b.board_matrix[r][c+adder]=="LI"){
        adder++;
    }
    if(is_valid(r,c+adder,b)){
        if((b.board_matrix[r][c+adder][0] == 'R' || b.board_matrix[r][c+adder][0] == 'Q')&&b.board_matrix[r][c+adder][1]==turn_opp){
            return true;
        }
    }
    adder = 1;
    while(b.board_matrix[r][c-adder]=="LI"){
        adder++;
    }
    if(is_valid(r,c-adder,b)){
        if((b.board_matrix[r][c-adder][0] == 'R' || b.board_matrix[r][c-adder][0] == 'Q')&&b.board_matrix[r][c-adder][1]==turn_opp){
            return true;
        }
    }
    adder = 1;
    while(b.board_matrix[r+adder][c]=="LI"){
        adder++;
    }
    if(is_valid(r+adder,c,b)){
        if((b.board_matrix[r+adder][c][0] == 'R' || b.board_matrix[r+adder][c][0] == 'Q')&&b.board_matrix[r+adder][c][1]==turn_opp){
            return true;
        }
    }
    adder = 1;
    while(b.board_matrix[r-adder][c]=="LI"){
        adder++;
    }
    if(is_valid(r-adder,c,b)){
        if((b.board_matrix[r-adder][c][0] == 'R' || b.board_matrix[r-adder][c][0] == 'Q')&&b.board_matrix[r-adder][c][1]==turn_opp){
            return true;
        }
    }
    //checking for knight
    if(is_valid(r+2,c+1,b)){
        if((b.board_matrix[r+2][c+1][0] == 'N')&&b.board_matrix[r+2][c+1][1]==turn_opp){
            return true;
        }
    }
    if(is_valid(r+2,c-1,b)){
        if((b.board_matrix[r+2][c-1][0] == 'N')&&b.board_matrix[r+2][c-1][1]==turn_opp){
            return true;
        }
    }
    if(is_valid(r-2,c+1,b)){
        if((b.board_matrix[r-2][c+1][0] == 'N')&&b.board_matrix[r-2][c+1][1]==turn_opp){
            return true;
        }
    }
    if(is_valid(r-2,c-1,b)){
        if((b.board_matrix[r-2][c-1][0] == 'N')&&b.board_matrix[r-2][c-1][1]==turn_opp){
            return true;
        }
    }
    if(is_valid(r+1,c+2,b)){
        if((b.board_matrix[r+1][c+2][0] == 'N')&&b.board_matrix[r+1][c+2][1]==turn_opp){
            return true;
        }
    }
    if(is_valid(r-1,c+2,b)){
        if((b.board_matrix[r-1][c+2][0] == 'N')&&b.board_matrix[r-1][c+2][1]==turn_opp){
            return true;
        }
    }
    if(is_valid(r+1,c-2,b)){
        if((b.board_matrix[r+1][c-2][0] == 'N')&&b.board_matrix[r+1][c-2][1]==turn_opp){
            return true;
        }
    }
    if(is_valid(r-1,c-2,b)){
        if((b.board_matrix[r-1][c-2][0] == 'N')&&b.board_matrix[r-1][c-2][1]==turn_opp){
            return true;
        }
    }
    //checking for pawns

    return false;
}

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
 * description: determines whether a square on board matrix will be in check from the enemy pieces
 */