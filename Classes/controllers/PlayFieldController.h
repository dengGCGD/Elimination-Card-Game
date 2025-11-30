#pragma once
#include "cocos2d.h"
#include "../models/GameModel.h"
#include "../services/UndoService.h"
#include "../views/PlayFieldView.h"
#include "../managers/GameManager.h"

// 主牌区控制器
class PlayFieldController : public cocos2d::Ref {
public:
    CREATE_FUNC(PlayFieldController);
    ~PlayFieldController() override = default;

    bool init();
    bool init(GameManager* gameManager);

    void bindView(PlayFieldView* view);

    bool handleCardClick(int cardId);

private:
    bool checkCardMoveCondition(int cardId) const;

    GameManager* _gameManager = nullptr;
    PlayFieldView* _playFieldView = nullptr;
};