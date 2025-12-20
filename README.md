Tic Tac Toe (C++)

Files:
- tictactoe.cpp: Console Tic Tac Toe game with Human vs Human and Human vs Computer (minimax AI).

Build:
- macOS / clang++ (C++17):

  /usr/bin/clang++ -std=c++17 tictactoe.cpp -O2 -o tictactoe

Run:
- Interactive:

  ./tictactoe

  Choose mode 1 (HvH) or 2 (HvC). When prompted, enter moves as numbers 1-9.

- Auto test (non-interactive):

  ./tictactoe autotest

Notes;
- The board prints numbers for empty cells to show move positions.
 - Colored output: X and O are colored using ANSI escape sequences. If your terminal doesn't support colors or you prefer no color, set the environment variable `NO_COLOR` or run the program with the `--no-color` flag.
-small projects , every day