#ifndef CONSOLE_ADVENTURE_OTHER_SETTINGS
#define CONSOLE_ADVENTURE_OTHER_SETTINGS

#include <string>
#include <map>
#include <vector>

const static inline std::map<std::string, std::vector<int>> keys = {
    {"UP", {87, 38}},
    {"DOWN", {83, 40}},
    {"LEFT", {65, 37}},
    {"RIGHT", {68, 39}},

    {"INVENTORY", {73, -1}},

    {"ATTACK", {46, -1}},
    {"ITEMS", {48, -1}},
    {"DEFENSE", {47, -1}},
};

class Settings {
    public:
        static bool isMoveKey(int key);
        static bool isInventoryKey(int key);
        static bool isAttackKey(int key);
        static bool isItemsKey(int key);
        static bool isDefenseKey(int key);

        static std::vector<int> getKey(std::string keyName);
};

#endif