#pragma once
#include "cocos2d.h"
#include "../models/CardModel.h"
#include "../configs/models/CardResConfig.h"

// 卡牌的显示
class CardView : public cocos2d::Sprite {
public:
    using ClickCallback = std::function<void(const CardModel*)>;

    static CardView* create(CardModel* cardModel, const ClickCallback& callback);
    ~CardView() override = default;

    CardModel* getCardModel() { return _cardModel; }

    void setCardModel(CardModel* model);

    void initCardUI();

private:
    CardView();
    bool init(CardModel* cardModel, const ClickCallback& callback);

    void registerTouchEvent();

    CardModel* _cardModel = nullptr;
    ClickCallback _callback;
    cocos2d::Sprite* _backSprite = nullptr;
    cocos2d::Sprite* _suitSprite = nullptr;
    cocos2d::Sprite* _smallFaceSprite = nullptr;
    cocos2d::Sprite* _bigFaceSprite = nullptr;
};