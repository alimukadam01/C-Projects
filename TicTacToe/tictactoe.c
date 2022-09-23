#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char player1 = 'X';
const char player2 = 'O';
const char computer = 'O';
char vs = ' ';


void resetBoard();
void printBoard();
int checkEmptyPlaces();
void player1Move();
void player2Move();
void computerMove();
char checkWinner();
void printWinner(char);

int main(){
        char winner = ' ';
        
        winner = ' ';
        resetBoard();
        
        printf("Do you want to play against Computer or Player?(C/P): ");
        scanf("%c", &vs);
        
        if (vs == 'C'){
            while(winner == ' ' && checkEmptyPlaces() != 0){
                printBoard();
                
                player1Move();
                winner = checkWinner();
                if (winner != ' ' || checkEmptyPlaces == 0)
                {
                    break;
                }
                
                computerMove();
                winner = checkWinner();
                if (winner != ' ' || checkEmptyPlaces() == 0)
                {
                    break;
                }
            }
        }
        else if (vs == 'P'){
            while(winner == ' ' && checkEmptyPlaces() != 0){
                printBoard();
                
                player1Move();
                winner = checkWinner();
                if (winner != ' ' || checkEmptyPlaces == 0)
                {
                    break;
                }
                
                printBoard();
                
                player2Move();
                winner = checkWinner();
                if (winner != ' ' || checkEmptyPlaces() == 0)
                {
                    break;
                }
            }
        }
        
        printBoard();
        printWinner(winner);
        printf("Thanks for playing!");
    
    
    return 0;
}

void resetBoard(){
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            board[i][j] = ' ';
        }
    } 
};

void printBoard(){
    printf("\n");
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n___|___|___\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n___|___|___\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
};

int checkEmptyPlaces(){
    int freeSpaces = 9;
    
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if (board[i][j] != ' '){
                freeSpaces--; 
            }
        }
    }
    return freeSpaces;
};

void player1Move(){
    int x;
    int y;
    
    do
    { 
        printf("Enter row#(1-3)");
        scanf("%d", &x);
        x--;
         
        printf("Enter column#(1-3)");
        scanf("%d", &y);
        y--;
        
        if (board[x][y] != ' '){
            printf("Invalid Move!\n");
        }
        else{
            board[x][y] = player1;
            break;
        }
    }while(board[x][y] != ' ');
};

void player2Move(){
    int x;
    int y;
    
    do
    { 
        printf("Enter row#(1-3)");
        scanf("%d", &x);
        x--;
         
        printf("Enter column#(1-3)");
        scanf("%d", &y);
        y--;
        
        if (board[x][y] != ' '){
            printf("Invalid Move!\n");
        }
        else{
            board[x][y] = player2;
            break;
        }
    }while(board[x][y] != ' ');
}

void computerMove(){
    //creates a random int based on time
    srand(time(0));
    
    int x;
    int y;
    
    if (checkEmptyPlaces() > 0){
        do{
            x = rand()%3;
            y = rand()%3;
        }while(board[x][y] != ' ');
        
        board[x][y] = computer;
    }
    else{
        printWinner(' ');
    }
};

char checkWinner(){
    //check columns
    for(int i=0; i<3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }
    
    //check columns
    for(int i=0; i<3; i++){
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
        }
    }
    
    //check diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][0];
    }
    
    return ' ';
};

void printWinner(char winner){
    if (vs == 'C'){
        if (winner == player1){
            printf("YOU WIN!\n");
        }
        else if (winner == computer){
            printf("YOU LOSE!\n");
        }
        else{
            printf("IT'S A DRAW\n");
        }
    }
    if (vs == 'P'){
        if (winner == player1){
            printf("PLAYER1 WINS!\n");
        }
        else if (winner == player2){
            printf("PLAYER2 WINS!\n");
        }
        else{
            printf("IT'S A DRAW\n");
        }
    }
};
