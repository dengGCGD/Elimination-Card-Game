#include "GameView.h"
#include "cocos2d.h"

bool GameView::init() {
    if (!cocos2d::Layer::init()) return false;

    _playFieldView = PlayFieldView::create();
    _stackView = StackView::create();

    this->addChild(_playFieldView);
    this->addChild(_stackView);

    return true;
}

//初始化游戏界面（上下背景，回退按钮，卡牌，标题）
void GameView::initUI(GameModel* gameModel) {
    if (!gameModel) return;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    auto topBg = cocos2d::LayerColor::create(cocos2d::Color4B(220, 240, 240, 255));
    topBg->setContentSize(cocos2d::Size(1080, 1500));
    topBg->setPosition(0, 580);
    this->addChild(topBg, -2);

    auto bottomBg = cocos2d::LayerColor::create(cocos2d::Color4B(245, 240, 230, 255));
    bottomBg->setContentSize(cocos2d::Size(1080, 580));
    bottomBg->setPosition(0, 0);
    this->addChild(bottomBg, -2);

    _playFieldView->initPlayFieldCards(gameModel->getPlayfieldCards());
    _stackView->initStackCards(gameModel->getStackCards());

    _undoButton = cocos2d::ui::Button::create();
    if (_undoButton) {
        auto buttonBg = cocos2d::LayerColor::create(cocos2d::Color4B(100, 200, 100, 255));
        buttonBg->setContentSize(cocos2d::Size(60, 30));
        buttonBg->setPosition(0, 0);
        _undoButton->addChild(buttonBg, -1);

        _undoButton->setTitleText("Undo");
        _undoButton->setTitleFontName("fonts/Arial.ttf");
        _undoButton->setTitleFontSize(24);
        _undoButton->setTitleColor(cocos2d::Color3B::WHITE);

        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        _undoButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));

        _undoButton->addClickEventListener([this](cocos2d::Ref* sender) {
            if (_undoCallback) {
                _undoCallback();
            }
            });

        this->addChild(_undoButton, 999);
    }

    auto* title = cocos2d::Label::createWithTTF("Elimination Card Game", "fonts/Marker Felt.ttf", 36);
    title->setPosition(cocos2d::Vec2(
        cocos2d::Director::getInstance()->getWinSize().width / 2,
        cocos2d::Director::getInstance()->getWinSize().height - 50
    ));
    title->setTextColor(cocos2d::Color4B(80, 100, 120, 255));
    this->addChild(title);
}