#include "GameController.h"

GameController::~GameController() {
    if (_playFieldController) {
        _playFieldController->release();
        _playFieldController = nullptr;
    }
    if (_stackController) {
        _stackController->release();
        _stackController = nullptr;
    }
    if (_gameManager) {
        delete _gameManager;
        _gameManager = nullptr;
    }
}

bool GameController::init() {
    // 初始化管理器和子控制器
    _gameManager = new GameManager();
    _playFieldController = PlayFieldController::create();
    _playFieldController->retain();
    _stackController = StackController::create();
    _stackController->retain();

    _playFieldController->init(_gameManager);
    _stackController->init(_gameManager);

    return true;
}

void GameController::startGame() {
    // 初始化游戏数据
    _gameManager->initGame();

    // 创建游戏视图
    _gameView = GameView::create();
    auto* director = cocos2d::Director::getInstance();
    auto* scene = director->getRunningScene();
    if (scene) {
        scene->addChild(_gameView);
    }

    // 绑定子控制器视图
    _playFieldController->bindView(_gameView->getPlayFieldView());
    _stackController->bindView(_gameView->getStackView());

    // 初始化视图UI
    _gameView->initUI(_gameManager->getGameModel());

    // 注册回退按钮的回调
    _gameView->registerUndoCallback(CC_CALLBACK_0(GameController::handleUndoClick, this));
    _gameManager->setViews(_gameView->getStackView(), _gameView->getPlayFieldView());
}

void GameController::handleUndoClick() {
    if (_gameManager) {
        _gameManager->undo();
    }
}