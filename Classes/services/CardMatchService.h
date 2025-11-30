#pragma once
#include "../models/CardModel.h"

class CardMatchService {
public:
    static CardMatchService* getInstance();

    static void destroyInstance();

    bool isPlayfieldCardMatch(CardModel* playCard, CardModel* topStackCard);

private:
    CardMatchService() = default;
    ~CardMatchService() = default;
    static CardMatchService* _instance;
};