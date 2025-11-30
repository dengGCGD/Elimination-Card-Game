#pragma once
#include "../models/CardModel.h"
#include "../views/CardView.h"
#include <map>

// 卡牌管理器
class CardManager {
public:
    CardManager() = default;
    ~CardManager() = default;

    CardView* createCardView(CardModel* cardModel, const CardView::ClickCallback& clickCallback);

    CardView* getCardViewById(int cardId);

    void updateCardPosition(CardModel* cardModel, float duration = 0.3f);

    void releaseAllCardViews();

private:
    std::map<int, CardView*> _cardViewMap;
};