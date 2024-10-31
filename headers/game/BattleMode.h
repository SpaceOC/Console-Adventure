#ifndef CONSOLE_ADVENTURE_GAME_BATTLE_MODE
#define CONSOLE_ADVENTURE_GAME_BATTLE_MODE

#include <string>
#include <map>
#include <vector>
#include "game/Player.h"
#include "game/ItemManager.h"

// Используется для defaultEnemyInfo и enemy
struct DEnemyInfo {
    std::string name;
    int id;
    int health;
    int strength;
};

class BattleMode {
    private:
        static inline size_t enemyVectorPos(const std::string& name);
        const static inline std::vector<DEnemyInfo> defaultEnemyInfo = {
            {"Skeleton", IENEMY_SKELETON, 75, 6},
            {"Zombie", IENEMY_ZOMBIE, 150, 3},
            {"Ghost", IUNKNOWN_ENEMY, 25, 1},
            {"Evil Knight", IENEMY_EVIL_KNIGHT, 225, 2},
            {"idkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk", -1, 1, 1} // Его никогда нельзя будет встретить в игре
        };
        static inline DEnemyInfo enemy;
        static inline std::string message;
        static bool playerWin();
        static bool enemyWin();
        static std::string text();
        static bool playerCommandIsExist(std::string command);
    public:
        static inline bool playerInBattleMode = false;
        static void battle();
        static void playerAttack();
        static void enemyAttack();
        static void playerItemMenu();
};

#endif