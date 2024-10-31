#include <iostream>
#include "game/ItemManager.h"
#include "game/Helper.h"

PlayerItemData ItemManager::addRandomMapItem(std::vector<PlayerItemData>& itemStorage) {
    int daRandom = rand() % itemsList.at(IMAP).size();
    std::string randomItem = itemsList.at(IMAP).at(daRandom).name;
    int randomItemPercent = itemsList.at(IMAP).at(daRandom).percent;
    for (int a = 0; a < 5; a++) {
        int random = rand() % 101;
        if (random < randomItemPercent) {
            daRandom = rand() % itemsList.at(IMAP).size();
            randomItem = itemsList.at(IMAP).at(daRandom).name;
            randomItemPercent = itemsList.at(IMAP).at(daRandom).percent;
        }
        else {
            break;
        }
    }

    PlayerItemData playerItem = {defaultItemsInfo.at(randomItem), 1, 0, randomItem};

    for (auto& item : itemStorage) {
        if (item.defaultName == randomItem) {
            if ((item.amount == 1 && !item.item.stack) || item.amount >= item.item.maxStack)
                return addRandomMapItem(itemStorage);
            else if (item.amount > 0 && item.item.stack) {
                item.amount++;
                return {};
            }
        }
    }
    Helper::message = "You picked " + randomItem;
    return playerItem;
}

PlayerItemData ItemManager::addRandomEnemyItem(const int& enemy, std::vector<PlayerItemData>& itemStorage) {
    if (enemy == -1) return {};
    int daRandom = rand() % itemsList.at(enemy).size();
    std::string randomItem = itemsList.at(enemy).at(daRandom).name;
    int randomItemPercent = itemsList.at(enemy).at(daRandom).percent;
    for (int a = 0; a < 4; a++) {
        int random = rand() % 101;
        if (random < randomItemPercent) {
            daRandom = rand() % itemsList.at(enemy).size();
            randomItem = itemsList.at(enemy).at(daRandom).name;
            randomItemPercent = itemsList.at(enemy).at(daRandom).percent;
        }
        else if (a == 3) return {};
        else {
            break;
        }
    }

    PlayerItemData playerItem = {defaultItemsInfo.at(randomItem), 1, 0, randomItem};

    for (auto& item : itemStorage) {
        if (item.defaultName == randomItem) {
            if ((item.amount == 1 && !item.item.stack) || item.amount >= item.item.maxStack)
                return addRandomMapItem(itemStorage);
            else if (item.amount > 0 && item.item.stack) {
                item.amount++;
                return {};
            }
        }
    }
    Helper::message = "The enemy is defeated | You picked " + randomItem;
    return playerItem;
}

bool ItemManager::isWeapon(std::string itemName) {
    return (defaultItemsInfo.at(itemName).type == ItemType::WEAPON);
}

bool ItemManager::isHealther(std::string itemName) {
    return (defaultItemsInfo.at(itemName).type == ItemType::HEALTH);
}

bool ItemManager::isArmor(std::string itemName) {
    return (defaultItemsInfo.at(itemName).type == ItemType::ARMOR);
}

bool ItemManager::isShield(std::string itemName) {
    return (defaultItemsInfo.at(itemName).type == ItemType::SHIELD);
}