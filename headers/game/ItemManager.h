#ifndef CONSOLE_ADVENTURE_GAME_ITEM_MANAGER
#define CONSOLE_ADVENTURE_GAME_ITEM_MANAGER

#include <string>
#include <vector>
#include <map>

#define IMAP 0
#define IENEMY_ZOMBIE 1
#define IENEMY_SKELETON 2
#define IENEMY_EVIL_KNIGHT 3
#define IUNKNOWN_ENEMY -1

enum ItemType {
    WEAPON,
    HEALTH,
    ARMOR,
    SHIELD
};

// Данные предмета
struct ItemData {
    ItemType type; // Тип предмета
    float strength; // Сила
    int medicability; // Лечимость (ну............... 💀) от данного предмета... Чем выше - тем лучше
    float protectability; // Защищаемость данного предмета. Чем выше - лучше
    bool stack; // Определяет возможно ли носить сразу несколько таких предметов
    int maxStack = 1; // Максимальное разрешённое количество предметов, которое можно носить с собой
};

struct PlayerItemData {
    ItemData item; // Данные предмета
    int amount; // Количество предметов
    double lvl; // Уровень предмета
    std::string defaultName; // Обычное (стандартное) имя предмета при его получении
    std::string customName = ""; // Имя предмета, которое задаёт сам игрок
    bool used = false; // Используется ли данный предмет
};

// Используется для itemsList
struct ItemListsData {
    std::string name; // Имя предмета
    int percent; // Шанс получения/выпадения
};

class ItemManager {
    public:
        const static inline std::map<std::string, ItemData> defaultItemsInfo = {
            // Health items [map]
            {"Bread", {ItemType::HEALTH, 0, 12, 0, true, 64}},
            {"Apple", {ItemType::HEALTH, 0, 5, 0, true, 128}},
            {"Iron Apple", {ItemType::HEALTH, 0, 15, 0, true, 28}},
            {"Golden Apple", {ItemType::HEALTH, 0, 25, 0, true, 16}},

            // Health items [enemy]
            {"Diamond Apple", {ItemType::HEALTH, 0, 59, 0, true, 8}},

            // Weapon items [map]
            {"Paper Sword", {ItemType::WEAPON, 0.5, 0, 0.15, false}},
            {"Wooden Sword", {ItemType::WEAPON, 1.5, 0, 0.45, false}},

            // Weapon items [enemy]
            {"Skeleton Sword", {ItemType::WEAPON, 2.3, 0, 0.95, false}},

            // Shield items [map]
            {"Paper Shield", {ItemType::SHIELD, 0, 0, 0.65, false}},
            {"Stone Shield", {ItemType::SHIELD, 0.3, 0, 1, false}},

            // Shield items [enemy]
            {"Magic Shield", {ItemType::SHIELD, 0.75, 12, 1.7, false}},

            // Armor items [map]
            {"Wooden Armor", {ItemType::ARMOR, 0, 0, 1.35, false}},
        };
        const static inline std::map<int, std::vector<ItemListsData>> itemsList = {
            {IMAP, {
                {"Apple", 85},
                {"Golden Apple", 20},
                {"Iron Apple", 30},
                {"Bread", 65},
                {"Paper Shield", 50},
                {"Wooden Sword", 45},
                {"Wooden Armor", 20}
                }
            },
            {IENEMY_SKELETON, {
                {"Skeleton Sword", 15},
                {"Stone Shield", 20},
                {"Golder Apple", 25}
                }
            },
            {IENEMY_ZOMBIE, {
                {"Stone Shield", 20}
                }
            },
            {IENEMY_EVIL_KNIGHT, {
                {"Stone Shield", 20},
                {"Magic Shield", 10}
                }
            }
        };

        static PlayerItemData addRandomMapItem(std::vector<PlayerItemData>& itemStorage);
        static PlayerItemData addRandomEnemyItem(const int& enemy, std::vector<PlayerItemData>& itemStorage);
        //static void deleteItem(std::string itemName);
        static bool isWeapon(std::string itemName);
        static bool isHealther(std::string itemName);
        static bool isArmor(std::string itemName);
        static bool isShield(std::string itemName);
        static std::map<int, std::string> handlerItemsMenu();
        static std::string playerInventory();
};

#endif