#ifndef CONSOLE_ADVENTURE_GAME_PLAYER
#define CONSOLE_ADVENTURE_GAME_PLAYER

#include <string>
#include "game/Map.h"
#include "game/ItemManager.h"

class Player {
    private:
        static std::map<int, std::string> handlerInvMenu();
        static size_t itemStorageVectorPos(std::string itemName);

        static inline int where(int key);

        static bool hiWall(int a, bool rightSide);
        static void hiItem(int a, bool rightSide);
        static void hiEnemy(int a, bool rightSide);
        static void hiDoor(int a, bool rightSide);

        static bool thisIsRightLeft(int pos);
    public:
        static inline int x = 5;
        static inline int y = 9;
        static inline PlayerItemData sword;
        static inline PlayerItemData armor;
        static inline PlayerItemData shield;
        static inline int maxHealth = 100;
        static inline int health = 100;
        static inline int defaultStrength = 2;
        static inline int strength = defaultStrength;
        static inline float defense = 1.0f;
        static inline std::vector<PlayerItemData> itemStorage;
        static inline bool isDead = false;

        static void move(int pos);
        static void addPlayerOnMap();
        static void restart();
        static void INVMenu();
        static void useItem(std::string itemName);

        static void clearInventory();
        static void deleteItem(std::string itemName);
        static std::string inventoryString();
};

#endif