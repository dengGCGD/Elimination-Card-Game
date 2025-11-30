#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include "cocos2d.h"
#include <vector>

// 关卡配置类
class LevelConfig
{
public:
    LevelConfig();
    virtual ~LevelConfig();

    // 获取关卡ID
    int getLevelId() const { return _levelId; }
    void setLevelId(int levelId) { _levelId = levelId; }

    // 获取关卡名称
    std::string getLevelName() const { return _levelName; }
    void setLevelName(const std::string& name) { _levelName = name; }

    // 主牌区初始卡牌配置
    std::vector<int> getPlayFieldCards() const { return _playFieldCards; }
    void setPlayFieldCards(const std::vector<int>& cards) { _playFieldCards = cards; }

    // 手牌区初始卡牌配置
    std::vector<int> getStackCards() const { return _stackCards; }
    void setStackCards(const std::vector<int>& cards) { _stackCards = cards; }

private:
    int _levelId;
    std::string _levelName;
    std::vector<int> _playFieldCards;
    std::vector<int> _stackCards;
};

#endif // __LEVEL_CONFIG_H__