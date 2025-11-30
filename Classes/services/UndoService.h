#pragma once
#include "../models/GameModel.h"

class UndoService {
public:
    static UndoService* getInstance();

    static void destroyInstance();

    bool undo(GameModel* gameModel);

private:
    UndoService() = default;
    ~UndoService() = default;
    static UndoService* _instance;
};