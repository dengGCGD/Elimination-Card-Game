#pragma once
#include "cocos2d.h"
#include "../models/GameModel.h"
#include "../services/UndoService.h"
#include "../views/StackView.h"
#include "../managers/GameManager.h"

// 手牌区控制器
class StackController : public cocos2d::Ref {
public:
    CREATE_FUNC(StackController);
    ~StackController() override = default;

    bool init();
    bool init(GameManager* gameManager);

    void bindView(StackView* view);

    bool handleCardClick(int cardId);

    StackView* getStackView() const { return _stackView; }

private:
    GameManager* _gameManager = nullptr;
    StackView* _stackView = nullptr;
};