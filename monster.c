#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int boardX, boardY, plrX, plrY, goalX, goalY, monX, monY;

void printBoard(char** board){

    for(int i=boardY-1; i>=0; i--){
        for(int j=0; j<boardX; j++) board[i][j]='.';
    }
    board[plrX][plrY]='P';
    board[goalX][goalY]='G';
    board[monX][monY]='M';

    for(int i=boardY-1; i>=0; i--){
        for(int j=0; j<boardX; j++){
            printf("%c ", board[j][i]);
        }
        printf("\n");
    }
}


bool isMoveValid(char** board, char move){

    switch(move){
        case 'N':
            if(plrY+1>=boardY){
                printf("invalid move\n");
                return false;
            } else {
                plrY++;
                return true;
            }
        case 'E': 
            if(plrX+1>=boardX){
                printf("invalid move\n");
                return false;
            }else {
                plrX++;
                return true;
            }
        case 'W':
            if(plrX-1<0){
                printf("invalid move\n");
                return false;
            }else {
                plrX--;
                return true;
            }
        case 'S':
            if(plrY-1<0){
                printf("invalid move\n");
                return false;
            }else {
                plrY--;
                return true;
            }
        default : return false;
    }

    return false;
} 

bool monsterMove(char** board){
    char move;

    if(plrX!=monX && (plrY==monY || abs(plrX-monX)<abs(plrY-monY))){
        if(plrX<monX) {
            move='W'; monX--;
        }else{
            move='E'; monX++;
        }
    }else{
        if(plrY<monY) {
            move='S'; monY--;
        }else{
            move='N'; monY++;
        }
    }

    printf("monster moves %c\n", move);

    return (plrX==monX && plrY==monY);
}

int main(int argc, char* argv[]){

    boardX = atoi(argv[1]);
    boardY = atoi(argv[2]);
    plrX = atoi(argv[3]);
    plrY = atoi(argv[4]);
    goalX = atoi(argv[5]);
    goalY = atoi(argv[6]);
    monX = atoi(argv[7]);
    monY = atoi(argv[8]);

    char** board = malloc(sizeof(char*) *boardY);
    for(int i=0; i<boardY; i++){
        board[i]=malloc(sizeof(char) *boardX);
    }

    printBoard(board);

    char move = ' ';
    while(true){
        move = fgetc(stdin);
        while(!isMoveValid(board, move)){
            move = fgetc(stdin);
        }

        if(plrX==goalX && plrY==goalY){
            printf("player wins!\n");
            break;
        }else if(plrX==monX && plrY==monY){
            printf("monster wins!\n");
            break;
        }else if(monsterMove(board)){
            printf("monster wins!\n");
            break;
        }

        printBoard(board);

    }

    for(int i=0; i<boardY; i++){
        free(board[i]);
    }
    free(board);

}