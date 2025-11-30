#pragma once
#include "../configs/models/Card.h"
#include "cocos2d.h"

// 卡牌模板
class CardModel {
public:
    CardModel(int id, CardSuitType suit, CardFaceType face, const cocos2d::Vec2& pos);
    ~CardModel() = default;

    cocos2d::Vec2 getPosition() const { return _position; }
    void setPosition(const cocos2d::Vec2& pos) { _position = pos; }

    cocos2d::Vec2 getOriginalPos() const { return _originalPos; }

    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }

    int getFaceValue() const { return CardConst::getFaceValue(_face); }

    bool isOpen() const { return _isOpen; }
    void setOpen(bool open) { _isOpen = open; }

    int getId() const { return _id; }

private:
    int _id;
    CardSuitType _suit;
    CardFaceType _face;
    cocos2d::Vec2 _position;
    cocos2d::Vec2 _originalPos;
    bool _isOpen = true;
};