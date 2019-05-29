// dvir segev
// 318651627

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


#define Size 20

int flag=1;

struct Place {
    int x;
    int y;
};
typedef struct Place place;
struct tetris {
    char board[Size][Size];
    place Lsign;
    place Msign;
    place Rsign;
};

int PlaceMinos(int i, int j);

typedef struct tetris tetris;
static tetris *tetris1;

void printTet();



void initPositions() {
    tetris1->Lsign.x = 0;
    tetris1->Lsign.y = 8;
    tetris1->Msign.x = 0;
    tetris1->Msign.y = 9;
    tetris1->Rsign.x = 0;
    tetris1->Rsign.y = 10;
}

void handleAlarm(int sig) {

    tetris1->Lsign.x +=1 ;
    tetris1->Msign.x += 1;
    tetris1->Rsign.x += 1;
    if ( tetris1->Rsign.x == Size-1)
        initPositions();
    signal(SIGALRM, handleAlarm);
    printTet();
}

void setBorad() {
    for (int i = 0; i < Size; i++) {
        tetris1->board[i][0] = '*';
        tetris1->board[i][Size - 1] = '*';
    }
    for (int j = 0; j < Size; j++) {
        tetris1->board[Size - 1][j] = '*';
    }
}
void printTet() {
    signal(SIGALRM, handleAlarm);
    if(flag)
        alarm(1);
    system("clear");
    for (int i = 0; i < Size;i++)
    {
        for (int j = 0; j < Size; j++) {
            if (tetris1->board[i][j] == '*')
                write(1, &tetris1->board[i][j], 1);
            else if (PlaceMinos(i, j))
                write(1, "-", 1);
            else write(1, " ", 1);
        }
        write(1, "\n", strlen("\n"));
    }

//    for(int j=0; j<Size-2;j++) {
//     write(1,&tetris1->board[Size-1][j],1);
//    }


}

int PlaceMinos(int i, int j) {
    return (((tetris1->Lsign.x == i && tetris1->Lsign.y == j) ||
             (tetris1->Msign.x == i && tetris1->Msign.y == j) ||
             (tetris1->Rsign.x == i && tetris1->Rsign.y == j)));
}

int main() {
    tetris1 = (tetris *) malloc(sizeof(tetris));
//    signal(SIGUSR2, readUsual);
    initPositions();
    setBorad();
    write(1, "\n", 1);
    printTet();
    while (1) {
        //}
    }
}
