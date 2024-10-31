#include <iostream>
#include <windows.h>
#include <conio.h>
#include "other\settings.h"
#include "game\Player.h"
#include "game\ItemManager.h"
#include "game\Helper.h"
//#include "game.h"

void gameover();
void keyMove();

void startGame() {
    Map::draw();
    Player::restart();
    Player::addPlayerOnMap();
    while(!Player::isDead) {
        Map::helloDoor();
        system("cls");
        std::cout << "Version: 0.2 Alpha | LVL: " + std::to_string(Map::mapLVLTUI)
            + "\nMap: \n"
            + Map::see() + "\n\n"
            + "X: " + std::to_string(Player::x) + " | Y: " + std::to_string(Player::y)
            + "\nMessage: " + Helper::message
            + "\nHealth: " + std::to_string(Player::health);
        keyMove();
    }
    if (Player::isDead) {
        Player::clearInventory();
        gameover();
    }
}

void keyMove() {
    bool waiting = true;
    while (waiting) {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                case 'A':
                    Player::move(Settings::getKey("LEFT").at(0));
                    waiting = false;
                    break;
                case 'd':
                case 'D':
                    Player::move(Settings::getKey("RIGHT").at(0));
                    waiting = false;
                    break;
                case 'w':
                case 'W':
                    Player::move(Settings::getKey("UP").at(0));
                    waiting = false;
                    break;
                case 's':
                case 'S':
                    Player::move(Settings::getKey("DOWN").at(0));
                    waiting = false;
                    break;
                case 'e':
                case 'E':
                    Player::INVMenu();
                    waiting = false;
                    break;
            }
        }
    }
}

void gameover() {
    std::cout << "Game Over" << std::endl;
    std::cout << "Restart? (Y/N) \t";
    std::string temp; std::cin >> temp;
    if (temp == "Y") {
        system("cls");
        startGame();
    }
}