#include "GameManager.h"

GameManager::GameManager() {
    _gameModel = new GameModel();
    _cardManager = new CardManager();
    _matchService = CardMatchService::getInstance();
    _undoService = UndoService::getInstance();
}

GameManager::~GameManager() {
    delete _gameModel;
    delete _cardManager;
}

void GameManager::initGame() {
    _gameModel->initHardCode();
}

bool GameManager::replaceStackTopCard(CardModel* newCard) {
    if (!newCard || !_gameModel->getTopStackCard()) {
        return false;
    }

    UndoStep step;
    step.type = UndoStep::UT_STACK_REPLACE;
    step.cardId = newCard->getId();
    step.oldPos = newCard->getPosition();
    step.oldTopCardId = _gameModel->getTopStackCard()->getId();
    step.oldTopPos = _gameModel->getTopStackCard()->getPosition();

    _gameModel->getUndoModel().pushStep(step);

    bool ret = _gameModel->replaceTopStackCard(newCard);

    if (ret) {
        _cardManager->updateCardPosition(newCard);
        _cardManager->updateCardPosition(_gameModel->getCardById(step.oldTopCardId));
    }

    return ret;
}

bool GameManager::matchPlayfieldCard(CardModel* playCard) {
    if (!playCard || !_matchService->isPlayfieldCardMatch(playCard, _gameModel->getTopStackCard())) {
        return false;
    }

    UndoStep step;
    step.type = UndoStep::UT_MATCH_PLAYFIELD;
    step.cardId = playCard->getId();
    step.oldPos = playCard->getPosition();
    step.oldTopCardId = _gameModel->getTopStackCard()->getId();
    step.oldTopPos = _gameModel->getTopStackCard()->getPosition();

    _gameModel->getUndoModel().pushStep(step);

    return _gameModel->replaceTopStackCard(playCard);
}

bool GameManager::undo() {
    bool ret = _undoService->undo(_gameModel);
    if (ret) {
        if (_stackView) {
            _stackView->removeAllChildren();
            _stackView->initStackCards(_gameModel->getStackCards());
        }
        if (_playFieldView) {
            _playFieldView->removeAllChildren();
            _playFieldView->initPlayFieldCards(_gameModel->getPlayfieldCards());
        }

        for (auto* card : _gameModel->getPlayfieldCards()) {
            _cardManager->updateCardPosition(card, 0.2f);
        }
        for (auto* card : _gameModel->getStackCards()) {
            _cardManager->updateCardPosition(card, 0.2f);
        }
    }
    return ret;
}