#include <iostream>
#include<vector>
#include<map>
#include<stack>
#include<queue>
using namespace std;
char SpecialChar;
int dx[]{1,-1,0,0};
int dy[]{0,0,1,-1};

class Puzzle{
    //The 8 puzzle game is a classic sliding puzzle that consists of a 3x3 grid with eight numbered tiles and one blank space.
    // The objective is to rearrange the tiles by sliding them into the blank space,ultimately achieving a specific goal configuration.
    // The tiles can only be moved into the adjacent empty space,
    // and the puzzle is considered solved when the tiles are arranged in numerical order from 1 to 8,
    // with the blank space in the bottom-right corner.
    // It's a simple yet challenging game that requires strategic thinking and planning to solve efficiently.
public:
    vector<vector<char>>grid;
    const int siz = 3;
    Puzzle(){
        grid.resize(siz,vector<char>(siz,'0'));
    }
    void Input(){
        cout<<"input the initial puzzle configuration you can use any character as the blank cell but don't make it empty:"<<endl;
        for(int i=0;i<siz;i++){
            for(int j=0;j<siz;j++){
                cin>>grid[i][j];
                if(!isdigit(grid[i][j])||grid[i][j]=='0'){
                    SpecialChar = grid[i][j];
                }
            }
        }
    }
    bool valid(int i,int j){
        return i>=0 && i<siz && j>=0 && j<siz;
    }
    vector<Puzzle>ActionsToMake(){
        //work on this pointer to return the valid actions from the current state
        vector<Puzzle>res;
        pair<int,int>pos = make_pair(-1,-1);
        for(int i=0;i<siz;i++){
            for(int j=0;j<siz;j++){
                if(grid[i][j]==SpecialChar){
                    pos = make_pair(i,j);
                }
            }
        }
        for(int i=0;i<4;i++){
            int ni = pos.first + dx[i];
            int nj = pos.second + dy[i];
            if(valid(ni,nj)){
                swap(grid[pos.first][pos.second],grid[ni][nj]);
                res.emplace_back(*this);
                swap(grid[pos.first][pos.second],grid[ni][nj]);
            }
        }
        return res;
    }
    bool GoalCheck(){
         vector<vector<char>>temp{{'1','2','3'},{'4','5','6'},{'7','8', SpecialChar}};
         return this->grid == temp;
    }
    bool operator==(Puzzle &b)const{
        return this->grid == b.grid;
    }
};

void PuzzleSolver(const Puzzle &InitialPuzzle){
    queue<Puzzle>q;
    q.push(InitialPuzzle);
    map<vector<vector<char>>,vector<vector<char>>>parent;
    map<vector<vector<char>>,bool> vis;//keep track of the explored puzzles
    int TotalMoves = 0;
    vis[InitialPuzzle.grid] = true;
    while(!q.empty()){
        int sz = (int)q.size();
        while(sz--) {
            Puzzle node = q.front();
            if (node.GoalCheck()) {
                cout << "YES WE FOUND THE GOAL AND IT COSTED US:"<<" "<< TotalMoves <<" Moves"<< endl<<endl;
                cout << "THE OPTIMAL PATH TO FIND THE GOAL IS:"<<endl;
                vector<vector<vector<char>>>ans;
                vector<vector<char>>temp = node.grid;
                while(parent.count(temp)){
                    ans.emplace_back(temp);
                    temp = parent[temp];
                }
                ans.emplace_back(temp);
                reverse(ans.begin(),ans.end());
                for(int i=0;i<ans.size();i++){
                    cout<<"at the "<<i<<"th Move"<<":"<<endl;
                    for(auto &val:ans[i]){
                        for(auto &j:val)
                            cout<<j;
                        cout<<endl;
                    }
                }
                exit(0);
            }
            q.pop();
            vector<Puzzle> temp = node.ActionsToMake();
            for (auto &val: temp) {
                if (vis.count(val.grid))continue;
                vis[val.grid] = true;
                parent[val.grid] = node.grid;
                q.push(val);
            }
        }
        TotalMoves++;
    }
}

int main() {
    Puzzle initial;
    initial.Input();
    PuzzleSolver(initial);
}
