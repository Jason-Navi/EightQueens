/**
* Jason Navi
* 3/10/16
* Program prints all 92 solutions to the eight queens problem (8x8 board)
* Solutions are printed out on a visual board
*/
#include <iostream>
#include <cmath>
using namespace std;

/**Checks and returns true if there are no conflicts. If there is a conflict, returns false*/
bool ok(int q[], int c){
    for (int i = 0; i < c; ++i)
        if (q[i] == q[c] || abs(q[i] - q[c]) == c - i) // If there is a Queen in the same column, or in the upper/lower-left diagonal return false
            return false;
    return true;
}

/**Prints out solution on a visual board*/
void print(int q[]){
    // Keeps track of solutions found
    static int solution = 0;

    // Box is a data type: a 5x7 2D array of characters
    typedef char box[5][7];

    // bb and wb are boxes (5x7 arrays). Board is an 8x8 array of pointers to boxes
    box bb, wb, *board[8][8];

    //Fills in bb (black box) and wb (white box). They each represent a square of the chessboard
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 7; j++) {
            bb[i][j] = ' ';
            wb[i][j] = char(219);
        }

    // Creates 2 more boxes to represent the queens by drawing a picture of each queen (white and black) in the 2D array
    static box bq = {{char(219), char(219), char(219), char(219), char(219), char(219), char(219)},
                     {char(219), ' ',       char(219), ' ',       char(219), ' ',       char(219)},
                     {char(219), ' ',       ' ',       ' ',       ' ',       ' ',       char(219)},
                     {char(219), ' ',       ' ',       ' ',       ' ',       ' ',       char(219)},
                     {char(219), char(219), char(219), char(219), char(219), char(219), char(219)}};

    static box wq = {{' ', ' ',       ' ',       ' ',       ' ',       ' ',       ' '},
                     {' ', char(219), ' ',       char(219), ' ',       char(219), ' '},
                     {' ', char(219), char(219), char(219), char(219), char(219), ' '},
                     {' ', char(219), char(219), char(219), char(219), char(219), ' '},
                     {' ', ' ',       ' ',       ' ',       ' ',       ' ',       ' '}};

    // Fills the board with pointers to bb and wb in alternate positions
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if ((i + j) % 2 == 0)
                board[i][j] = &wb;
            else
                board[i][j] = &bb;


    // Sets up the current solution on the chessboard by placing pointers to bq and wq in the appropriate squares
    // Places black queens on white squares and white queens on black squares, so that you will be able to see them when printing
    for (int i = 0; i < 8; i++) {
        if ((q[i] + i) % 2 == 0)
            board[q[i]][i] = &bq;
        else board[q[i]][i] = &wq;
    }

    // Prints out the current solution number
    cout << "Solution #" << ++solution << ":\n ";

    // Prints the upper border
    for (int i = 0; i < 7 * 8; i++)
        cout << '_';
    cout << "\n";

    // Prints the board
    for (int i = 0; i < 8; i++)                   // For each board row
        for (int k = 0; k < 5; k++) {             // For each box row
            cout << char(179);                    // Prints out a dash "-" to create the boxes
            for (int j = 0; j < 8; j++)           // For each board column
                for (int l = 0; l < 7; l++)       // For each box column
                    cout << (*board[i][j])[k][l]; // Prints the box being pointed to in the kth row, lth column of the box
            cout << char(179) << "\n";
        }

    // Prints lower border
    cout << " ";
    for (int i = 0; i < 7 * 8; i++)
        cout << char(196);
    cout << "\n\n";
}

/**Prints the correct solution once you hit column eight otherwise it keeps looking for a solution*/
void next(int q[], int c){
    if (c == 8)                           // If columns is equal to 8 then you have found a solution and should print it
        print(q);
    else for(q[c] = 0; q[c] < 8; ++q[c])  // Otherwise loop through the rows in column c to find a place for the next Queen
            if (ok(q, c))                 // If there is no conflict in the row then move to the next column to find a place for the next Queen
                next(q, c + 1);
}

int main(){
    // Declares an array of length 8 and calls the next function with the array and column as 0 to start the program
    int q[8];
    next(q, 0);
    return 0;
}
