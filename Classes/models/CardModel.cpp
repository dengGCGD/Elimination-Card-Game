#include "CardModel.h"

CardModel::CardModel(int id, CardSuitType suit, CardFaceType face, const cocos2d::Vec2& pos)
    : _id(id), _suit(suit), _face(face), _position(pos), _originalPos(pos) {
}