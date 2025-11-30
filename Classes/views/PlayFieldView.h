#pragma once
#include "cocos2d.h"
#include "../models/CardModel.h"
#include "CardView.h"
#include <map>

// 主牌区的显示
class PlayFieldView : public cocos2d::Layer {
public:
    CREATE_FUNC(PlayFieldView);
    ~PlayFieldView() override = default;

    using CardClickCallback = std::function<bool(int)>;

    void registerCardClickCallback(const CardClickCallback& callback) {
        _cardClickCallback = callback;
    }

    void initPlayFieldCards(const std::vector<CardModel*>& cardModels);

    void playMatchAnimation(int playCardId);

    void refreshPlayFieldCards(const std::vector<CardModel*>& cardModels);

private:
    bool init() override;

    void onCardClicked(const CardModel* cardModel);

    CardClickCallback _cardClickCallback; 
    std::map<int, CardView*> _cardViewMap; 
};