#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>

// Global constants for easy modification
const int ITERATIONS = 5;                 // Number of reaction tests
const int MIN_DELAY_MS = 4000;            // Minimum random delay in milliseconds
const int MAX_DELAY_MS = 8000;            // Maximum random delay in milliseconds

void waitForInput(const std::string& prompt) {
    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void measureReactionTimes() {
    std::vector<int> reactionTimes;
    std::srand(static_cast<unsigned>(std::time(0))); // Seed random number generator

    for (int i = 1; i <= ITERATIONS; ++i) {
        std::cout << "Iteration " << i << "/" << ITERATIONS << ": Press ENTER to start...\n";
        waitForInput("");

        std::cout << "Get ready! Pay attention...\n";

        // Random delay between MIN_DELAY_MS and MAX_DELAY_MS
        int randomDelay = MIN_DELAY_MS + std::rand() % (MAX_DELAY_MS - MIN_DELAY_MS + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(randomDelay));

        std::cout << "NOW! Press ENTER as quickly as possible!\n";

        // Start timer
        auto startTime = std::chrono::high_resolution_clock::now();

        // Wait for user input
        waitForInput("");

        // Stop timer
        auto endTime = std::chrono::high_resolution_clock::now();

        // Calculate reaction time
        int reactionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "Reaction time: " << reactionTime << " ms\n";
        reactionTimes.push_back(reactionTime);
    }

    // Calculate and display the average reaction time
    int total = std::accumulate(reactionTimes.begin(), reactionTimes.end(), 0);
    double average = static_cast<double>(total) / ITERATIONS;
    std::cout << "\nAverage reaction time: " << average << " ms\n";

    std::cout << "\nReturning to the menu...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
    while (true) {
        std::cout << "Reaction Time Tester\n";
        std::cout << "1. Start\n";
        std::cout << "2. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        if (choice == 1) {
            measureReactionTimes();
        } else if (choice == 2) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}