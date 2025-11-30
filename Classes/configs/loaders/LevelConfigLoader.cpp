#include "LevelConfigLoader.h"

LevelConfig* LevelConfigLoader::loadLevelConfig(int levelId)
{
    // 从配置文件加载(目前返回默认配置)
    return createDefaultLevelConfig();
}

LevelConfig* LevelConfigLoader::createDefaultLevelConfig()
{
    LevelConfig* config = new LevelConfig();
    config->setLevelId(1);
    config->setLevelName("Level 1");

    // 设置默认卡牌配置（示例）
    std::vector<int> playFieldCards;
    std::vector<int> stackCards;

    // 根据实际需求设置卡牌
    config->setPlayFieldCards(playFieldCards);
    config->setStackCards(stackCards);

    return config;
}