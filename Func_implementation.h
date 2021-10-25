inline void display_board(const board& b){
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

inline void constructor_board(board& b){
    //initializing blank board
    for(int i = 0;i< row_size;i++){
        for(int j = 0;j<col_size;j++){
            b.board_matrix[i][j] = "LI";
        }
    }
    //white pieces setup
    b.board_matrix[0][0] = "Rb";
    b.board_matrix[0][1] = "Nb";
    b.board_matrix[0][2] = "Bb";
    b.board_matrix[0][3] = "Qb";
    b.board_matrix[0][4] = "Kb";
    b.board_matrix[0][5] = "Bb";
    b.board_matrix[0][6] = "Nb";
    b.board_matrix[0][7] = "Rb";
    for(int i = 0;i<col_size;i++){
        b.board_matrix[1][i] = "Pb";
    }
    //black pieces setup
    b.board_matrix[7][0] = "Rw";
    b.board_matrix[7][1] = "Nw";
    b.board_matrix[7][2] = "Bw";
    b.board_matrix[7][3] = "Qw";
    b.board_matrix[7][4] = "Kw";
    b.board_matrix[7][5] = "Bw";
    b.board_matrix[7][6] = "Nw";
    b.board_matrix[7][7] = "Rw";
    for(int i = 0;i<col_size;i++){
        b.board_matrix[6][i] = "Pw";
    }
}

inline void get_square(const board& b){
    do{
        cout<<"Enter selection square: "<<endl;
        char inp[3];
        cin>>inp;
        cor[1] = inp[0]-97; cor[0] = fabs(inp[1] - 49-7);
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

inline bool is_valid(int row,int col,const board& b){
    if(!(row>=0 && row<row_size &&col>=0 && col<col_size)){
        return false;
    }
    char t = (b.turn)? 'b':'w';
    if(b.board_matrix[row][col][1] == t){
        return false;
    }
    return true;
}

inline void make_move(board& b){
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
            if(fabs(inp[1]-49-7) == temp_move_list[i]&&inp[0]-97==temp_move_list[i+1]){
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
    des[0] = fabs(inp[1] - 49-7);
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
        rank = fabs(x[loop_var] -8);
        cout<<file<<rank<<" ";
        loop_var+=2;
    }
    cout<<endl;
}

inline void print_all_game_moves(){
    int loop_var = 0;
    while(loop_var<moves.size()){
        printf("%c%d to %c%d\n", moves[loop_var+1]+97,(int)fabs(moves[loop_var]-8),moves[loop_var+3]+97,(int)fabs(moves[loop_var+2]-8));  //-8 to fix the lateral inversion of alphabetic notation on the board
        loop_var+=4;
    }
}

inline bool in_check(const int r,const int c,const board& b){
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