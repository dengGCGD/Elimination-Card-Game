#pragma once
#include "../models/GameModel.h"
#include "../managers/CardManager.h"
#include "../services/CardMatchService.h"
#include "../services/UndoService.h"
#include "../views/StackView.h"
#include "../views/PlayFieldView.h"

// 游戏管理器
class GameManager {
public:
    GameManager();
    ~GameManager();

    void initGame();

    bool replaceStackTopCard(CardModel* newCard);

    bool matchPlayfieldCard(CardModel* playCard);

    bool undo();

    GameModel* getGameModel() { return _gameModel; }

    CardManager* getCardManager() { return _cardManager; }

    void setViews(StackView* stackView, PlayFieldView* playFieldView) {
        _stackView = stackView;
        _playFieldView = playFieldView;
    }

private:
    GameModel* _gameModel = nullptr;
    CardManager* _cardManager = nullptr;
    CardMatchService* _matchService = nullptr;
    UndoService* _undoService = nullptr;
    StackView* _stackView = nullptr;
    PlayFieldView* _playFieldView = nullptr;
};