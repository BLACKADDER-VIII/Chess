class King{
public:
    vector<int> move_list;
    void reset(){
        move_list.clear();
    }
    void get_moves(int r,int c,const board& b){
        if(is_valid(r+1,c+1,b)&&!(in_check(r+1,c+1,b))){
            move_list.push_back(r+1);move_list.push_back(c+1);
        }
        if(is_valid(r,c+1,b)&&!(in_check(r,c+1,b))){
            move_list.push_back(r);move_list.push_back(c+1);
        }
        if(is_valid(r-1,c+1,b)&&!(in_check(r-1,c+1,b))){
            move_list.push_back(r-1);move_list.push_back(c+1);
        }
        if(is_valid(r+1,c-1,b)&&!(in_check(r+1,c-1,b))){
            move_list.push_back(r+1);move_list.push_back(c-1);
        }
        if(is_valid(r+1,c,b)&&!(in_check(r+1,c,b))){
            move_list.push_back(r+1);move_list.push_back(c);
        }
        if(is_valid(r,c-1,b)&&!(in_check(r,c-1,b))){
            move_list.push_back(r);move_list.push_back(c-1);
        }
        if(is_valid(r-1,c,b)&&!(in_check(r-1,c,b))){
            move_list.push_back(r-1);move_list.push_back(c);
        }
        if(is_valid(r-1,c-1,b)&&!(in_check(r-1,c-1,b))){
            move_list.push_back(r-1);move_list.push_back(c-1);
        }
    }

private:
};