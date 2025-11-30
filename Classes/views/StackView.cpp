#include "StackView.h"
#include "cocos2d.h"

bool StackView::init() {
    if (!cocos2d::Layer::init()) return false;
    return true;
}

void StackView::initStackCards(const std::vector<CardModel*>& cardModels) {
    for (size_t i = 0; i < cardModels.size(); ++i) {
        auto* cardModel = cardModels[i];
        auto* cardView = CardView::create(cardModel, [this](const CardModel* card) {
            this->onCardClicked(card);
            });
        if (cardView) {
            this->addChild(cardView);
            _cardViewMap[cardModel->getId()] = cardView;
            cardView->setPosition(cardModel->getPosition());
            cardView->setLocalZOrder(i);
        }
    }
}

void StackView::playReplaceAnimation(int cardId) {
    auto* cardView = _cardViewMap[cardId];
    if (!cardView) return;

    cardView->setLocalZOrder(1000);
    cardView->runAction(cocos2d::Sequence::create(
        cocos2d::MoveTo::create(0.3f, cocos2d::Vec2(540, 300)),
        cocos2d::CallFunc::create([cardView]() {
            cardView->setLocalZOrder(999);
            }),
        nullptr
    ));
}

void StackView::onCardClicked(const CardModel* cardModel) {
    if (_cardClickCallback && cardModel) {
        _cardClickCallback(cardModel->getId());
    }
}

void StackView::refreshStackCards(const std::vector<CardModel*>& cardModels) {
    std::set<int> currentCardIds;
    for (auto* card : cardModels) {
        currentCardIds.insert(card->getId());
    }

    for (auto it = _cardViewMap.begin(); it != _cardViewMap.end(); ) {
        if (!currentCardIds.count(it->first)) {
            it->second->removeFromParent();
            it = _cardViewMap.erase(it);
        }
        else {
            ++it;
        }
    }

    for (size_t i = 0; i < cardModels.size(); ++i) {
        auto* card = cardModels[i];
        auto it = _cardViewMap.find(card->getId());
        CardView* cardView = nullptr;

        if (it == _cardViewMap.end()) {
            cardView = CardView::create(card, [this](const CardModel* card) {
                this->onCardClicked(card);
                });
            this->addChild(cardView);
            _cardViewMap[card->getId()] = cardView;
        }
        else {
            cardView = it->second;
            cardView->setCardModel(card);
        }

        cardView->setPosition(card->getPosition());
        cardView->setLocalZOrder(i);
        cardView->setVisible(true);
    }
}