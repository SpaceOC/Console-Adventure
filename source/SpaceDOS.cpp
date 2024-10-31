/*
#include "SpaceDOS.h"
#include <iostream>
#include "game.h"


const char* dllName() { return "Console Adventure"; }

bool __dllLoader() {
    return true;
}

const char* addCommands_functions() {
    return "consoleAdventureMenu";
}

const char* addCommands_description(const char* funcName) {
    if ("consoleAdventureMenu") return "game - Console Adventure";
    return "Unknown";
}

const char* addCommands_name(const char* funcName) {
    if ("consoleAdventureMenu") return "console_adventure";
    return "Unknown";
}
*/