#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "game.h"

std::vector<std::string> gameLogo = {
    R"(CONSOLE)",
    R"(ADVENTURE)"
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    for (auto vs : gameLogo) {
        std::cout << vs << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }
    std::cout << "by SpaceOC\nEnter 'Start' to start adventure: ";
    std::string temp; std::cin >> temp;
    if (temp == "Start")
        startGame();
    if (temp == "Exit")
        std::cout << "Goodbye" << '\n';
    return 0;
}