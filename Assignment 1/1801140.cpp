#include <bits/stdc++.h>
using namespace std;

#define ll long long

int SIZE = 8;

/*Class declaration for Board*/
class Board{
private:
        string board;
        int cost;
public:
        Board(string board, int cost){
                this->cost = cost;
                this->board = board;
        }
        int returnCost(){
                return this->cost;
        }
        string returnBoard(){
                return this->board;
        }
};
/*For Priority Queue Comparison based on Cost*/
class Compare{
public:
    bool operator() (Board c1, Board c2){
        if (c1.returnCost() > c2.returnCost())
                return 1;
        else if (c1.returnCost() < c2.returnCost())
                return -1;
        return 0;
    }
};

class NQueenp_queue{
public:
    string arr;
    /*Creating initial state*/
    Board setBoard(){
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)
                arr+="0";
        return Board(arr,0);
    }
    /*Search for the row so as to find where to insert the queen*/
    int find(string arr){
        int i;
        for(i=0;i<SIZE;i++){
            int flag = 0;
            for(int j=0;j<SIZE;j++){
                if(arr[SIZE*i+j] == '1'){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
                return i;
        }
        return i;
    }
    /*check if the current state of board is valid*/
    bool isValid(string arr){
        for(int i=0;i<SIZE;i++){
            int sum_row = 0;
            int sum_col = 0;
            for(int j=0;j<SIZE;j++){
                sum_row += (int)arr[SIZE*i+j]-48;
                sum_col += (int)arr[SIZE*j+i]-48;
            }
            if(sum_row > 1 || sum_col > 1)
                return false;
        }
        for(int i=0;i<SIZE;i++){
            int sum_left = 0;
            int sum_right = 0;
            for(int j=0;j+i<SIZE;j++){
                sum_left += (int)arr[SIZE*j+j+i]-48;
                sum_right += (int)arr[SIZE*(j+i)+j]-48;
            }
            if(sum_left > 1 || sum_right > 1)
                return false;
        }
        for(int i=0;i<2*SIZE-1;i++){
            int sum_left = 0;
            int sum_right = 0;
            if(i<SIZE){
                for(int j=0;i-j>=0;j++){
                    sum_left += (int)arr[SIZE*j+i-j]-48;
                }
            }
            else{
                for(int j=i-SIZE+1;j<SIZE;j++){
                    sum_right += (int)arr[SIZE*j+i-j]-48;
                }
            }
            if(sum_left > 1 || sum_right > 1)
                return false;
        }
        return true;
    }
    /*print the valid state , called by driver function*/
    void display(string arr){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                if(arr[SIZE*i+j]=='1')cout<<"Q ";
                else cout<<". ";
            }
            cout<<'\n';
        }
    }
};

int main(){
    int count = 1; 
    NQueenp_queue queen;
    Board sol = queen.setBoard();
    priority_queue<Board, vector<Board>, Compare> p_queue;   
    p_queue.push(sol);
    while(!( p_queue.empty() )){
        /*Dequeue the Top/Head of the Queue*/
        Board chs = p_queue.top();
        p_queue.pop();
        string answer = chs.returnBoard();
        /*to check if my current state is valid*/
        if(!(queen.isValid(answer)))continue;
        /*variable i will get the position to insert the queen*/
        int i = queen.find(answer);
        /*if the state is valid and solution is complete*/
        if(i==SIZE){
            count++;
            cout<<"** NQueen Solution No. "<<count<<" **\n";
            queen.display(answer);
            cout<<"-------------------------------------\n";
                
        }
        else{
            /*explore the current node and enqueue it*/
            for(int j=0;j<SIZE;j++){
                answer = answer.substr(0, SIZE*i+j)+"1"+answer.substr(SIZE*i+j+1);
                p_queue.push(Board(answer, chs.returnCost()+1));
                answer = chs.returnBoard();
            }
        }

    }
    return 0;
}
