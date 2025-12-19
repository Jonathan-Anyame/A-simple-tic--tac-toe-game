#include <iostream>
#include <array>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

using Board = array<char, 9>;

// Color toggle and ANSI codes
static bool g_use_color = true;
static const char *COLOR_RED = "\x1b[31m";  // X
static const char *COLOR_BLUE = "\x1b[34m"; // O
static const char *COLOR_RESET = "\x1b[0m";

void printBoard(const Board &b)
{
    cout << "\n";
    for (int i = 0; i < 9; i++)
    {
        char c = b[i];
        if (c == ' ')
            cout << (i + 1);
        else
        {
            if (g_use_color)
            {
                if (c == 'X')
                    cout << COLOR_RED << c << COLOR_RESET;
                else
                    cout << COLOR_BLUE << c << COLOR_RESET;
            }
            else
                cout << c;
        }

        if ((i + 1) % 3 == 0)
            cout << "\n";
        else
            cout << " | ";
    }
    cout << "\n";
}

char checkWinner(const Board &b)
{
    static const int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (auto &w : wins)
    {
        if (b[w[0]] != ' ' && b[w[0]] == b[w[1]] && b[w[1]] == b[w[2]])
            return b[w[0]];
    }
    for (char c : b)
        if (c == ' ')
            return ' ';
    return 'D'; // draw
}

int minimax(Board b, char player, char aiPlayer)
{
    char winner = checkWinner(b);
    if (winner == aiPlayer)
        return 10;
    if (winner == 'D')
        return 0;
    if (winner != ' ')
        return -10;

    int best = (player == aiPlayer) ? INT_MIN : INT_MAX;
    for (int i = 0; i < 9; ++i)
    {
        if (b[i] == ' ')
        {
            b[i] = player;
            int score = minimax(b, (player == 'X' ? 'O' : 'X'), aiPlayer);
            b[i] = ' ';
            if (player == aiPlayer)
                best = max(best, score);
            else
                best = min(best, score);
        }
    }
    return best;
}

int findBestMove(Board b, char aiPlayer)
{
    int bestVal = INT_MIN;
    int bestMove = -1;
    for (int i = 0; i < 9; ++i)
    {
        if (b[i] == ' ')
        {
            b[i] = aiPlayer;
            int moveVal = minimax(b, (aiPlayer == 'X' ? 'O' : 'X'), aiPlayer);
            b[i] = ' ';
            if (moveVal > bestVal)
            {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

int getHumanMove(const Board &b)
{
    while (true)
    {
        cout << "Enter your move (1-9): ";
        int pos;
        if (!(cin >> pos))
        {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            cout << "Invalid input. Try again.\n";
            continue;
        }
        if (pos < 1 || pos > 9)
        {
            cout << "Out of range.\n";
            continue;
        }
        if (b[pos - 1] != ' ')
        {
            cout << "Cell occupied.\n";
            continue;
        }
        return pos - 1;
    }
}

void playHumanVsHuman()
{
    Board b;
    b.fill(' ');
    char turn = 'X';
    while (true)
    {
        printBoard(b);
        cout << "Player " << turn << "'s turn.\n";
        int m = getHumanMove(b);
        b[m] = turn;
        char winner = checkWinner(b);
        if (winner != ' ')
        {
            printBoard(b);
            if (winner == 'D')
                cout << "It's a draw!\n";
            else
                cout << "Player " << winner << " wins!\n";
            return;
        }
        turn = (turn == 'X' ? 'O' : 'X');
    }
}

void playHumanVsAI(bool humanIsX = true)
{
    Board b;
    b.fill(' ');
    char human = humanIsX ? 'X' : 'O';
    char ai = (human == 'X') ? 'O' : 'X';
    char turn = 'X';
    while (true)
    {
        printBoard(b);
        if (turn == human)
        {
            cout << "Your turn (" << human << ").\n";
            int m = getHumanMove(b);
            b[m] = human;
        }
        else
        {
            cout << "Computer (" << ai << ") is thinking...\n";
            int move = findBestMove(b, ai);
            if (move == -1)
            {
                // fallback
                for (int i = 0; i < 9; ++i)
                    if (b[i] == ' ')
                    {
                        move = i;
                        break;
                    }
            }
            b[move] = ai;
        }
        char winner = checkWinner(b);
        if (winner != ' ')
        {
            printBoard(b);
            if (winner == 'D')
                cout << "It's a draw!\n";
            else if (winner == human)
                cout << "You win!\n";
            else
                cout << "Computer wins!\n";
            return;
        }
        turn = (turn == 'X' ? 'O' : 'X');
    }
}

// Autotest: AI vs AI sequence to verify program runs non-interactively
int runAutoTest()
{
    Board b;
    b.fill(' ');
    char turn = 'X';
    while (true)
    {
        int move = findBestMove(b, turn);
        if (move == -1)
        {
            // pick first free
            for (int i = 0; i < 9; ++i)
                if (b[i] == ' ')
                {
                    move = i;
                    break;
                }
        }
        if (move == -1)
            break;
        b[move] = turn;
        char winner = checkWinner(b);
        if (winner != ' ')
        {
            printBoard(b);
            if (winner == 'D')
                cout << "AutoTest: draw\n";
            else
                cout << "AutoTest: " << winner << " wins\n";
            return 0;
        }
        turn = (turn == 'X' ? 'O' : 'X');
    }
    printBoard(b);
    cout << "AutoTest: ended\n";
    return 0;
}

int main(int argc, char **argv)
{
    // Check environment and args for color toggle or autotest
    const char *noColorEnv = getenv("NO_COLOR");
    if (noColorEnv != nullptr)
        g_use_color = false;

    if (argc > 1)
    {
        string a = argv[1];
        if (a == "autotest")
            return runAutoTest();
        if (a == "--no-color")
            g_use_color = false;
    }

    cout << "Tic Tac Toe\n";
    cout << "1) Human vs Human\n";
    cout << "2) Human vs Computer\n";
    cout << "Choose mode: ";
    int mode;
    if (!(cin >> mode))
        return 0;
    if (mode == 1)
        playHumanVsHuman();
    else if (mode == 2)
    {
        cout << "Play as X (first)? (y/n): ";
        char c;
        cin >> c;
        bool humanIsX = (c == 'y' || c == 'Y');
        playHumanVsAI(humanIsX);
    }
    else
        cout << "Unknown mode\n";
    return 0;
}
