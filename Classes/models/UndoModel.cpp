#include "UndoModel.h"

void UndoModel::pushStep(const UndoStep& step) {
    _steps.push_back(step);
}

bool UndoModel::popStep(UndoStep& outStep) {
    if (_steps.empty()) {
        return false;
    }
    outStep = _steps.back();
    _steps.pop_back();
    return true;
}

void UndoModel::clear() {
    _steps.clear();
}