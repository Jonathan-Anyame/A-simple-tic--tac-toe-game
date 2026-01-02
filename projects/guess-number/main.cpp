// Guess the Number - beginner friendly C++ project
// The program selects a random number and the user tries to guess it.
#include <iostream>
#include <random>
#include <limits>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    int secret = dist(gen);

    std::cout << "Welcome to Guess the Number! I'm thinking of a number between 1 and 100." << std::endl;
    int attempts = 0;

    while (true)
    {
        std::cout << "Enter your guess: ";
        int guess;
        if (!(std::cin >> guess))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid integer." << std::endl;
            continue;
        }
        ++attempts;
        if (guess == secret)
        {
            std::cout << "Correct! You guessed the number in " << attempts << " attempts." << std::endl;
            break;
        }
        else if (guess < secret)
        {
            std::cout << "Too low." << std::endl;
        }
        else
        {
            std::cout << "Too high." << std::endl;
        }
    }

    return 0;
}
