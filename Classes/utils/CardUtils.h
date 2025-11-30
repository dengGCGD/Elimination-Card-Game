#pragma once
#include "cocos2d.h"
#include "../configs/models/Card.h"
#include <cmath>

namespace CardUtils {
    inline bool isCardsMatch(int val1, int val2) {
        return std::abs(val1 - val2) == 1;
    }

    cocos2d::Vec2 adaptPosition(const cocos2d::Vec2& rawPos);
}