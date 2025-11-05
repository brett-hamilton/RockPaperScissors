#include <iostream>
#include <random>
#include <string>

enum class Outcome { win, lose, tie};
enum class Choice { rock, paper, scissors};

void print_options();
void get_user_input(int* input);
void print_prompt();
int get_computer_choice();
Outcome get_outcome(Choice user_choice, Choice computer_choice);
void print_score(int user_score, int computer_score);
Choice convert_input(int input);
std::string choice_to_string(Choice choice);

int main() {
    auto game_over = false;
    int user_score = 0;
    int computer_score = 0;

    while (!game_over) {
        // Display score
        std::cout << "----------------" << std::endl;
        print_score(user_score, computer_score);

        // Display menu
        std::cout << "  Options" << std::endl;
        std::cout << "----------------" << std::endl;
        print_options();
        std::cout << "----------------" << std::endl;

        // Get user input
        print_prompt();
        int user_input;
        get_user_input(&user_input);
        Choice user_choice = convert_input(user_input);

        // Determine computer selection
        const int computer_input = get_computer_choice();
        Choice computer_choice = convert_input(computer_input);
        std::cout << "Computer chose: " << choice_to_string(computer_choice) << std::endl;

        // Determine winner
        Outcome outcome = get_outcome(user_choice, computer_choice);

        // Update score
        if (outcome == Outcome::win) {
            user_score++;
        } else if (outcome == Outcome::lose) {
            computer_score++;
        }

        // Determine if user or computer has won, else continue game loop
        if (user_score >= 2) {
            std::cout << "You win!" << std::endl;
            game_over = true;
        } else if (computer_score >= 2) {
            std::cout << "You lose!" << std::endl;
            game_over = true;
        }
    }

    return 0;
}

void print_options() {
    std::cout << "  1 - Rock" << std::endl;
    std::cout << "  2 - Paper" << std::endl;
    std::cout << "  3 - Scissors" << std::endl;
}

void print_prompt() {
    std::cout << "Enter choice: ";
}

void get_user_input(int* input) {
    std::cin >> *input;
}

int get_computer_choice() {
    // Choose random number between 1 and 3, inclusive
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 3);
    return distribution(gen);
}

Choice convert_input(int input) {
    Choice choice;

    switch (input) {
        case 1:
            choice = Choice::rock;
            break;
        case 2:
            choice = Choice::paper;
            break;
        case 3:
            choice = Choice::scissors;
            break;
    }

    return choice;
}

std::string choice_to_string(Choice choice) {
    switch (choice) {
        case Choice::rock: return "Rock";
        case Choice::paper: return "Paper";
        case Choice::scissors: return "Scissors";
        default: return "Unknown";
    }
}

void print_score(int user_score, int computer_score) {
    std::cout << "  User Score: " << user_score << " | Computer Score: " << computer_score << std::endl;
}

Outcome get_outcome(Choice user_choice, Choice computer_choice) {
    // 1 - Rock beats 3 - Scissors
    // 2 - Paper beats 1 - Rock
    // 3 - Scissors beats 2 - Paper

    if (user_choice == computer_choice) {
        return Outcome::tie;
    }

    switch (user_choice) {
        case Choice::rock:
            if (computer_choice == Choice::scissors) {
                return Outcome::win;
            }
        case Choice::paper:
            if (computer_choice == Choice::rock) {
                return Outcome::win;
            }
        case Choice::scissors:
            if (computer_choice == Choice::paper) {
                return Outcome::win;
            }
        default:
            std::cout << "Invalid choice!" << std::endl;
    }

    return Outcome::lose;
}