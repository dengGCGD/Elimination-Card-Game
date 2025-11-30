#pragma once
#include "CardModel.h"
#include "UndoModel.h"
#include <vector>
#include <map>

// 游戏模型
class GameModel {
public:
    GameModel() = default;
    ~GameModel();

    void initHardCode();

    std::vector<CardModel*> getPlayfieldCards() const { return _playfieldCards; }
    CardModel* getPlayfieldCardById(int id);

    std::vector<CardModel*> getStackCards() const { return _stackCards; }
    CardModel* getTopStackCard() const { return _stackCards.empty() ? nullptr : _stackCards.back(); }

    bool replaceTopStackCard(CardModel* newCard);

    bool isPlayfieldCardMatch(CardModel* playCard) const;

    UndoModel& getUndoModel() { return _undoModel; }

    bool undoStep(const UndoStep& step);

    CardModel* getCardById(int id);

private:
    void releaseCards();

    std::vector<CardModel*> _playfieldCards;
    std::vector<CardModel*> _stackCards;
    std::map<int, CardModel*> _allCards;
    UndoModel _undoModel;
};