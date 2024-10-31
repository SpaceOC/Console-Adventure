#include <iostream>
#include <map>
#include "game/BattleMode.h"
#include "game/Helper.h"
#include "other/settings.h"

size_t Player::itemStorageVectorPos(std::string itemName) {
    size_t realSize = (itemStorage.size() == 1 ? 1 : itemStorage.size() - 1);
    for (size_t i = 0; i <= realSize; i++)
        if (itemStorage.at(i).defaultName == itemName)
            return i;
    return -1;
}

std::map<int, std::string> Player::handlerInvMenu() {
    std::map<int, std::string> temp;
    if (itemStorage.empty()) {
        return {{0, ""}};
    }
    else {
        int i = 0;
        for (const auto& item : itemStorage) {
            temp[i] = item.defaultName;
            i++;
        }
    }
    return temp;
}

int Player::where(int key) {
    for (const auto& el : Settings::getKey("DOWN")) {
        if (key == el) { return 1; }
    }
    for (const auto& el : Settings::getKey("RIGHT")) {
        if (key == el) { return 1; }
    }
    return -1;
}

bool Player::hiWall(int a, bool rightSide) {
    if (rightSide && Map::getMap()[y][x + a] == Map::addSpace(x + a) + TexturesMap::getTexture("WALL")) { return true; }
    else if (!rightSide && Map::getMap()[y + a][x] == TexturesMap::getTexture("WALL") + " ") { return true; }
    return false;
}

void Player::hiItem(int a, bool rightSide) {
    if (rightSide && Map::getMap()[y][x + a] == Map::addSpace(x + a) + TexturesMap::getTexture("ITEM")) {
        PlayerItemData newItem = ItemManager::addRandomMapItem(itemStorage);
        if (!newItem.defaultName.empty() && newItem.defaultName != Player::sword.defaultName && newItem.defaultName != Player::armor.defaultName)
            itemStorage.push_back(newItem);
    }
    else if (!rightSide && Map::getMap()[y + a][x] == Map::addSpace(y + a) + TexturesMap::getTexture("ITEM")) {
        PlayerItemData newItem = ItemManager::addRandomMapItem(itemStorage);
        if (!newItem.defaultName.empty() && newItem.defaultName != Player::sword.defaultName && newItem.defaultName != Player::armor.defaultName)
            itemStorage.push_back(newItem);
    }
}

void Player::hiEnemy(int a, bool rightSide) {
    if (rightSide && Map::getMap()[y][x + a] == Map::addSpace(x + a) + TexturesMap::getTexture("ENEMY")) {
        std::cout << '\n';
        BattleMode::battle();
    }
    else if (!rightSide && Map::getMap()[y + a][x] == Map::addSpace(y + a) + TexturesMap::getTexture("ENEMY")) {
        std::cout << '\n';
        BattleMode::battle();
    }
}

void Player::hiDoor(int a, bool rightSide) {
    if (rightSide && Map::getMap()[y][x + a] == Map::addSpace(x + a) + TexturesMap::getTexture("DOOR")) {
        x = 5; y = 9;
        Map::draw();
        if (Map::mapLVL <= Map::maxMapLVL) { Map::mapLVL += 0.02; }
        Map::mapLVLTUI += 1;
        Map::firstMessageDoor = false;
    }
    else if (!rightSide && Map::getMap()[y + a][x] == TexturesMap::getTexture("DOOR") + " ") {
        x = 5; y = 9;
        Map::draw();
        if (Map::mapLVL <= Map::maxMapLVL) { Map::mapLVL += 0.02; }
        Map::mapLVLTUI += 1;
        Map::firstMessageDoor = false;
    }
}

bool Player::thisIsRightLeft(int pos) {
    for (const auto& el : Settings::getKey("LEFT")) {
        if (pos == el) { return true; }
    }
    for (const auto& el : Settings::getKey("RIGHT")) {
        if (pos == el) { return true; }
    }
    return false;
}

void Player::move(int pos) {
    int tempWhere = where(pos);
    int tempThisIsX = thisIsRightLeft(pos);
    if (!hiWall(tempWhere, tempThisIsX)) {
        Map::change(y, x, TexturesMap::getTexture("AIR"));
        hiEnemy(tempWhere, tempThisIsX);
        hiItem(tempWhere, tempThisIsX);
        hiDoor(tempWhere, tempThisIsX);

        if (tempThisIsX) { x += tempWhere; }
        else { y += tempWhere; }
    }
    Map::change(y, x, TexturesMap::getTexture("PLAYER"));
}

void Player::INVMenu() {
    system("cls");
    std::cout << "\n" + inventoryString() << std::endl;
    if (itemStorage.empty()) {
        Helper::message = "0 items in inventory!";
    }
    else {
        for (const auto& element : handlerInvMenu()) { std::cout << element.first << ". " << element.second << std::endl; }
        std::string temp;
        std::cout << "Enter item name: ";
        while (!(std::cin >> std::ws)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Enter item name: ";
        }
        getline(std::cin, temp);
        useItem(temp);
    }
}

void Player::useItem(std::string itemName) {
    for (const auto& element : handlerInvMenu()) {
        if (itemName == std::to_string(element.first) || itemName == element.second) {
            if (itemName == std::to_string(element.first)) { itemName = element.second; }
            if (ItemManager::isHealther(itemName) && itemStorage.at(itemStorageVectorPos(itemName)).amount >= 1) {
                if (health < maxHealth) { health += ItemManager::defaultItemsInfo.at(itemName).medicability; }
                else if (health >= maxHealth) { health = 100; }
                Helper::message = "You recover " + std::to_string(ItemManager::defaultItemsInfo.at(itemName).medicability) + "HP";
                deleteItem(itemName);
            }
            else if (ItemManager::isWeapon(itemName) && itemStorage.at(itemStorageVectorPos(itemName)).amount == 1) {
                sword = itemStorage.at(itemStorageVectorPos(itemName));
                strength = defaultStrength + ItemManager::defaultItemsInfo.at(itemName).strength;
                deleteItem(itemName);
                Helper::message = "New sword";
            }
            else if (ItemManager::isArmor(itemName) && itemStorage.at(itemStorageVectorPos(itemName)).amount == 1) {
                armor = itemStorage.at(itemStorageVectorPos(itemName));
                defense = itemStorage.at(itemStorageVectorPos(itemName)).item.protectability;
                deleteItem(itemName);
                Helper::message = "New armor";
            }
            else { Helper::message = "NO!"; }
        }
    }
}

void Player::addPlayerOnMap() {
    Map::change(y, x, TexturesMap::getTexture("PLAYER"));
}

void Player::restart() {
    x = 5; y = 9;
    isDead = false; health = 100;
}

void Player::clearInventory() {
    if (!itemStorage.empty())
        for (auto item : itemStorage)
            itemStorage.erase(itemStorage.begin());
}

void Player::deleteItem(std::string itemName) {
    itemStorage.at(itemStorageVectorPos(itemName)).amount -= 1;
    if (itemStorage.at(itemStorageVectorPos(itemName)).amount == 0) {
        auto iter = itemStorage.begin();
        for (const auto& item : itemStorage) {
            if (item.defaultName == itemName) {
                itemStorage.erase(iter);
                break;
            }
            iter++;
        }
    }
}

std::string Player::inventoryString() {
    if (!itemStorage.empty()) {
        std::string temp;
        for (auto item : itemStorage) {
            temp += "Item: " + item.defaultName + (!item.customName.empty() ? "( " + item.customName + " )": "") + " | Amount: " + std::to_string(item.amount) + "\n";
        }
        return temp;
    }
    return "No Items";
}