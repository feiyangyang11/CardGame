#ifndef LEVEL_CARD_CONFIG_
#define LEVEL_CARD_CONFIG_H

#include <string>
#include "cocos2d.h"
#include"../enums/CardDefine.h"


class LevelCardConfig {
private:
                          
public:
    CardSuitType suit;
    CardFaceType number;
    cocos2d::Vec2 position;
    bool isVisible;
    int id;

    LevelCardConfig():
        suit(CardSuitType::CST_NONE), number(CardFaceType::CFT_NONE) ,
        position(cocos2d::Vec2::ZERO), isVisible(true), id(0) {}

    LevelCardConfig(CardSuitType s, CardFaceType n, cocos2d::Vec2& pos, bool vis, int cardId)
        : suit(s), number(n), position(pos), isVisible(vis), id(cardId) {}
};

#endif // __LEVEL_CARD_CONFIG_H__
