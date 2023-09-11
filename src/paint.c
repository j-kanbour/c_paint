#include <stdio.h>
#include <stdlib.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

#define WHITE 4

// Provided helper functions:

// Display the canvas.
void displayCanvas(int canvas[N_ROWS][N_COLS]);

// Clear the canvas by setting every pixel to be white.
void clearCanvas(int canvas[N_ROWS][N_COLS]);

//start == 1 or 2
void start_basic(int start, int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col);

//prints lines and empty boxes
void straight_lines(int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col);

//prints diagonal lines
void diagonal_lines(int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col);

//prints filled boxes
void filled_box(int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col);

//copies and pastes
void copy_paste(int canvas[N_ROWS][N_COLS], int start_row, int start_col, 
int end_row, int end_col, int to_row, int to_col);

//sends valid co-ordinates and shade to canvas
void send_to_canvas(int canvas[N_ROWS][N_COLS], int start_col, int start_row, int shade);

//invalid input
int invalid(int start_row, int start_col, int end_row, int end_col);

//Macro Record
void macro_rec(int record[5][10], int lines, int lines_count, int start, 
int shade, int start_row, int start_col, int end_row, int end_col);

//Macro Playback
void macro_play(int record[5][10], int canvas[N_ROWS][N_COLS], int shade, 
int *lines_point);

//save state
void save_canvas(int canvas[N_ROWS][N_COLS], int save1[N_ROWS][N_COLS], 
int save2[N_ROWS][N_COLS], int save3[N_ROWS][N_COLS], int save4[N_ROWS][N_COLS], 
int save5[N_ROWS][N_COLS], int save);

//print saves
void display_saves(int save1[N_ROWS][N_COLS], int save2[N_ROWS][N_COLS], 
int save3[N_ROWS][N_COLS], int save4[N_ROWS][N_COLS], int save5[N_ROWS][N_COLS], 
int save_count);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int main(void) {

    //main canvas array
    int canvas[N_ROWS][N_COLS];

    //array for Macro Record
    int record[5][10] = {0};

    //arrays for saved canvises 
    int save1[N_ROWS][N_COLS] = {0};
    int save2[N_ROWS][N_COLS] = {0};
    int save3[N_ROWS][N_COLS] = {0};
    int save4[N_ROWS][N_COLS] = {0};
    int save5[N_ROWS][N_COLS] = {0};

    clearCanvas(canvas);

    int start;
    int shade = 0;
    int start_row;
    int end_row;
    int start_col;
    int end_col;
    int to_row;
    int to_col;
    int unlock_6 = 0;
    int lines;
    int save = 0;
    int new = 1;


    //will cycle inuts for drawing until EOF
    while (scanf("%d", &start) == 1) {
        
        //changes the brush shade when requested
        if (start == 3) {
            int shade_temp;
            scanf("%d", &shade_temp);
            if (shade_temp <= 4 && shade_temp >= 0) {
                shade = shade_temp;
            }
            continue;
        }

        //Macro Record
        else if (start == 5) {
            int lines_count = 0;

            scanf("%d", &lines);

            macro_rec(record, lines, lines_count, start, shade, start_row, 
            start_col, end_row, end_col);
            unlock_6 = 1;

            continue;
        }

        //Macro Playback only if Macro Record has been done
        else if (start == 6 && unlock_6) {
            macro_play(record, canvas, shade, &lines);
            new = 1;
            continue;
        }

        //saves current canvas if it is different from the last save
        else if (start == 7 && save < 5 && new == 1) {
            save ++;
            save_canvas(canvas, save1, save2, save3, save4, save5, save);
            new = 0;
            continue;
        }


        else if (start == 1 || start == 2 || start == 4) {
            //requesting input for two coordinates
            scanf("%d %d %d %d", &start_row, &start_col, &end_row, &end_col);

            //This will disregard the line if both ends lie outside the canvas
            if (invalid(start_row, start_col, end_row, end_col) == 1) {
                continue;
            }
            
        
            else if (start == 1 || start == 2) {
                start_basic(start, canvas, shade, start_row, start_col, end_row, end_col);
            }

            //copy and paste
            else if (start == 4) {
                scanf("%d %d", &to_row, &to_col);
                copy_paste(canvas, start_row, start_col, end_row, end_col, 
                to_row, to_col);
            }
            new = 1;
        }

        else {
            continue;
        }
        

    }
    //prints saved canveses
    if (save != 0) {
        int save_count = 1;
        while (save_count <= save) {
            display_saves(save1, save2, save3, save4, save5, save_count);
            printf("\n");
            save_count ++;
        }
    }

    //prints canvas
    displayCanvas(canvas);

    return 0;
}


// ADD CODE FOR YOUR FUNCTIONS HERE

//start = 1, 2 or 4
void start_basic(int start, int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col) {

    //prints straight lines, diagonal lines and empty box 
    if (start == 1) {
        // digonal lines
        if ((abs(start_row - end_row) == abs(start_col - end_col)) 
        && (start_row != end_row && start_col != end_col)) {
            diagonal_lines(canvas, shade, start_row, start_col, end_row, 
            end_col);
        }
        //straight lines
        else {
            straight_lines(canvas, shade, start_row, start_col, end_row, 
            end_col);
        }
    }

    //prints filled box
    else if (start == 2) {
        filled_box(canvas, shade, start_row, start_col, end_row, end_col);
    }
}

//prints lines and empty boxes
void straight_lines(int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col) {

    //horoxzontal line going right
    if (end_col > start_col && start_row == end_row) {
        while (start_col <= end_col) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_col ++;
        }
    }
    //horoxzontal line going left
    else if (end_col < start_col && start_row == end_row) {
        while (start_col >= end_col) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_col --;
        }
    }
    //varticle line going down
    else if (end_row > start_row && start_col == end_col) {
        while (start_row <= end_row) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_row ++;
        }
    }
    //varticle line going up
    else if (end_row < start_row && start_col == end_col) {
        while (start_row >= end_row) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_row --;
        }
    }
    //single point
    else if (start_row == end_row && start_col == end_col) {
        send_to_canvas(canvas, start_col, start_row, shade);
    }

}

//prints diagonal lines
void diagonal_lines(int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col) {

    //Up Left
    if (start_row > end_row && start_col > end_col) {
        while (start_row >= end_row) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_col --;
            start_row --;
        }   
    }

    //Down Right
    else if (start_row < end_row && start_col < end_col) {
        while (start_row <= end_row) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_col ++;
            start_row ++;
        } 
    }

    //Down Left
    else if (start_row < end_row && start_col > end_col) {
        while (start_row <= end_row) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_col --;
            start_row ++;
        } 
    }

    //Up Right
    else if (start_row > end_row && start_col < end_col) {
        while (start_row >= end_row) {
            send_to_canvas(canvas, start_col, start_row, shade);
            start_col ++;
            start_row --;
        } 
    }
}

//prints filled boxes
void filled_box(int canvas[N_ROWS][N_COLS], int shade, int start_row, 
int start_col, int end_row, int end_col) {    

    //Up Left
    if (start_row >= end_row && start_col >= end_col) {
        while (start_row >= end_row) {
            int col = 0;
            while (start_col >= end_col) {
                send_to_canvas(canvas, start_col, start_row, shade);
                start_col --;
                col ++;
            }
            start_row --;
            start_col += col;
        }   
    }

    //Down Right
    else if (start_row <= end_row && start_col <= end_col) {
        while (start_row <= end_row) {
            int col = 0;
            while (start_col <= end_col) {
                send_to_canvas(canvas, start_col, start_row, shade);
                start_col ++;
                col ++;
            }
            start_row ++;
            start_col -= col;
        }  
    }

    //Down Left
    else if (start_row <= end_row && start_col >= end_col) {
        while (start_row <= end_row) {
            int col = 0;
            while (start_col >= end_col) {
                send_to_canvas(canvas, start_col, start_row, shade);
                start_col --;
                col ++;
            }
            start_row ++;
            start_col += col;
        }
    }

    //Up Right
    else if (start_row >= end_row && start_col <= end_col) {
        while (start_row >= end_row) {
            int col = 0;
            while (start_col <= end_col) {
                send_to_canvas(canvas, start_col, start_row, shade);
                start_col ++;
                col ++;
            }
            start_row --;
            start_col -= col;
        }
    }
}

//copies and pastes
void copy_paste(int canvas[N_ROWS][N_COLS], int start_row, int start_col, 
int end_row, int end_col, int to_row, int to_col) {

    //intialising a temporary array
    int temporary_array[N_ROWS][N_COLS] = {0};
    
    //creatign exact copy of canvas array with printed patern
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            temporary_array[row][col] = canvas[row][col];
            col ++;
        }
        row ++;
    }

    //copying pattern form temp array to canvas in new position
    int start_col_constant = start_col;
    int end_col_constant = end_col;
    int to_row_constant = to_col;

    while (start_row <= end_row) {
        start_col = start_col_constant;
        end_col = end_col_constant;
        to_col = to_row_constant;

        while (start_col <= end_col) {
            if ((to_col >= 0 && to_row >= 0) 
            && (to_col < N_COLS && to_row < N_ROWS)) {
                canvas[to_row][to_col] = temporary_array[start_row][start_col];
            }
            start_col ++;
            to_col ++;
        }
        start_row ++;
        to_row ++;
    }
}

//sends valid co-ordinates and shade to canvas
void send_to_canvas(int canvas[N_ROWS][N_COLS], int start_col, int start_row, int shade) {

    if ((start_col >= 0 && start_row >= 0) && 
    (start_col < N_COLS && start_row < N_ROWS))  {
        canvas[start_row][start_col] = shade;
    }

}

//invalid input
int invalid(int start_row, int start_col, int end_row, int end_col) {
    
    if ((start_row >= N_ROWS && end_row >= N_ROWS) 
    || (start_row < 0 && end_row < 0) 
    || (start_col >= N_COLS && end_col >= N_COLS) 
    || (start_col < 0 && end_col < 0) 
    || (start_row < 0 && end_row >= N_ROWS) 
    || (start_col < 0 && end_col >= N_COLS) 
    || (start_row >= N_ROWS && end_row < 0) 
    || (start_col >= N_COLS && end_col < 0)) {
        return 1;
    }
    else {
        return 0;
    }

}

//Macro Record
void macro_rec(int record[5][10], int lines, int lines_count, int start, 
int shade, int start_row, int start_col, int end_row, int end_col) {

    //creats a 2D array of 10 Cols, 5 Rows
    int row = 0;
    while (row < 10) {
        int col = 0;
        while (col < 5) {
            record[col][row] = 0;
            col ++;
        }
        row ++;
    }

    //enters the lines to be recorded into the 2D array 
    while (lines_count < lines) {
        int input = 0; 


        scanf("%d %d %d %d %d", &start, &start_row, &start_col, &end_row, 
        &end_col);

        record[input][lines_count] = start;
        input ++;
        record[input][lines_count] = start_row;
        input ++;
        record[input][lines_count] = start_col;
        input ++;
        record[input][lines_count] = end_row;
        input ++;
        record[input][lines_count] = end_col;

        lines_count ++;
    }
}

//Macro Playback
void macro_play(int record[5][10], int canvas[N_ROWS][N_COLS], int shade, 
int *lines_point) {

    int move_x;
    int move_y;
    int lines_count = 0;

    //requests for the Macro shifts
    scanf("%d %d", &move_x, &move_y);

    //enters the recorded line elements back into the initial co-ordinate inputs
    while (lines_count < *lines_point) {
        
        int row_count = 0;

        int start = record[row_count][lines_count];
        row_count ++;
        int start_row = record[row_count][lines_count] + move_x;
        row_count ++;
        int start_col = record[row_count][lines_count] + move_y;
        row_count ++;
        int end_row = record[row_count][lines_count] + move_x;
        row_count ++;
        int end_col = record[row_count][lines_count] + move_y;

        if (invalid(start_row, start_col, end_row, end_col) == 1) {
            lines_count ++;
            continue;
        }

        else {
            //start == 1 or 2
            start_basic(start, canvas, shade, start_row, start_col, end_row, end_col);
            lines_count ++;
        }
        
    }
}

//Save
void save_canvas(int canvas[N_ROWS][N_COLS], int save1[N_ROWS][N_COLS], 
int save2[N_ROWS][N_COLS], int save3[N_ROWS][N_COLS], int save4[N_ROWS][N_COLS], 
int save5[N_ROWS][N_COLS], int save) {
    //copies the current canvas into the current save array

    if (save == 1) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                save1[row][col] = canvas[row][col];
                col ++;
            }
            row ++;
        }
    }


    else if (save == 2) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                save2[row][col] = canvas[row][col];
                col ++;
            }
            row ++;
        }
    }

    else if (save == 3) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                save3[row][col] = canvas[row][col];
                col ++;
            }
            row ++;
        }
    }

    else if (save == 4) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                save4[row][col] = canvas[row][col];
                col ++;
            }
            row ++;
        }
    }

    else if (save == 5) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                save5[row][col] = canvas[row][col];
                col ++;
            }
            row ++;
        }
    }

}

//display saves
void display_saves(int save1[N_ROWS][N_COLS], int save2[N_ROWS][N_COLS], 
int save3[N_ROWS][N_COLS], int save4[N_ROWS][N_COLS], 
int save5[N_ROWS][N_COLS], int save_count) {
    //cycles throught the elements of the save arrays to print them 
    
    if (save_count == 1) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                printf("%d ", save1[row][col]);
                col ++;
            }
            row ++;
            printf("\n");
        }
    }

    else if (save_count == 2) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                printf("%d ", save2[row][col]);
                col ++;
            }
            row ++;
            printf("\n");
        }
    }

    else if (save_count == 3) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                printf("%d ", save3[row][col]);
                col ++;
            }
            row ++;
            printf("\n");
        }
    }

    else if (save_count == 4) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                printf("%d ", save4[row][col]);
                col ++;
            }
            row ++;
            printf("\n");
        }
    }

    else if (save_count == 5) {
        int row = 0;
        while (row < N_ROWS) {
            int col = 0;
            while (col < N_COLS) {
                printf("%d ", save5[row][col]);
                col ++;
            }
            row ++;
            printf("\n");
        }
    }
}

// Dis`plays the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.

// You should not need to change the displayCanvas function.

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
//
// You should not need to change the clearCanvas function.
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
vx10 % 
