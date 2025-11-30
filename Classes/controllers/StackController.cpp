#include "StackController.h"
#include "../models/CardModel.h"

bool StackController::init() {
    return true;
}

bool StackController::init(GameManager* gameManager) {
    if (!init()) return false;
    _gameManager = gameManager;
    return true;
}

void StackController::bindView(StackView* view) {
    _stackView = view;
    if (_stackView) {
        _stackView->registerCardClickCallback(
            CC_CALLBACK_1(StackController::handleCardClick, this)
        );
    }
}

bool StackController::handleCardClick(int cardId) {
    if (!_gameManager || !_stackView) return false;

    CardModel* card = _gameManager->getGameModel()->getCardById(cardId);
    bool ret = _gameManager->replaceStackTopCard(card);

    if (ret && _stackView) {
        _stackView->playReplaceAnimation(cardId);

        auto delay = cocos2d::DelayTime::create(0.3f);
        auto refresh = cocos2d::CallFunc::create([this]() {
            auto latestStackCards = _gameManager->getGameModel()->getStackCards();
            _stackView->refreshStackCards(latestStackCards);
            });
        _stackView->runAction(cocos2d::Sequence::create(delay, refresh, nullptr));
    }

    return ret;
}