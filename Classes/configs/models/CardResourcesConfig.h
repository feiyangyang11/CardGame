#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include <string>
#include "cocos2d.h"
#include"../enums/CardDefine.h"

class CardResourcesConfig {
public:
  
    CardResourcesConfig(){}

    static std::string getCardFrontImage();

    static std::string getCardBackImage();

    static cocos2d::Size getCardSize();

    static std::string getSuitImage(CardSuitType suit);

    static std::string getFaceImage(CardSuitType suit,CardFaceType number, int flag);

//private:
    // 资源路径常量
    static const std::string resPath;
    static const std::string CardBackImageName;
    static const std::string CardFrontImageName;
    static const std::string SuitImageName;
    static const std::string FaceImageName;
    static const float cardWidth;
    static const float cardHeight;
};

#endif // __CARD_RES_CONFIG_H__
