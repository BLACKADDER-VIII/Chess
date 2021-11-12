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
    //black pieces setup
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
    //white pieces setup
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

void get_square(const board& b){
    do{
        cout<<"Enter selection square: "<<endl;
        char inp[3];
        cin>>inp;
        cor[1] = (int)inp[0]-97; cor[0] = fabs(inp[1] - 49-7);
        if(is_pinned(cor[0],cor[1],b)){
            cout<<"Pinned Piece"<<endl;
            continue;
        }
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
    bool king;
    while(cin) {
        king = 0;
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
                case 'K' : {
                    King U_P;
                    U_P.get_moves(cor[0],cor[1],b);
                    temp_move_list = U_P.move_list;
                    king = 1;
                    break;
                }
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
    des[1] = inp[0] - 97;
    des[0] = fabs(inp[1] - 49-7);
    if(king) {              //updating king position
        if (b.turn) {
            b_k_pos[0] = des[0];
            b_k_pos[1] = des[1];
        } else {
            w_k_pos[0] = des[0];
            w_k_pos[1] = des[1];
        }
    }
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

void print_all_game_moves(){
    int loop_var = 0;
    while(loop_var<moves.size()){
        printf("%c%d to %c%d\n", moves[loop_var+1]+97,(int)fabs(moves[loop_var]-8),moves[loop_var+3]+97,(int)fabs(moves[loop_var+2]-8));  //-8 to fix the lateral inversion of alphabetic notation on the board
        loop_var+=4;
    }
}

bool in_check(const int r,const int c,const board& b){
    int cond = 0;
    char turn_opp = (b.turn)? 'w':'b';      //gives the opposite piece
    int adder = 1;
    //checking for bishop and queen
    while(b.board_matrix[r+adder][c+adder]=="LI"){
        adder++;
    }
    if(is_valid(r+adder,c+adder,b)){
        if((b.board_matrix[r+adder][c+adder][0] == 'B' || b.board_matrix[r+adder][c+adder][0] == 'Q')&&b.board_matrix[r+adder][c+adder][1]==turn_opp){
            checker.push_back(r+adder);checker.push_back(c+adder);     //updates checker
            cond++;
        }
    }
    adder = 1;
    while(b.board_matrix[r+adder][c-adder]=="LI"){
        adder++;
    }
    if(is_valid(r+adder,c-adder,b)){
        if((b.board_matrix[r+adder][c-adder][0] == 'B' || b.board_matrix[r+adder][c-adder][0] == 'Q')&&b.board_matrix[r+adder][c-adder][1]==turn_opp){
            checker.push_back(r+adder);checker.push_back(c-adder);
            cond++;
        }
    }
    adder = 1;
    while(b.board_matrix[r-adder][c+adder]=="LI"){
        adder++;
    }
    if(is_valid(r-adder,c+adder,b)){
        if((b.board_matrix[r-adder][c+adder][0] == 'B' || b.board_matrix[r-adder][c+adder][0] == 'Q')&&b.board_matrix[r-adder][c+adder][1]==turn_opp){
            checker.push_back(r-adder);checker.push_back(c+adder);
            cond++;
        }
    }
    adder = 1;
    while(b.board_matrix[r-adder][c-adder]=="LI"){
        adder++;
    }
    if(is_valid(r-adder,c-adder,b)){
        if((b.board_matrix[r-adder][c-adder][0] == 'B' || b.board_matrix[r-adder][c-adder][0] == 'Q')&&b.board_matrix[r-adder][c-adder][1]==turn_opp){
            checker.push_back(r-adder);checker.push_back(c-adder);
            cond++;
        }
    }
    //checking for Rook&Queen
    adder = 1;
    while(b.board_matrix[r][c+adder]=="LI"){
        adder++;
    }
    if(is_valid(r,c+adder,b)){
        if((b.board_matrix[r][c+adder][0] == 'R' || b.board_matrix[r][c+adder][0] == 'Q')&&b.board_matrix[r][c+adder][1]==turn_opp){
            checker.push_back(r);checker.push_back(c+adder);
            cond++;
        }
    }
    adder = 1;
    while(b.board_matrix[r][c-adder]=="LI"){
        adder++;
    }
    if(is_valid(r,c-adder,b)){
        if((b.board_matrix[r][c-adder][0] == 'R' || b.board_matrix[r][c-adder][0] == 'Q')&&b.board_matrix[r][c-adder][1]==turn_opp){
            checker.push_back(r);checker.push_back(c-adder);
            cond++;
        }
    }
    adder = 1;
    while(b.board_matrix[r+adder][c]=="LI"){
        adder++;
    }
    if(is_valid(r+adder,c,b)){
        if((b.board_matrix[r+adder][c][0] == 'R' || b.board_matrix[r+adder][c][0] == 'Q')&&b.board_matrix[r+adder][c][1]==turn_opp){
            checker.push_back(r+adder);checker.push_back(c);
            cond++;
        }
    }
    adder = 1;
    while(b.board_matrix[r-adder][c]=="LI"){
        adder++;
    }
    if(is_valid(r-adder,c,b)){
        if((b.board_matrix[r-adder][c][0] == 'R' || b.board_matrix[r-adder][c][0] == 'Q')&&b.board_matrix[r-adder][c][1]==turn_opp){
            checker.push_back(r-adder);checker.push_back(c);
            cond++;
        }
    }
    //checking for knight
    if(is_valid(r+2,c+1,b)){
        if((b.board_matrix[r+2][c+1][0] == 'N')&&b.board_matrix[r+2][c+1][1]==turn_opp){
            checker.push_back(r+2);checker.push_back(c+1);
            cond++;
        }
    }
    if(is_valid(r+2,c-1,b)){
        if((b.board_matrix[r+2][c-1][0] == 'N')&&b.board_matrix[r+2][c-1][1]==turn_opp){
            checker.push_back(r+2);checker.push_back(c-1);
            cond++;
        }
    }
    if(is_valid(r-2,c+1,b)){
        if((b.board_matrix[r-2][c+1][0] == 'N')&&b.board_matrix[r-2][c+1][1]==turn_opp){
            checker.push_back(r-2);checker.push_back(c+1);
            cond++;
        }
    }
    if(is_valid(r-2,c-1,b)){
        if((b.board_matrix[r-2][c-1][0] == 'N')&&b.board_matrix[r-2][c-1][1]==turn_opp){
            checker.push_back(r-2);checker.push_back(c-1);
            cond++;
        }
    }
    if(is_valid(r+1,c+2,b)){
        if((b.board_matrix[r+1][c+2][0] == 'N')&&b.board_matrix[r+1][c+2][1]==turn_opp){
            checker.push_back(r+1);checker.push_back(c+2);
            cond++;
        }
    }
    if(is_valid(r-1,c+2,b)){
        if((b.board_matrix[r-1][c+2][0] == 'N')&&b.board_matrix[r-1][c+2][1]==turn_opp){
            checker.push_back(r-1);checker.push_back(c+2);
            cond++;
        }
    }
    if(is_valid(r+1,c-2,b)){
        if((b.board_matrix[r+1][c-2][0] == 'N')&&b.board_matrix[r+1][c-2][1]==turn_opp){
            checker.push_back(r+1);checker.push_back(c-2);
            cond++;
        }
    }
    if(is_valid(r-1,c-2,b)){
        if((b.board_matrix[r-1][c-2][0] == 'N')&&b.board_matrix[r-1][c-2][1]==turn_opp){
            checker.push_back(r-1);checker.push_back(c-2);
            cond++;
        }
    }
    //FIXME checking for pawns
    if(b.turn) {
        if (is_valid(r + 1, c - 1, b)) {
            if ((b.board_matrix[r + 1][c - 1][0] == 'P') && b.board_matrix[r + 1][c - 1][1] == 'w') {
                checker.push_back(r + 1);
                checker.push_back(c - 1);
                cond++;
            }
        }
        if (is_valid(r + 1, c + 1, b)) {
            if (b.board_matrix[r + 1][c + 1][0] == 'P' && b.board_matrix[r + 1][c + 1][1] == 'w') {
                checker.push_back(r + 1);
                checker.push_back(c + 1);
                cout<<"Entered"<<endl;
                cond++;
            }
        }
    }

    else{
        if (is_valid(r - 1, c - 1, b)) {
            if ((b.board_matrix[r - 1][c - 1][0] == 'P') && b.board_matrix[r - 1][c - 1][1] == 'b') {
                checker.push_back(r - 1);
                checker.push_back(c - 1);
                cond++;
            }
        }
        if (is_valid(r - 1, c + 1, b)) {
            if ((b.board_matrix[r - 1][c + 1][0] == 'P') && b.board_matrix[r - 1][c + 1][1] == 'b') {
                checker.push_back(r - 1);
                checker.push_back(c + 1);
                cond++;
            }
        }
    }
    return cond;
}

bool checker_capturable(vector<int> copy,board b){
    checker.clear();
    b.turn = (b.turn)? 0:1;
    if(in_check(copy[0],copy[1],b)){
    }
    elig_squares = checker;
    return elig_squares.size();
}

bool is_pinned(int row,int col,board b){
    b.board_matrix[row][col] = "LI";
    int curr[2];
    if(b.turn){
        curr[0] = b_k_pos[0],curr[1] = b_k_pos[1];
    }
    else{
        curr[0] = w_k_pos[0],curr[1] = w_k_pos[1];
    }
    if(in_check(curr[0],curr[1],b)&&!(curr[0]==row&&curr[1]==col)){
        return true;
    }
    return false;
}

inline bool intercept(int k_r,int k_c,int ch_r,int ch_c,board b){       //FIXME !!! ADD PAWN CONDITIONS
    interceptors.clear();
    checker.clear();
    b.turn = (b.turn)? 0:1;
    vector<int> pawns;
    // For Bishop and Queen
    if(b.board_matrix[ch_r][ch_c][0]=='B'||b.board_matrix[ch_r][ch_c][0]=='Q'){
        //4 possible directions of attack
        if(ch_r>k_r&&ch_c>k_c){
            int diff = ch_r-k_r;
            for(int i = 1;i<diff;i++){
                if(in_check(k_r+i,k_c+i,b)){
                }
                if(!b.turn){
                    if(b.board_matrix[k_r+i-1][k_c+i]=="Pb"){
                        pawns.push_back(k_r+i-1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r+i-2][k_c+i]=="Pb"){
                        pawns.push_back(k_r+i-2);pawns.push_back(k_c+i);
                    }
                }
                else{
                    if(b.board_matrix[k_r+i+1][k_c+i]=="Pw"){
                        pawns.push_back(k_r+i+1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r+i+2][k_c+i]=="Pw"){
                        pawns.push_back(k_r+i+2);pawns.push_back(k_c+i);
                    }
                }
            }
        }
        if(ch_r>k_r&&ch_c<k_c){
            int diff = ch_r-k_r;
            for(int i = 1;i<diff;i++){
                if(in_check(k_r+i,k_c-i,b)){
                }
                if(!b.turn){
                    if(b.board_matrix[k_r+i-1][k_c+i]=="Pb"){
                        pawns.push_back(k_r+i-1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r+i-2][k_c+i]=="Pb"){
                        pawns.push_back(k_r+i-2);pawns.push_back(k_c+i);
                    }
                }
                else{
                    if(b.board_matrix[k_r+i+1][k_c+i]=="Pw"){
                        pawns.push_back(k_r+i+1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r+i+2][k_c+i]=="Pw"){
                        pawns.push_back(k_r+i+2);pawns.push_back(k_c+i);
                    }
                }
            }
        }
        if(ch_r<k_r&&ch_c>k_c){
            int diff = (ch_r-k_r)*-1;
            for(int i = 1;i<diff;i++){
                if(in_check(k_r-i,k_c+i,b)){
                }
                if(!b.turn){
                    if(b.board_matrix[k_r-i-1][k_c+i]=="Pb"){
                        pawns.push_back(k_r-i-1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r-i-2][k_c+i]=="Pb"){
                        pawns.push_back(k_r-i-2);pawns.push_back(k_c+i);
                    }
                }
                else{
                    if(b.board_matrix[k_r-i+1][k_c+i]=="Pw"){
                        pawns.push_back(k_r-i+1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r-i+2][k_c+i]=="Pw"){
                        pawns.push_back(k_r-i+2);pawns.push_back(k_c+i);
                    }
                }
            }
        }
        if(ch_r<k_r&&ch_c<k_c){
            int diff = (ch_r-k_r)*-1;
            for(int i = 1;i<diff;i++){
                if(in_check(k_r-i,k_c-i,b)){
                }
                if(!b.turn){
                    if(b.board_matrix[k_r-i-1][k_c+i]=="Pb"){
                        pawns.push_back(k_r-i-1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r-i-2][k_c+i]=="Pb"){
                        pawns.push_back(k_r-i-2);pawns.push_back(k_c+i);
                    }
                }
                else{
                    if(b.board_matrix[k_r-i+1][k_c+i]=="Pw"){
                        pawns.push_back(k_r-i+1);pawns.push_back(k_c+i);
                    }
                    if(b.board_matrix[k_r-i+2][k_c+i]=="Pw"){
                        pawns.push_back(k_r-i+2);pawns.push_back(k_c+i);
                    }
                }
            }
        }
    }
    //For rook and queen
    else if(b.board_matrix[ch_r][ch_c][0]=='R'||b.board_matrix[ch_r][ch_c][0]=='Q'){    //FIXME ADD PAWN CHECKING
        //4 directions of attack
        if(ch_c>k_c){
            int diff = ch_c-k_c;
            for(int i = 1;i<diff;i++){
                if(in_check(k_r,k_c+i,b)){
                }
            }
        }
        if(ch_c<k_c){
            int diff = (ch_c-k_c)*-1;
            for(int i = 1;i<diff;i++){
                if(in_check(k_r,k_c-i,b)){
                }
            }
        }
        if(ch_r<k_r){
            int diff = (ch_r-k_r)*-1;
            for(int i = 1;i<diff;i++){
                if(in_check(k_r-i,k_c,b)){
                }
            }
        }
        if(ch_r>k_r){
            int diff = (ch_r-k_r);
            for(int i = 1;i<diff;i++){
                if(in_check(k_r+i,k_c,b)){
                }
            }
        }
    }
    for(int i = 0;i<checker.size();i+=2){
        if(b.board_matrix[checker[i]][checker[i+1]][0]!='P'){       //checker contains diagonal pawn move and hence can't be used for interception
            interceptors.push_back(checker[i]);interceptors.push_back(checker[i+1]);
        }
    }
    for(int i:pawns){
        interceptors.push_back(i);
    }
    return interceptors.size();
}