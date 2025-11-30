#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

#include "cocos2d.h"
#include "../models/LevelConfig.h"

// 关卡配置加载器
class LevelConfigLoader
{
public:
    // 加载关卡配置
    static LevelConfig* loadLevelConfig(int levelId);

    // 创建默认关卡配置
    static LevelConfig* createDefaultLevelConfig();

private:
    LevelConfigLoader() {}
    virtual ~LevelConfigLoader() {}
};

#endif // __LEVEL_CONFIG_LOADER_H__