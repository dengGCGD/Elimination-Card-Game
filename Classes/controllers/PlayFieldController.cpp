#include "PlayFieldController.h"
#include "../models/CardModel.h"

bool PlayFieldController::init() {
    return true;
}

bool PlayFieldController::init(GameManager* gameManager) {
    if (!init()) return false;
    _gameManager = gameManager;
    return true;
}

void PlayFieldController::bindView(PlayFieldView* view) {
    _playFieldView = view;
    if (_playFieldView) {
        _playFieldView->registerCardClickCallback(
            CC_CALLBACK_1(PlayFieldController::handleCardClick, this)
        );
    }
}

bool PlayFieldController::handleCardClick(int cardId) {
    CCLOG("PlayFieldController::handleCardClick, id = %d", cardId);
    if (!_gameManager || !_playFieldView) return false;

    if (!checkCardMoveCondition(cardId)) return false;

    CardModel* playCard = _gameManager->getGameModel()->getCardById(cardId);
    bool ret = _gameManager->matchPlayfieldCard(playCard);

    if (ret && _playFieldView) {
        _playFieldView->playMatchAnimation(cardId);
    }

    return ret;
}

bool PlayFieldController::checkCardMoveCondition(int cardId) const {
    if (!_gameManager) return false;
    CardModel* playCard = _gameManager->getGameModel()->getCardById(cardId);
    return _gameManager->getGameModel()->isPlayfieldCardMatch(playCard);
}