#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

int player;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}
int discs_value(array<std::array<int, SIZE>, SIZE> &tboard,int x,int y,int state,int opponent_state)
{
    int value=0;
    if(tboard[x][y]==state)
    {
        //¾î
        int t;
        for(t=x;t<SIZE&&tboard[t][y]==state;t++)
            ;
        if(t-x>=3)
            value+=1;
        if(t-x>=5)
            return INT_MAX;
        //½Ý
        int t;
        for(t=y;t<SIZE&&tboard[x][t]==state;t++)
            ;
        if(t-y>=3)
            value+=1;
        if(t-y>=5)
            return INT_MAX;
        //±×
        int t;
        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==state;t++)
            ;
        if(t>=3)
            value+=1;
        if(t>=5)
            return INT_MAX;
    }
    if(tboard[x][y]==opponent_state)
    {
        //¾î
        int t;
        for(t=x;t<SIZE&&tboard[t][y]==opponent_state;t++)
            ;
        if(t-x>=4)
            value-=1;
        if(t-x>=5)
            return INT_MIN;
        //½Ý
        int t;
        for(t=y;t<SIZE&&tboard[x][t]==opponent_state;t++)
            ;
        if(t-y>=4)
            value-=1;
        if(t-y>=5)
            return INT_MIN;
        //±×
        int t;
        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==opponent_state;t++)
            ;
        if(t>=4)
            value-=1;
        if(t>=5)
            return INT_MIN;
    }
    return value;
}

int value_fun(array<std::array<int, SIZE>, SIZE> &tboard,int state,int opponent_state)
{
    int value=0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            value+=discs_value(tboard,i,j,state,opponent_state);
        }
    }
    return value;
}
enum MINMAXFIND_STATE {
    FINDMAX = 0,
    FINDMIN = 1,
};
int minmax_find(array<std::array<int, SIZE>, SIZE> &tboard,int depth,int minmaxmode,int state)
{
    if(depth==0)
        return value_fun(tboard,player,3-player);
    int x = (rand() % SIZE);
    int y = (rand() % SIZE);
    int tx=x;
    int ty=y;
    int minmaxvalue;
    if(minmaxmode==FINDMAX)
        minmaxvalue=INT_MIN;
    else
        minmaxvalue=INT_MAX;
    while(1)
    {
        if(board[tx][ty] == EMPTY)
        {
            board[tx][ty]=state;
            int tv=minmax_find(tboard,depth-1,2-minmaxmode,3-state);
            board[tx][ty]=EMPTY;
            if(minmaxmode==FINDMAX)
            {
                if(tv>minmaxvalue)
                    minmaxvalue=tv;
            }
            else
            {
                if(tv<minmaxvalue)
                    minmaxvalue=tv;
            }
        }
        tx++;
        if(tx>=SIZE)
        {
            tx=0;
            ty++;
            if(ty>=SIZE)
                ty=0;
        }
        if(tx==x&&ty==y)
            break;
    }
    return minmaxvalue;
}

void write_valid_spot(std::ofstream& fout) {
    srand(time(NULL));
    int x = (rand() % SIZE);
    int y = (rand() % SIZE);
    int tx=x;
    int ty=y;
    int depth=2;
    int maxvalue=INT_MIN;
    int minmaxmode=FINDMAX;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.

        /*if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }*/
        if (board[tx][ty] == EMPTY)
        {
            board[tx][ty]=player;
            int tv=minmax_find(tboard,depth-1,2-minmaxmode,3-player);
            board[tx][ty]=EMPTY;
            if(tv>minmaxvalue)
            {
                minmaxvalue=tv;
                fout << tx << " " << ty << std::endl;
                fout.flush();
            }
        }
        tx++;
        if(tx>=SIZE)
        {
            tx=0;
            ty++;
            if(ty>=SIZE)
                ty=0;
        }
        if(tx==x&&ty==y)
            depth++;
    }
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
