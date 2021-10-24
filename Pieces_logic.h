class Knight{
public:
    vector<int> move_list;
    void get_moves(int r,int c,const board& b){
        if(is_valid(r+2,c+1,b)){
            move_list.push_back(r+2); move_list.push_back(c+1);
        }
        if(is_valid(r+2,c-1,b)){
            move_list.push_back(r+2); move_list.push_back(c-1);
        }
        if(is_valid(r-2,c+1,b)){
            move_list.push_back(r-2); move_list.push_back(c+1);
        }
        if(is_valid(r-2,c-1,b)){
            move_list.push_back(r-2); move_list.push_back(c-1);
        }
        if(is_valid(r+1,c+2,b)){
            move_list.push_back(r+1); move_list.push_back(c+2);
        }
        if(is_valid(r+1,c-2,b)){
            move_list.push_back(r+1); move_list.push_back(c-2);
        }
        if(is_valid(r-1,c+2,b)){
            move_list.push_back(r-1); move_list.push_back(c+2);
        }
        if(is_valid(r-1,c-2,b)){
            move_list.push_back(r-1); move_list.push_back(c-2);
        }
    }
    void reset(){
        move_list.clear();
    }

private:
};

class Rook{
public:
    vector<int> move_list;
    void reset(){
        move_list.clear();
    }
    void get_moves(int r,int c,const board& b){
        char t = (b.turn)? 'w':'b';     //it will be the opposite piece here
        for(int i = c+1; is_valid(r,i,b);i++){
            move_list.push_back(r);
            move_list.push_back(i);
            if(b.board_matrix[r][i][1]==t){
                break;
            }
        }
        for(int i = c-1; is_valid(r,i,b);i--){
            move_list.push_back(r);
            move_list.push_back(i);
            if(b.board_matrix[r][i][1]==t){
                break;
            }
        }
        for(int i = r+1; is_valid(i,c,b);i++){
            move_list.push_back(i);
            move_list.push_back(c);
            if(b.board_matrix[i][c][1]==t){
                break;
            }
        }
        for(int i = r-1; is_valid(i,c,b);i--){
            move_list.push_back(i);
            move_list.push_back(c);
            if(b.board_matrix[i][c][1]==t){
                break;
            }
        }
    }
private:
};

class Bishop{
public:
    vector <int> move_list;
    void reset(){
        move_list.clear();
    }
    void get_moves(int r,int c,const board& b){
        int curr_r;
        char t = (b.turn)? 'w':'b';     //it will be the opposite piece here
        curr_r=r;
        for(int i = c+1; is_valid(curr_r+1,i,b);i++){
            move_list.push_back(curr_r+1);
            move_list.push_back(i);
            if(b.board_matrix[curr_r+1][i][1]==t){
                break;
            }
            curr_r++;
        }
        curr_r=r;
        for(int i = c-1; is_valid(curr_r+1,i,b);i--){
            move_list.push_back(curr_r+1);
            move_list.push_back(i);
            if(b.board_matrix[curr_r+1][i][1]==t){
                break;
            }
            curr_r++;
        }
        curr_r=r;
        for(int i = c+1; is_valid(curr_r-1,i,b);i++){
            move_list.push_back(curr_r+1);
            move_list.push_back(i);
            if(b.board_matrix[curr_r-1][i][1]==t){
                break;
            }
            curr_r--;
        }
        curr_r=r;
        for(int i = c-1; is_valid(curr_r-1,i,b);i--){
            move_list.push_back(curr_r+1);
            move_list.push_back(i);
            if(b.board_matrix[curr_r-1][i][1]==t){
                break;
            }
            curr_r--;
        }
    }

private:
};

class Queen{
public:
    vector<int> move_list;
    void reset(){
        move_list.clear();
    }
    void get_moves(int r,int c,const board& b){
        char t = (b.turn)? 'w':'b';     //it will be the opposite piece here
        for(int i = c+1; is_valid(r,i,b);i++){
            move_list.push_back(r);
            move_list.push_back(i);
            if(b.board_matrix[r][i][1]==t){
                break;
            }
        }
        for(int i = c-1; is_valid(r,i,b);i--){
            move_list.push_back(r);
            move_list.push_back(i);
            if(b.board_matrix[r][i][1]==t){
                break;
            }
        }
        for(int i = r+1; is_valid(i,c,b);i++){
            move_list.push_back(i);
            move_list.push_back(c);
            if(b.board_matrix[i][c][1]==t){
                break;
            }
        }
        for(int i = r-1; is_valid(i,c,b);i--){
            move_list.push_back(i);
            move_list.push_back(c);
            if(b.board_matrix[i][c][1]==t){
                break;
            }
        }
    int curr_r;
    curr_r=r;
    for(int i = c+1; is_valid(curr_r+1,i,b);i++){
        move_list.push_back(curr_r+1);
        move_list.push_back(i);
        if(b.board_matrix[curr_r+1][i][1]==t){
            break;
        }
        curr_r++;
    }
    curr_r=r;
    for(int i = c-1; is_valid(curr_r+1,i,b);i--){
        move_list.push_back(curr_r+1);
        move_list.push_back(i);
        if(b.board_matrix[curr_r+1][i][1]==t){
            break;
        }
        curr_r++;
    }
    curr_r=r;
    for(int i = c+1; is_valid(curr_r-1,i,b);i++){
        move_list.push_back(curr_r+1);
        move_list.push_back(i);
        if(b.board_matrix[curr_r-1][i][1]==t){
            break;
        }
        curr_r--;
    }
    curr_r=r;
    for(int i = c-1; is_valid(curr_r-1,i,b);i--){
        move_list.push_back(curr_r+1);
        move_list.push_back(i);
        if(b.board_matrix[curr_r-1][i][1]==t){
            break;
        }
        curr_r--;
    }
}
private:
};

class Pawn{     //!!!!FIXME : ADD EN PASSANT
public:
    vector<int> move_list;
    void reset(){
        move_list.clear();
    }
    void get_moves(int r,int c,const board& b){
        char t = b.board_matrix[cor[0]][cor[1]][1];
        if(t=='w'){
            if(cor[0]==1){      //starting rank 2 square jump for pawns
                if(b.board_matrix[3][cor[1]] == "LI"){
                    move_list.push_back(3); move_list.push_back(cor[1]);
                }
            }
            if(b.board_matrix[cor[0]+1][cor[1]]=="LI"){     //moving pawn one square forward
                move_list.push_back(cor[0]+1); move_list.push_back(cor[1]);
            }
            if(b.board_matrix[cor[0]+1][cor[1]+1][1]=='b'){
                move_list.push_back(cor[0]+1); move_list.push_back(cor[1]+1);
            }
            if(b.board_matrix[cor[0]+1][cor[1]-1][1]=='b'){
                move_list.push_back(cor[0]+1); move_list.push_back(cor[1]-1);
            }
            if(cor[0]==4){      //!!!EN PASSANT
                if(b.board_matrix[cor[0]][cor[1]-1]=="Pb"){
                    if(moves[moves.size()-2]==4 && moves[moves.size()-1]==cor[1]-1){
                        move_list.push_back(cor[0]+1); move_list.push_back(cor[1]-1);
                    }
                }
                if(b.board_matrix[cor[0]][cor[1]+1]=="Pb"){
                    if(moves[moves.size()-2]==5 && moves[moves.size()-1]==cor[1]+1){
                        move_list.push_back(cor[0]+1); move_list.push_back(cor[1]+1);
                    }
                }
            }
        }
        if(t=='b') {
            if (cor[0] == 6) {
                if (b.board_matrix[4][cor[1]] == "LI") {
                    move_list.push_back(4);
                    move_list.push_back(cor[1]);
                }
            }
            if (b.board_matrix[cor[0] - 1][cor[1]] == "LI") {
                move_list.push_back(cor[0] - 1);
                move_list.push_back(cor[1]);
            }
            if (b.board_matrix[cor[0] - 1][cor[1] + 1][1] == 'w') {
                move_list.push_back(cor[0] - 1);
                move_list.push_back(cor[1] + 1);
            }
            if (b.board_matrix[cor[0] - 1][cor[1] - 1][1] == 'w') {
                move_list.push_back(cor[0] - 1);
                move_list.push_back(cor[1] - 1);
            }
            if (cor[0] == 3) {
                if (b.board_matrix[cor[0]][cor[1] - 1] == "Pw") {
                    if (moves[moves.size() - 2] == 5 && moves[moves.size() - 1] == cor[1] - 1) {
                        move_list.push_back(cor[0] - 1);
                        move_list.push_back(cor[1] - 1);
                    }
                }
                if (b.board_matrix[cor[0]][cor[1] + 1] == "Pw") {
                    if (moves[moves.size() - 2] == 5 && moves[moves.size() - 1] == cor[1] + 1) {
                        move_list.push_back(cor[0] - 1);
                        move_list.push_back(cor[1] + 1);
                    }
                }
            }
        }
    }
};