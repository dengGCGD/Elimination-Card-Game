#pragma once
#include "cocos2d.h"
#include "../models/GameModel.h"
#include "PlayFieldView.h"
#include "StackView.h"
#include "ui/CocosGUI.h"

// 游戏的显示
class GameView : public cocos2d::Layer {
public:
    CREATE_FUNC(GameView);
    ~GameView() override = default;

    using UndoCallback = std::function<void()>;

    void registerUndoCallback(const UndoCallback& callback) {
        _undoCallback = callback;
    }

    void initUI(GameModel* gameModel);

    PlayFieldView* getPlayFieldView() { return _playFieldView; }

    StackView* getStackView() { return _stackView; }

private:
    bool init() override;

    PlayFieldView* _playFieldView = nullptr;
    StackView* _stackView = nullptr;
    cocos2d::ui::Button* _undoButton = nullptr;
    UndoCallback _undoCallback;
};