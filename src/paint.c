#include <stdio.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define WHITE 4

//helper functions:
// Display the canvas.
void displayCanvas(int canvas[N_ROWS][N_COLS]);
// Clear the canvas by setting every pixel to be white.
void clearCanvas(int canvas[N_ROWS][N_COLS]);
//used to check that the coordicnates make a straight line
int invalid(int start_row, int start_col, int end_row, int end_col);

int main(void) {
    int canvas[N_ROWS][N_COLS];

    clearCanvas(canvas);

    int start;
    int start_row;
    int end_row;
    int start_col;
    int end_col;


    while (scanf("%d", &start) == 1) {
        
        //requesting input for two coordinates
        scanf("%d %d %d %d", &start_row, &start_col, &end_row, &end_col);

        //adjust coordinated if they are out of range
        if (start_row >= N_ROWS) {
            start_row = N_ROWS - 1;
        }
        if (start_row < 0) {
            start_row = 0;
        }
        if (start_col >= N_COLS) {
            start_col = N_COLS - 1;
        }
        if (start_col < 0) {
            start_col = 0;
        }

        if (end_row >= N_ROWS) {
            end_row = N_ROWS - 1;
        }
        if (end_row < 0) {
            end_row = 0;
        }
        if (end_col >= N_COLS) {
            end_col = N_COLS - 1;
        }
        if (end_col < 0) {
            end_col = 0;
        }

        if(start == 1) {}
        else if(start == 2) {}
    displayCanvas(canvas);

    return 0;
}

// Displays the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
void displayCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
void clearCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}