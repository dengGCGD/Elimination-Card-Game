#include "CardView.h"
#include "cocos2d.h"

CardView::CardView() {}

CardView* CardView::create(CardModel* cardModel, const ClickCallback& callback) {
    CardView* cardView = new CardView();
    if (cardView && cardView->init(cardModel, callback)) {
        cardView->autorelease();
        return cardView;
    }
    delete cardView;
    return nullptr;
}

bool CardView::init(CardModel* cardModel, const ClickCallback& callback) {
    if (!cocos2d::Sprite::init()) {
        return false;
    }

    _cardModel = cardModel;
    _callback = callback;
    if (!_cardModel) {
        return false;
    }

    initCardUI();
    this->setPosition(_cardModel->getPosition());
    registerTouchEvent();

    return true;
}

void CardView::initCardUI() {
    this->removeAllChildren();
    cocos2d::Size cardSize = CardConfig::getCardSize();

    _backSprite = cocos2d::Sprite::create(CardConfig::getCardBackRes());   // 卡牌背景
    if (_backSprite) {
        _backSprite->setContentSize(cardSize);
        _backSprite->setPosition(cardSize.width / 2, cardSize.height / 2);
        this->addChild(_backSprite);
    }

    std::string suitRes = CardConfig::getSuitRes(_cardModel->getSuit());   // 右上角花色
    _suitSprite = cocos2d::Sprite::create(suitRes);
    if (_suitSprite) {
        cocos2d::Vec2 suitPos = cocos2d::Vec2(
            cardSize.width - 10 - _suitSprite->getContentSize().width / 2,
            cardSize.height - 10 - _suitSprite->getContentSize().height / 2
        );
        _suitSprite->setPosition(suitPos);
        this->addChild(_suitSprite);
    }

    std::string smallFaceRes = CardConfig::getFaceRes(_cardModel->getSuit(), _cardModel->getFace(), true); // 左上角点数（小）
    _smallFaceSprite = cocos2d::Sprite::create(smallFaceRes);
    if (_smallFaceSprite) {
        cocos2d::Vec2 smallFacePos = cocos2d::Vec2(
            10 + _smallFaceSprite->getContentSize().width / 2,
            cardSize.height - 10 - _smallFaceSprite->getContentSize().height / 2
        );
        _smallFaceSprite->setPosition(smallFacePos);
        this->addChild(_smallFaceSprite);
    }

    std::string bigFaceRes = CardConfig::getFaceRes(_cardModel->getSuit(), _cardModel->getFace(), false); // 下方点数（大）
    _bigFaceSprite = cocos2d::Sprite::create(bigFaceRes);
    if (_bigFaceSprite) {
        cocos2d::Vec2 bigFacePos = cocos2d::Vec2(
            cardSize.width / 2,
            cardSize.height / 4
        );
        _bigFaceSprite->setPosition(bigFacePos);
        this->addChild(_bigFaceSprite);
    }

    this->setContentSize(cardSize);
}

void CardView::registerTouchEvent() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (this->getBoundingBox().containsPoint(touch->getLocation())) {
            if (_callback && _cardModel) {
                _callback(_cardModel);
            }
            return true;
        }
        return false;
        };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    listener->setSwallowTouches(true);
    CCLOG("registerTouchEvent");
}

void CardView::setCardModel(CardModel* model)
{
    if (!model) return;
    _cardModel = model;
    initCardUI();
    this->setPosition(_cardModel->getPosition());
}