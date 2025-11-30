#pragma once
#include "Card.h"
#include "cocos2d.h"

class CardConfig {
public:
    static cocos2d::Size getCardSize();

    static std::string getCardBackRes();
    static std::string getCardFrontRes();
    static std::string getSuitRes(CardSuitType suit);
    static std::string getFaceRes(CardSuitType suit, CardFaceType face, bool isSmall);

private:
    static cocos2d::Size s_cardSize;
    static bool s_cardSizeInitialized;
    static void initializeCardSize();
};