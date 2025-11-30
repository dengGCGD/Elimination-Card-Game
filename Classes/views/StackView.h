#pragma once
#include "cocos2d.h"
#include "../models/CardModel.h"
#include "../models/GameModel.h"
#include "CardView.h"
#include <map>

// 手牌区的显示
class StackView : public cocos2d::Layer {
public:
    CREATE_FUNC(StackView);
    ~StackView() override = default;

    using CardClickCallback = std::function<bool(int)>;

    void registerCardClickCallback(const CardClickCallback& callback) {
        _cardClickCallback = callback;
    }

    void initStackCards(const std::vector<CardModel*>& cardModels);

    void playReplaceAnimation(int cardId);

    void refreshStackCards(const std::vector<CardModel*>& cardModels);

private:
    bool init() override;

    void onCardClicked(const CardModel* cardModel);

    CardClickCallback _cardClickCallback;
    std::map<int, CardView*> _cardViewMap; 
};