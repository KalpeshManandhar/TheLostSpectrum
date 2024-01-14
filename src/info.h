#pragma once

static const char *levelDirs[] = {
    "./assets/levelmaps/levelA",
    "./assets/levelmaps/shard",
};

struct LevelInfo{
    bool enemies;
    const char *levelDir;
    const char *interactFiles[];
};

static LevelInfo level1INFO = {
    true,
    "./assets/levelmaps/levelA",
    {
        "./assets/npcs/npc1.txt",
        "./assets/npcs/npc2.txt",
    }
};
static LevelInfo level2INFO = {
    false,
    "./assets/levelmaps/shard",
    {
        "./assets/npcs/npc3.txt",
    }
};