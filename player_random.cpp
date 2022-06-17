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
        //½Ý
        int t;
        for(t=y;t<SIZE&&tboard[x][t]==state;t++)
            ;
        if(t-y>=3)
            value+=1;
        //±×
        int t;
        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==state;t++)
            ;
        if(t>=3)
            value+=1;
    }
    if(tboard[x][y]==opponent_state)
    {
        //¾î
        int t;
        for(t=x;t<SIZE&&tboard[t][y]==opponent_state;t++)
            ;
        if(t-x>=4)
            value-=1;
        //½Ý
        int t;
        for(t=y;t<SIZE&&tboard[x][t]==opponent_state;t++)
            ;
        if(t-y>=4)
            value-=1;
        //±×
        int t;
        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==opponent_state;t++)
            ;
        if(t>=4)
            value-=1;
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

void write_valid_spot(std::ofstream& fout) {
    srand(time(NULL));
    int x, y;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.
        int x = (rand() % SIZE);
        int y = (rand() % SIZE);
        if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
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
