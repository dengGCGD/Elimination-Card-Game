#pragma once
#include "cocos2d.h"
#include "../managers/GameManager.h"
#include "../views/GameView.h"
#include "PlayFieldController.h"
#include "StackController.h"

// 游戏主控制器
class GameController : public cocos2d::Ref {
public:
    CREATE_FUNC(GameController);
    ~GameController();

    bool init();

    void startGame();

    void handleUndoClick();

    GameManager* getGameManager() { return _gameManager; }

    GameView* getGameView() const { return _gameView; }

private:
    GameManager* _gameManager = nullptr;
    GameView* _gameView = nullptr;
    PlayFieldController* _playFieldController = nullptr;
    StackController* _stackController = nullptr;
};