#include "CardResConfig.h"

cocos2d::Size CardConfig::s_cardSize = cocos2d::Size::ZERO;
bool CardConfig::s_cardSizeInitialized = false;

void CardConfig::initializeCardSize() {
    if (!s_cardSizeInitialized) {
        // 创建Sprite来读取图片尺寸
        auto sp = cocos2d::Sprite::create("card_general.png");
        if (sp) {
            s_cardSize = sp->getContentSize();
        }
        else {
            s_cardSize = cocos2d::Size(120, 160);
        }
        s_cardSizeInitialized = true;
    }
}

cocos2d::Size CardConfig::getCardSize() {
    if (!s_cardSizeInitialized) {
        initializeCardSize();
    }
    return s_cardSize;
}

std::string CardConfig::getCardBackRes() {
    return "card_general.png";
}

std::string CardConfig::getSuitRes(CardSuitType suit) {
    return cocos2d::StringUtils::format("suits/%s.png", CardConst::getSuitName(suit));
}

std::string CardConfig::getFaceRes(CardSuitType suit, CardFaceType face, bool isSmall) {
    // 红色（方块、红桃）用 red，黑色（梅花、黑桃）用 black
    bool isRed = (suit == CST_DIAMONDS || suit == CST_HEARTS);
    std::string colorPrefix = isRed ? "red" : "black";
    std::string sizePrefix = isSmall ? "small_" : "big_";
    return cocos2d::StringUtils::format("number/%s%s_%s.png", sizePrefix.c_str(), colorPrefix.c_str(), CardConst::getFaceName(face));
}