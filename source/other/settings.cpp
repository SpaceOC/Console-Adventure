#include "other\settings.h"

bool Settings::isMoveKey(int key) {
    for (const auto& element : keys) {
        if (key == element.second.at(0) || key == element.second.at(1)) return true;
    }
    return false;
}
bool Settings::isInventoryKey(int key) {
    for (const auto& element : keys) {
        if (key == element.second.at(0) || key == element.second.at(1)) return true;
    }
    return false;
}
bool Settings::isAttackKey(int key) {
    for (const auto& element : keys) {
        if (key == element.second.at(0) || key == element.second.at(1)) return true;
    }
    return false;
}
bool Settings::isItemsKey(int key) {
    for (const auto& element : keys) {
        if (key == element.second.at(0) || key == element.second.at(1)) return true;
    }
    return false;
}
bool Settings::isDefenseKey(int key) {
    for (const auto& element : keys) {
        if (key == element.second.at(0) || key == element.second.at(1)) return true;
    }
    return false;
}

std::vector<int> Settings::getKey(std::string keyName) {
    return keys.at(keyName);
}