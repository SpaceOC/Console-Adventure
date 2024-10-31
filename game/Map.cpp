#include <iostream>
#include "game/Map.h"
#include "game/Helper.h"

bool Map::betterEnemyCheck() {
    for (const auto& e : map) {
        for (const auto& h : e.second) {
            if (h.first == 0 || h.first >= maxSizeMap) continue;
            std::string enemyString = (addSpace(h.first) + TexturesMap::getTexture("ENEMY"));
            if (h.second == enemyString)
                return true;
        }
    }
    return false;
}

std::string Map::addSpace(int partMap) {
    std::string space = " ERROR ";
    if (partMap == 0) { space = ""; }
    else if (partMap == maxSizeMap - 1) { space = " "; }
    else { space = " "; }
    return space;
}

std::string Map::randomWhatSet(int partMap) {
    std::string temp;
    int percentRandom = rand() % 100;
    if (percentRandom <= 15) { temp = addSpace(partMap) + TexturesMap::getTexture("ITEM"); }
    if (percentRandom > 15 && percentRandom < 5 + static_cast<int>(15 + 12 * mapLVL)) { 
        temp = addSpace(partMap) + TexturesMap::getTexture("ENEMY");
        enemys++;
    }
    if (percentRandom >= 5 + static_cast<int>(15 + 12 * mapLVL)) { temp = addSpace(partMap) + TexturesMap::getTexture("AIR"); }
    return temp;
};

std::string Map::whatSet(int partMap) {
    std::string temp;
    if (partMap == 0 || partMap >= maxSizeMap) { temp = addSpace(partMap) + TexturesMap::getTexture("WALL"); }
    else if (partMap > 0 && partMap < maxSizeMap) { temp = randomWhatSet(partMap); }
    return temp;
};

void Map::draw() {
    for (int i = 0; i <= maxSizeMap; i++) {
        for (int k = 0; k <= maxSizeMap; k++) {
            if (k == 0 || k == maxSizeMap) {
                map[k][i] = TexturesMap::getTexture("WALL") + " ";
            }
            else {
                map[k][i] = whatSet(i);
            }
        }
    }
    helloDoor();
}

void Map::change(int levelMap, int partMap, std::string newPartMap) {
    map[levelMap][partMap] = addSpace(partMap) + newPartMap;
}

std::string Map::see() {
    std::string temp;
    for (int i = 0; i <= maxSizeMap; i++) {
        for (int k = 0; k <= maxSizeMap; k++) {
            temp += map[i][k];
        }
        temp += "\n";
    }
    return temp;
}

std::string Map::getPartMap(int levelMap, int partMap) {
    return map[levelMap][partMap];
}


std::map<int, std::map<int, std::string>> Map::getMap() {
    return map;
}

void Map::helloDoor() {
    if (firstMessageDoor) return;
    if (!betterEnemyCheck()) enemys = 0;
    if (enemys == 0) {
        map[0][static_cast<int>(maxSizeMap / 2)] = TexturesMap::getTexture("DOOR") + addSpace(static_cast<int>(maxSizeMap / 2));
        Helper::message = "Door unlocked!";
        firstMessageDoor = true;
    }
}