#ifndef CONSOLE_ADVENTURE_GAME_MAP
#define CONSOLE_ADVENTURE_GAME_MAP

#include <string>
#include <map>
#include "game/Textures.h"

class Map {
    private:
        // первый int - отвечает за "уровень". 0 или 8 - только стены и дверь. Остальное - враги, предметы и т.д
        static inline std::map<int, std::map<int, std::string>> map;
        static std::string whatSet(int partMap);
        static std::string randomWhatSet(int partMap);

        /**
         * Проверяет есть ли ВООБЩЕ враги на карте
         * @return true если враги есть на карте
         */
        static bool betterEnemyCheck();
    public:
        static inline bool firstMessageDoor;
        static inline int enemys = 0;
        static inline double mapLVL = 0.05;
        static inline int mapLVLTUI = 1;
        static inline int maxSizeMap = 10;
        static inline double maxMapLVL = 1.5;

        static void draw();
        static void change(int levelMap, int partMap, std::string newPartMap);
        static void helloDoor();
        static std::string see();
        static std::string getPartMap(int levelMap, int partMap);
        static std::map<int, std::map<int, std::string>> getMap();
        static std::string addSpace(int partMap);
};

#endif