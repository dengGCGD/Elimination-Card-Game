#include "GameModel.h"
#include "cocos2d.h"
#include <cmath>
#include <algorithm>

GameModel::~GameModel() {
    releaseCards();
}

void GameModel::initHardCode() {
    releaseCards();

    int cardId = 0;
    _playfieldCards.push_back(new CardModel(cardId++, CST_SPADES, CFT_QUEEN, cocos2d::Vec2(220, 1300)));
    _playfieldCards.push_back(new CardModel(cardId++, CST_CLUBS, CFT_THREE, cocos2d::Vec2(270, 1100)));
    _playfieldCards.push_back(new CardModel(cardId++, CST_DIAMONDS, CFT_TWO, cocos2d::Vec2(320, 900)));
    _playfieldCards.push_back(new CardModel(cardId++, CST_CLUBS, CFT_SEVEN, cocos2d::Vec2(860, 1300)));
    _playfieldCards.push_back(new CardModel(cardId++, CST_HEARTS, CFT_TWO, cocos2d::Vec2(810, 1100)));
    _playfieldCards.push_back(new CardModel(cardId++, CST_SPADES, CFT_ACE, cocos2d::Vec2(760, 900)));

    _stackCards.push_back(new CardModel(cardId++, CST_CLUBS, CFT_KING, cocos2d::Vec2(620, 300)));
    _stackCards.push_back(new CardModel(cardId++, CST_HEARTS, CFT_ACE, cocos2d::Vec2(580, 300)));
    _stackCards.push_back(new CardModel(cardId++, CST_CLUBS, CFT_THREE, cocos2d::Vec2(540, 300)));

    for (auto* card : _playfieldCards) {
        _allCards[card->getId()] = card;
    }
    for (auto* card : _stackCards) {
        _allCards[card->getId()] = card;
    }
}

bool GameModel::replaceTopStackCard(CardModel* newCard) {
    if (!newCard || _stackCards.empty()) {
        return false;
    }

    auto playfieldIt = std::find(_playfieldCards.begin(), _playfieldCards.end(), newCard);
    if (playfieldIt != _playfieldCards.end()) {
        _playfieldCards.erase(playfieldIt);
    }

    CardModel* oldTopCard = _stackCards.back();
    cocos2d::Vec2 oldTopPos = oldTopCard->getPosition();

    newCard->setPosition(oldTopPos);
    oldTopCard->setPosition(newCard->getOriginalPos());

    _stackCards.pop_back();
    _stackCards.push_back(newCard);

    auto it = std::find(_playfieldCards.begin(), _playfieldCards.end(), newCard);
    if (it != _playfieldCards.end()) {
        _playfieldCards.erase(it);
    }

    _allCards[newCard->getId()] = newCard;

    return true;
}

CardModel* GameModel::getPlayfieldCardById(int id) {
    for (auto* card : _playfieldCards) {
        if (card->getId() == id) {
            return card;
        }
    }
    return nullptr;
}

bool GameModel::isPlayfieldCardMatch(CardModel* playCard) const {
    if (!playCard || _stackCards.empty()) {
        return false;
    }
    int topVal = _stackCards.back()->getFaceValue();
    int playVal = playCard->getFaceValue();
    // ★ 推荐用 std::abs
    return std::abs(topVal - playVal) == 1;
}

bool GameModel::undoStep(const UndoStep& step) {
    if (step.type == UndoStep::UT_STACK_REPLACE) {
        CardModel* newCard = getCardById(step.cardId);
        if (!newCard) return false;

        newCard->setPosition(step.oldPos);
        _playfieldCards.push_back(newCard);

        CardModel* oldTopCard = getCardById(step.oldTopCardId);
        if (oldTopCard) {
            oldTopCard->setPosition(step.oldTopPos);
            if (!_stackCards.empty()) _stackCards.pop_back();
            _stackCards.push_back(oldTopCard);
        }

        auto stackIt = std::find(_stackCards.begin(), _stackCards.end(), newCard);
        if (stackIt != _stackCards.end()) {
            _stackCards.erase(stackIt);
        }
    }
    else if (step.type == UndoStep::UT_MATCH_PLAYFIELD) {
        CardModel* matchedCard = getCardById(step.cardId);
        if (!matchedCard) return false;

        matchedCard->setPosition(step.oldPos);
        _playfieldCards.push_back(matchedCard);

        if (step.oldTopCardId != -1) {
            CardModel* oldTopCard = getCardById(step.oldTopCardId);
            if (oldTopCard) {
                oldTopCard->setPosition(step.oldTopPos);
                if (!_stackCards.empty()) _stackCards.pop_back();
                _stackCards.push_back(oldTopCard);
            }
        }

        auto stackIt = std::find(_stackCards.begin(), _stackCards.end(), matchedCard);
        if (stackIt != _stackCards.end()) {
            _stackCards.erase(stackIt);
        }
    }

    return true;
}

CardModel* GameModel::getCardById(int id) {
    auto it = _allCards.find(id);
    return (it != _allCards.end()) ? it->second : nullptr;
}

void GameModel::releaseCards() {
    for (auto& pair : _allCards) {
        delete pair.second;
    }
    _allCards.clear();
    _playfieldCards.clear();
    _stackCards.clear();
    _undoModel.clear();
}