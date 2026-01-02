// Rock Paper Scissors - beginner friendly C++ project
// Play against the computer. First to reach a score wins.
#include <iostream>
#include <random>
#include <string>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);
    const std::string names[3] = {"Rock", "Paper", "Scissors"};

    int playerScore = 0, compScore = 0;
    const int target = 3;

    std::cout << "Rock-Paper-Scissors (best of 5, first to 3)" << std::endl;
    while (playerScore < target && compScore < target)
    {
        std::cout << "Choose (r)ock, (p)aper, (s)cissors or q to quit: ";
        char c;
        if (!(std::cin >> c))
            break;
        if (c == 'q' || c == 'Q')
            break;
        int player;
        if (c == 'r' || c == 'R')
            player = 0;
        else if (c == 'p' || c == 'P')
            player = 1;
        else if (c == 's' || c == 'S')
            player = 2;
        else
        {
            std::cout << "Invalid choice." << std::endl;
            continue;
        }

        int comp = dist(gen);
        std::cout << "Computer chose " << names[comp] << "." << std::endl;

        if (player == comp)
        {
            std::cout << "It's a tie." << std::endl;
        }
        else if ((player + 1) % 3 == comp)
        {
            std::cout << "Computer wins the round." << std::endl;
            ++compScore;
        }
        else
        {
            std::cout << "You win the round!" << std::endl;
            ++playerScore;
        }

        std::cout << "Score: You " << playerScore << " - " << compScore << " Computer" << std::endl;
    }

    if (playerScore > compScore)
        std::cout << "You won the game!" << std::endl;
    else if (compScore > playerScore)
        std::cout << "Computer won the game." << std::endl;
    else
        std::cout << "Game ended early." << std::endl;

    return 0;
}
