#include "UndoService.h"

UndoService* UndoService::_instance = nullptr;

UndoService* UndoService::getInstance() {
    if (!_instance) {
        _instance = new UndoService();
    }
    return _instance;
}

void UndoService::destroyInstance() {
    if (_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

bool UndoService::undo(GameModel* gameModel) {
    if (!gameModel || !gameModel->getUndoModel().hasUndo()) {
        return false;
    }

    UndoStep step;
    if (gameModel->getUndoModel().popStep(step)) {
        return gameModel->undoStep(step);
    }

    return false;
}