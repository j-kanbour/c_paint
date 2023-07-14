# c_paint
A mock of MS_Paint where you can paint on a terminal grid

Gid size (N x N): The top left corner of the canvas is (0, 0) and the bottom right corner of the canvas is (N_ROWS - 1, N_COLS - 1)

commands:
    Drawing:
        choose a color to start
            Black (0):    
            Dark  (1):  ░░
            Grey  (2):  ▒▒
            Light (3):  ▓▓
            White (4):  ██
        choose start and end coordinates
            Sx Sy Ex Ey 

    e.g. 
        2 5 5 10 5 --> DRAW LINE starting at (row 5, col 5) until (row 10, col 5) VERTICALLY.
        1 10 3 10 10 --> DRAW LINE starting at (row 10, col 3) until (row 10, col 10) HORIZONTALLY.
        1 2 2 2 2 --> DRAW LINE starting at (row 2, col 2) until (row 2, col 2) (A POINT).

more features comming soon...
