#pragma once
#include "CardModel.h"
#include <vector>

// 回退模型
struct UndoStep {
    enum Type {
        UT_STACK_REPLACE,  // 手牌区卡牌
        UT_MATCH_PLAYFIELD // 主牌区卡牌
    };

    Type type;
    int cardId;
    cocos2d::Vec2 oldPos;
    int oldTopCardId = -1;
    cocos2d::Vec2 oldTopPos;
};

class UndoModel {
public:
    UndoModel() = default;
    ~UndoModel() = default;

    void pushStep(const UndoStep& step);

    bool popStep(UndoStep& outStep);

    void clear();

    bool hasUndo() const { return !_steps.empty(); }

private:
    std::vector<UndoStep> _steps;
};