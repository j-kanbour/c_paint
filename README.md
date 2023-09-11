# c_paint
A mock of MS_Paint where you can paint on a terminal grid

Gid size (N x N): The top left corner of the canvas is (0, 0) and the bottom right corner of the canvas is (N_ROWS - 1, N_COLS - 1)

commands:
    Draw a line: (1 x1 y1 x2 y2)
        $1 5 5 10 5 --> DRAW LINE starting at (row 5, col 5) until (row 10, col 5) VERTICALLY.
        $1 10 3 10 10 --> DRAW LINE starting at (row 10, col 3) until (row 10, col 10) HORIZONTALLY.
        $1 0 0 9 9 --> DRAW LINE starting at (row 0, col 0) until (row 9, col 9) DIAGONALLY.
        $1 2 2 2 2 --> DRAW LINE starting at (row 2, col 2) until (row 2, col 2) (A POINT).

    Draw a filled box (2 x1 y1 x2 y2)
        e.g. 
            $2 0 0 10 10 --> FILL RECTANGLE starting at (row 0, col 0) until (row 10, col 10).
            $2 6 2 2 2 --> FILL RECTANGLE starting at (row 6, col 2) until (row 2, col 2).

    Change Shade (3 colour)
        choose a colour
            Black (0):    
            Dark  (1):  ░░
            Grey  (2):  ▒▒
            Light (3):  ▓▓
            White (4):  ██
    
        e.g. 
            $3 2 --> USE BRUSH WITH SHADE Grey (code: 2).
    
    Copy and paste (4 start_x start_y end_x end_y target_x target_y)
        e.g. 
            $4 0 0 9 9 0 10 --> COPY RECTANGLE starting at (row 0, col 0) until (row 9, col 9); PASTE STARTING AT (row 0, col 10).
    
    Macro Record which saves the commands you enter; and Macro Playback which plays a macro back.
        
        Macro record (5 number of lines to recors)
        Macro playback (6 row_offset col_offset)

        e.g. 
            5 2 #record the next 2 lines
            1 1 1 3 3
            1 5 5 7 7

            1 2 2 4 2 #this line is ignored

            6 1 0 #play the 2 recorded lines but offset them by 1 row
    
    Save state (7)