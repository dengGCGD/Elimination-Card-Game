#include "CardUtils.h"
#include "cocos2d.h"

cocos2d::Vec2 CardUtils::adaptPosition(const cocos2d::Vec2& rawPos) {
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    float scaleX = winSize.width / 1080.0f;
    float scaleY = winSize.height / 2080.0f;
    return cocos2d::Vec2(rawPos.x * scaleX, rawPos.y * scaleY);
}