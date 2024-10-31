#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "game/BattleMode.h"
#include "game/Player.h"

size_t BattleMode::enemyVectorPos(const std::string& name) {
    for (size_t i = 0; i <= defaultEnemyInfo.size(); i++) {
        if (defaultEnemyInfo.at(i).name == name) {
            return i;
        }
    }
    return -1;
}

std::string BattleMode::text() {
    std::string newtemp = " --- BATTLE MODE ---\n";
    std::string temp = newtemp
    + "Your Enemy: " + enemy.name + "\n"
    + "Enemy HP: " + std::to_string(enemy.health) + " | Enemy Strenght: " + std::to_string(enemy.strength) + '\n'
    + "\n\n"
    + "Your HP: " + std::to_string(Player::health) + "\n"
    + " --- [ Message ] ---\n" + message;
    return temp;
}

bool BattleMode::playerCommandIsExist(std::string command) {
    return (command == "Attack" || command == "Item" || command == "Defend");
}
bool BattleMode::playerWin() { return (enemy.health <= 0); }
bool BattleMode::enemyWin() { return (Player::health <= 0); }

void BattleMode::battle() {
    int randomPos = rand() % defaultEnemyInfo.size();
    enemy = defaultEnemyInfo.at(randomPos - (randomPos == 0 ? 0 : 1));
    enemy.health = enemy.health + rand() % (1 + static_cast<int>(10 * Map::mapLVL));
    playerInBattleMode = true;
    while (true) {
        std::cout << text() << std::endl;
        message = "";
        std::string temp; std::cin >> temp;
        if (temp == "Attack") { playerAttack(); }
        else if (temp == "Item") { playerItemMenu(); }
        else { enemyAttack(); }

        if (playerWin() || enemyWin()) { message = ""; playerInBattleMode = false; enemy = {}; Map::enemys--; break; }
    }
    if (enemyWin()) { Player::isDead = true; playerInBattleMode = false; }
    else {
        if (enemy.id == -1) return;
        PlayerItemData newItem = ItemManager::addRandomEnemyItem(enemy.id, Player::itemStorage);
        if (!newItem.defaultName.empty() && newItem.defaultName != Player::sword.defaultName && newItem.defaultName != Player::armor.defaultName)
            Player::itemStorage.push_back(newItem);
    }
}

void BattleMode::playerAttack() {
    const int randomPHP = (rand() % 15 + 1) * Player::strength;
    enemy.health = enemy.health - randomPHP;
    message += "After an enemy attack, his health is reduced by -" + std::to_string(randomPHP) + "\n";
    enemyAttack();
    system("cls");
}

void BattleMode::enemyAttack() {
    const int randomEHP = static_cast<int>(((rand() % 3 + 1) * enemy.strength) / Player::defense);
    Player::health -= randomEHP;
    message += "You've lost " + std::to_string(randomEHP) + " HP\n";
    system("cls");
}

void BattleMode::playerItemMenu() {
    Player::INVMenu();
    enemyAttack();
}