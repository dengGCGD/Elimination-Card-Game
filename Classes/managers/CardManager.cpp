#include "CardManager.h"
#include "cocos2d.h"

CardView* CardManager::createCardView(CardModel* cardModel, const CardView::ClickCallback& clickCallback) {
    if (!cardModel) {
        return nullptr;
    }

    CardView* cardView = CardView::create(cardModel, clickCallback);
    if (cardView) {
        _cardViewMap[cardModel->getId()] = cardView;
    }

    return cardView;
}

CardView* CardManager::getCardViewById(int cardId) {
    auto it = _cardViewMap.find(cardId);
    return (it != _cardViewMap.end()) ? it->second : nullptr;
}

void CardManager::updateCardPosition(CardModel* cardModel, float duration) {
    if (!cardModel) {
        return;
    }

    CardView* cardView = getCardViewById(cardModel->getId());
    if (cardView) {
        cardView->runAction(cocos2d::MoveTo::create(duration, cardModel->getPosition()));
    }
}

void CardManager::releaseAllCardViews() {
    for (auto& pair : _cardViewMap) {
        pair.second->removeFromParent();
        pair.second = nullptr;
    }
    _cardViewMap.clear();
}