#include "PlayFieldView.h"

bool PlayFieldView::init() {
    if (!cocos2d::Layer::init()) return false;
    return true;
}

void PlayFieldView::initPlayFieldCards(const std::vector<CardModel*>& cardModels) {
    for (auto* cardModel : cardModels) {
        auto* cardView = CardView::create(cardModel, [this](const CardModel* card) {
            this->onCardClicked(card);
        });
        if (cardView) {
            this->addChild(cardView);
            _cardViewMap[cardModel->getId()] = cardView;
        }
    }
}

void PlayFieldView::playMatchAnimation(int playCardId) {
    auto* cardView = _cardViewMap[playCardId];
    if (!cardView) return;

    auto* cardModel = cardView->getCardModel();
    cardView->setLocalZOrder(1000);
    cardView->runAction(cocos2d::Sequence::create(
        cocos2d::MoveTo::create(0.3f, cocos2d::Vec2(200, 300)),
        cocos2d::CallFunc::create([cardView]() {
            cardView->setLocalZOrder(999);
            }),
        nullptr
    ));
}

void PlayFieldView::onCardClicked(const CardModel* cardModel) {
    CCLOG("PlayFieldView::onCardClicked, id = %d", cardModel->getId());
    if (_cardClickCallback && cardModel) {
        _cardClickCallback(cardModel->getId());
    }
}

void PlayFieldView::refreshPlayFieldCards(const std::vector<CardModel*>& cardModels) {
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

    for (auto* card : cardModels) {
        auto it = _cardViewMap.find(card->getId());
        if (it == _cardViewMap.end()) {
            auto* cardView = CardView::create(card, [this](const CardModel* card) {
                this->onCardClicked(card);
                });
            this->addChild(cardView);
            _cardViewMap[card->getId()] = cardView;
        }
        else {
            auto* cardView = it->second;
            cardView->setCardModel(card);
            cardView->setPosition(card->getPosition());
        }
    }
}