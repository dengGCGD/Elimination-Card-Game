#include "CardMatchService.h"
#include "../utils/CardUtils.h"

CardMatchService* CardMatchService::_instance = nullptr;

CardMatchService* CardMatchService::getInstance() {
    if (!_instance) {
        _instance = new CardMatchService();
    }
    return _instance;
}

void CardMatchService::destroyInstance() {
    if (_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

bool CardMatchService::isPlayfieldCardMatch(CardModel* playCard, CardModel* topStackCard) {
    if (!playCard || !topStackCard) {
        return false;
    }
    return CardUtils::isCardsMatch(playCard->getFaceValue(), topStackCard->getFaceValue());
}