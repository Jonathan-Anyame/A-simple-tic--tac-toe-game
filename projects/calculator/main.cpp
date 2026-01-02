// Simple Calculator - beginner friendly C++ project
// Supports +, -, *, / on two numbers and handles division by zero.
#include <iostream>
#include <limits>

int main()
{
    std::cout << "Simple Calculator" << std::endl;
    double a, b;
    char op;

    while (true)
    {
        std::cout << "Enter expression (e.g. 2.5 * 4) or 'q' to quit: ";
        if (!(std::cin >> a))
        {
            // check for quit
            std::cin.clear();
            char c;
            if (std::cin >> c && (c == 'q' || c == 'Q'))
                break;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again." << std::endl;
            continue;
        }
        if (!(std::cin >> op >> b))
        {
            std::cout << "Incomplete expression. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        double result;
        bool valid = true;
        switch (op)
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0)
            {
                std::cout << "Error: division by zero." << std::endl;
                valid = false;
            }
            else
                result = a / b;
            break;
        default:
            std::cout << "Unsupported operator: " << op << std::endl;
            valid = false;
        }

        if (valid)
            std::cout << "= " << result << std::endl;
    }

    return 0;
}
