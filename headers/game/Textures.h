#ifndef CONSOLE_ADVENTURE_GAME_TEXTURES
#define CONSOLE_ADVENTURE_GAME_TEXTURES

#include <string>
#include <map>

class TexturesMap {
    private:
        static inline std::map<std::string, std::map<std::string, std::string>> textures {
        // Вы не понимаете))) Это самая графонистая игра на всём свете))))
            {"LOW",
                {
                    {"WALL", "#"},
                    {"AIR", "."},
                    {"ITEM", "I"},
                    {"PLAYER", "P"},
                    {"ENEMY", "E"},
                    {"DOOR", ":"},
                }
            },
            // Неееет(((
            {"MED",
                {
                    {"WALL", ""},
                }
            },
            // АААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААА
            {"HIGH",
                {
                    {"WALL", ""},
                }
            }
        };
        static inline std::string currentTextureLevel = "LOW";
    public:
        static std::string getTexture(std::string textureName, std::string textureLevel = "LOW");
        static void changeTextures();

        static std::map<std::string, std::map<std::string, std::string>> getTextures();
};

#endif