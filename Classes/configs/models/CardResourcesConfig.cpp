#include"CardResourcesConfig.h"
const std::string CardResourcesConfig::resPath = "";
const std::string CardResourcesConfig::CardBackImageName = "card_back.png";
const std::string CardResourcesConfig::CardFrontImageName = "card_general.png";
const std::string CardResourcesConfig::SuitImageName = "suits/";
const std::string CardResourcesConfig::FaceImageName = "numbers/";
const float CardResourcesConfig::cardWidth = 182.0f * 0.8;
const float CardResourcesConfig::cardHeight = 282.0f * 0.8;

cocos2d::Size CardResourcesConfig::getCardSize() {
    return cocos2d::Size(CardResourcesConfig::cardWidth, CardResourcesConfig::cardHeight);
}

std::string CardResourcesConfig::getCardFrontImage() {
    return CardResourcesConfig::resPath + CardResourcesConfig::CardFrontImageName;
}

std::string CardResourcesConfig::getCardBackImage() {
    return CardResourcesConfig::resPath + CardResourcesConfig::CardBackImageName;
}
std::string CardResourcesConfig::getSuitImage(CardSuitType suit) {
    std::string name;
    if (suit == CardSuitType::CST_CLUBS) name = "club";
    if (suit == CardSuitType::CST_SPADES) name = "spade";
    if (suit == CardSuitType::CST_DIAMONDS) name = "diamond";
    if (suit == CardSuitType::CST_HEARTS) name = "heart";
    return CardResourcesConfig::resPath + CardResourcesConfig::SuitImageName + name + ".png";
}
std::string CardResourcesConfig::getFaceImage(CardSuitType suit,CardFaceType number, int flag) {//0是小 1是大
    std::string name = flag == 0? "small_" : "big_";
    if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {
        name += "black_";
    }
    else if (suit == CardSuitType::CST_HEARTS || suit == CardSuitType::CST_DIAMONDS) {
        name += "red_";
    }
    return CardResourcesConfig::resPath + CardResourcesConfig::FaceImageName + name 
        + std::to_string(static_cast<int>(number)) + ".png";
}