/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3   // минимаьный максимальный размер игрового поля
#define DIM_MAX 9   //

// board
int board[DIM_MAX][DIM_MAX];  // двумерный масив игрового поля

// dimensions
int d; // переменная задания размера игрового поля

// prototypes функций
void clear(void); // функция очистки
void greet(void);  //функция приветствия 
void init(void);  // функция инициализации  -
void draw(void);    // создание игрового поля -
bool move(int tile);    // движение по игровому полю - 
bool won(void);     // функция отвечающая за определение победы -
void searchPosicion(int tile, int codeXY[2], int codeNull[2]); // прототип функции поиска

int main(int argc, string argv[]) //принимаем аргумент - размер игрового поля
{
    // ensure proper usage
    if (argc != 2) 
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log создание лог файла
    FILE *file = fopen("log.txt", "w"); 
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void){
    int numbersTiles = d*d-1;
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            board [i][j] = numbersTiles--;
        }
    }
    if ((d*d-1) % 2 != 0){
            int temp = board[d-1][d-2];
            board[d-1][d-2] = board[d-1][d-3];
            board[d-1][d-3] = temp;
        }      
}

/**
 * Prints the board in its current state.
 */
void draw(void){
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
             if (board[i][j] == 0){
                printf(" _");
            }
            else{ 
                printf("%2d", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile){
    int codeXY [2] = {0};
    int codeNull [2] = {0};
    
    searchPosicion(tile, codeXY, codeNull);
    
    if((codeXY [0] == codeNull [0] && abs(codeXY [1] - codeNull [1]) == 1) || (abs (codeXY [0] - codeNull [0]) == 1 && codeXY [1] == codeNull [1])){
        board [codeNull[0]][codeNull[1]] = board [codeXY[0]][codeXY[1]];
        board [codeXY[0]][codeXY[1]] = 0;
        return true;
    }
    return false;
}

void searchPosicion(int tile, int codeXY [2], int codeNull [2]){  // Поиск заданой плитки и нулевой плитки
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if(board [i][j] == 0)
            {
                codeNull [0] = i;
                codeNull [1] = j;
            }
            if(board[i][j] == tile)
            {
                codeXY[0] = i;
                codeXY[1] = j;
            }
        }
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void){
    int temp0 = 1;
    int temp1 = 0;
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            if (board[i][j] == temp0){
                temp0 ++;
            }
            else{
                 temp1 ++;
            }
        }
    }
    if (board[d-1][d-1] != 0){
        return false;
    }
    if (temp1-1 > 0){
        return false;
    }
    return true;
}

