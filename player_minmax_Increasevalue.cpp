#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

int player;
const int SIZE = 15;
const int IMPORT_SIZE = 2;
std::array<std::array<int, SIZE>, SIZE> board;
std::array<std::array<int, SIZE>, SIZE> import_board;

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
            import_board[i][j]=0;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(board[i][j]!=EMPTY)
            {
                for(int ti=std::max(0,i-IMPORT_SIZE),tim=std::min(SIZE-1,i+IMPORT_SIZE);ti<=tim;ti++)
                {
                    for(int tj=std::max(0,j-IMPORT_SIZE),tjm=std::min(SIZE-1,j+IMPORT_SIZE);tj<=tjm;tj++)
                    {
                        import_board[ti][tj]+=1;
                    }
                }
            }
        }
    }
}
void print_board(std::array<std::array<int, SIZE>, SIZE> &tboard) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout<< tboard[i][j];
        }
        std::cout<<std::endl;
    }
}
int discs_increase_value(std::array<std::array<int, SIZE>, SIZE> &tboard,int x,int y,int state,int opponent_state)
{
    int value=0;
    if(tboard[x][y]==state)
    {
        int t;
        int tt;
        for(t=0;t+x<SIZE&&tboard[t+x][y]==state;t++)
            ;
        for(tt=0;tt+x>=0&&tboard[tt+x][y]==state;tt--)
            ;
        if(t-tt-1==3)
            value+=1;
        else if(t-tt-1==4)
        {
            if(tt==-1||t==1)
            value+=4;
            else
            value+=5;
        }
        else if(t-tt-1==5)
            return INT_MAX;

        for(t=0;t+y<SIZE&&tboard[x][t+y]==state;t++)
            ;
        for(tt=0;tt+y>=0&&tboard[x][tt+y]==state;tt--)
            ;
        if(t-tt-1==3)
            value+=1;
        else if(t-tt-1==4)
        {
            if(tt==-1||t==1)
            value+=4;
            else
            value+=5;
        }
        else if(t-tt-1==5)
            return INT_MAX;

        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==state;t++)
            ;
        for(t=0;t+y>=0&&t+x>=0&&tboard[x+t][y+t]==state;t--)
            ;
        if(t-tt-1==3)
            value+=1;
        else if(t-tt-1==4)
        {
            if(tt==-1||t==1)
            value+=4;
            else
            value+=5;
        }
        else if(t-tt-1==5)
            return INT_MAX;
    }
    if(tboard[x][y]==opponent_state)
    {
        int t;
        int tt;
        for(t=0;t+x<SIZE&&tboard[t+x][y]==opponent_state;t++)
            ;
        for(tt=0;tt+x>=0&&tboard[tt+x][y]==opponent_state;tt--)
            ;
        if(t-tt-1==3)
            value-=1;
        else if(t-tt-1==4)
        {
            if(tt==-1||t==1)
            value-=4;
            else
            value-=5;
        }
        else if(t-tt-1==5)
            return INT_MIN;

        for(t=0;t+y<SIZE&&tboard[x][t+y]==opponent_state;t++)
            ;
        for(tt=0;tt+y>=0&&tboard[x][tt+y]==opponent_state;tt--)
            ;
        if(t-tt-1==3)
            value-=1;
        else if(t-tt-1==4)
        {
            if(tt==-1||t==1)
            value-=4;
            else
            value-=5;
        }
        else if(t-tt-1==5)
            return INT_MIN;

        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==opponent_state;t++)
            ;
        for(t=0;t+y>=0&&t+x>=0&&tboard[x+t][y+t]==opponent_state;t--)
            ;
        if(t-tt-1==3)
            value-=1;
        else if(t-tt-1==4)
        {
            if(tt==-1||t==1)
            value-=4;
            else
            value-=5;
        }
        else if(t-tt-1==5)
            return INT_MIN;
    }
    return value;
}
/*int discs_value(std::array<std::array<int, SIZE>, SIZE> &tboard,int x,int y,int state,int opponent_state)
{
    int value=0;
    if(tboard[x][y]==state)
    {
        //¾î
        int t;
        for(t=x;t<SIZE&&tboard[t][y]==state;t++)
            ;
        if(t-x==3)
            value+=1;
        else if(t-x==4)
            value+=5;
        else if(t-x==5)
            return INT_MAX;
        //½Ý
        for(t=y;t<SIZE&&tboard[x][t]==state;t++)
            ;
        if(t-y==3)
            value+=1;
        else if(t-y==4)
            value+=1;
        else if(t-y==5)
            return INT_MAX;
        //±×
        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==state;t++)
            ;
        if(t==3)
            value+=1;
        else if(t==4)
            value+=5;
        else if(t==5)
            return INT_MAX;
    }
    if(tboard[x][y]==opponent_state)
    {
        //¾î
        int t;
        for(t=x;t<SIZE&&tboard[t][y]==opponent_state;t++)
            ;
        if(t-x==3)
            value-=1;
        else if(t-x==4)
            value-=5;
        else if(t-x==5)
            return INT_MIN;
        //½Ý
        for(t=y;t<SIZE&&tboard[x][t]==opponent_state;t++)
            ;
        if(t-y==3)
            value-=1;
        else if(t-y==4)
            value-=5;
        else if(t-y==5)
            return INT_MIN;
        //±×
        for(t=0;t+y<SIZE&&t+x<SIZE&&tboard[x+t][y+t]==opponent_state;t++)
            ;
        if(t==3)
            value-=1;
        else if(t==4)
            value-=5;
        else if(t==5)
            return INT_MIN;
    }
    return value;
}

int value_fun(std::array<std::array<int, SIZE>, SIZE> &tboard,int state,int opponent_state)
{
    int value=0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int t=discs_value(tboard,i,j,state,opponent_state);
            if(t==INT_MIN||t==INT_MAX)
                return t;
            value+=t;
        }
    }
    return value;
}*/
enum MINMAXFIND_STATE {
    FINDMAX = 0,
    FINDMIN = 1,
};
int minmax_find(std::array<std::array<int, SIZE>, SIZE> &tboard,int depth,int minmaxmode,int state,int ox,int oy,int board_value)
{
    int tv=discs_increase_value(tboard,ox,oy,player,3-player);
    if(0)
    {
       print_board(board);
       std::cout<<ox<<" "<<oy<<" "<<tv<<std::endl;
    }
    if(tv==INT_MIN||tv==INT_MAX)
        return tv;
    board_value+=tv;
    if(depth==0)
        return board_value;
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
        if(board[tx][ty] == EMPTY&&import_board[tx][ty]>0)
        {
            board[tx][ty]=state;
            for(int ti=std::max(0,tx-IMPORT_SIZE),tim=std::min(SIZE-1,tx+IMPORT_SIZE);ti<=tim;ti++)
            {
                for(int tj=std::max(0,ty-IMPORT_SIZE),tjm=std::min(SIZE-1,ty+IMPORT_SIZE);tj<=tjm;tj++)
                {
                    import_board[ti][tj]+=1;
                }
            }
            int tv=minmax_find(tboard,depth-1,1-minmaxmode,3-state,tx,ty,board_value);
            board[tx][ty]=EMPTY;
            for(int ti=std::max(0,tx-IMPORT_SIZE),tim=std::min(SIZE-1,tx+IMPORT_SIZE);ti<=tim;ti++)
            {
                for(int tj=std::max(0,ty-IMPORT_SIZE),tjm=std::min(SIZE-1,ty+IMPORT_SIZE);tj<=tjm;tj++)
                {
                    import_board[ti][tj]-=1;
                }
            }
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
    int x = 0;//(rand() % SIZE);
    int y = 0;//(rand() % SIZE);
    int tx=x;
    int ty=y;
    const int print_depth=4;
    int depth=4;
    int maxvalue=INT_MIN;
    int minmaxmode=FINDMAX;
    int board_value=0;//value_fun(board,player,3-player);
    print_board(import_board);
    std::cout<<board_value<<std::endl;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.

        /*if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }*/
        if (board[tx][ty] == EMPTY &&import_board[tx][ty]>0)
        {
            board[tx][ty]=player;
            for(int ti=std::max(0,tx-IMPORT_SIZE),tim=std::min(SIZE-1,tx+IMPORT_SIZE);ti<=tim;ti++)
            {
                for(int tj=std::max(0,ty-IMPORT_SIZE),tjm=std::min(SIZE-1,ty+IMPORT_SIZE);tj<=tjm;tj++)
                {
                    import_board[ti][tj]+=1;
                }
            }
            int tv=minmax_find(board,depth-1,1-minmaxmode,3-player,tx,ty,board_value);
            board[tx][ty]=EMPTY;
            for(int ti=std::max(0,tx-IMPORT_SIZE),tim=std::min(SIZE-1,tx+IMPORT_SIZE);ti<=tim;ti++)
            {
                for(int tj=std::max(0,ty-IMPORT_SIZE),tjm=std::min(SIZE-1,ty+IMPORT_SIZE);tj<=tjm;tj++)
                {
                    import_board[ti][tj]-=1;
                }
            }
            if(depth==print_depth)
                std::cout<<tv<<" ";
            if(tv>maxvalue)
            {
                maxvalue=tv;
                fout << tx << " " << ty << std::endl;
                fout.flush();
            }
        }
        else if(depth==print_depth)
        {
            if(board[tx][ty]==BLACK)
                std::cout<<"B ";
            if(board[tx][ty]==WHITE)
                std::cout<<"W ";
            if(import_board[tx][ty]==0)
                std::cout<<"X ";
        }
        ty++;
        if(ty>=SIZE)
        {
            if(depth==print_depth)
                std::cout<<"\n";
            ty=0;
            tx++;
            if(tx>=SIZE)
            {
                tx=0;
            }
        }
        if(tx==x&&ty==y)
        {
            depth++;
            break;
        }
    }
}

int main(int, char** argv) {
    std::ifstream fin("state");
    std::ofstream fout("action");
    //std::ifstream fin(argv[1]);
    //std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
