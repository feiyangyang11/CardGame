#include "LevelConfigLoader.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

std::string LevelConfigLoader::getLevelConfigPath(int levelId) {
    return StringUtils::format("level_%02d.json", levelId);
}

LevelConfig LevelConfigLoader::loadLevelConfig(int levelId) {
    std::string filePath = getLevelConfigPath(levelId);//json文件路径
    std::string content = FileUtils::getInstance()->getStringFromFile(filePath);//获取json内容

    if (content.empty()) {
        CCLOG("Failed to load level config: %s\n", filePath.c_str());//文件打不开
        return LevelConfig();//空关卡
    }

    return loadFromJsonString(content);//调用下面那个函数↓
}

LevelConfig LevelConfigLoader::loadFromJsonString(const std::string& jsonStr) {
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    if (doc.HasParseError()) {
        CCLOG("JSON parse error\n");
        return LevelConfig();
    }

    LevelConfig config;

    // 解析 levelId
    if (doc.HasMember("levelId") && doc["levelId"].IsInt()) {
        config.setLevelId(doc["levelId"].GetInt());
    }

    // 解析桌面牌区
    if (doc.HasMember("tableCards") && doc["tableCards"].IsArray()) {
        const auto& tableArray = doc["tableCards"];
        for (rapidjson::SizeType i = 0; i < tableArray.Size(); i++) {
            const auto& cardObj = tableArray[i];

            LevelCardConfig cardConfig;
            if (cardObj.HasMember("suit") && cardObj["suit"].IsInt()) {
                cardConfig.suit = static_cast<CardSuitType>(cardObj["suit"].GetInt());
                CCLOG("HAS SUIT\n");
            }
            if (!cardObj.HasMember("number")) {
                CCLOG("NO MEM---NUMBER\n");
            }
            else {
                if (!cardObj["number"].IsInt()) {
                    CCLOG("NOT INT\n");
                }
            }
            
            if (cardObj.HasMember("number") && cardObj["number"].IsInt()) {
                cardConfig.number = static_cast<CardFaceType>(cardObj["number"].GetInt());
                CCLOG("HAS NUMBER\n");
            }
            else {
                CCLOG("NO NUMBER\n");
            }
            if (cardObj.HasMember("x") && cardObj["x"].IsNumber()) {
                cardConfig.position.x = cardObj["x"].GetFloat();
                CCLOG("HAS X\n");
            }
            if (cardObj.HasMember("y") && cardObj["y"].IsNumber()) {
                cardConfig.position.y = cardObj["y"].GetFloat();
            }
            if (cardObj.HasMember("isVisible") && cardObj["isVisible"].IsBool()) {
                cardConfig.isVisible = cardObj["isVisible"].GetBool();
                CCLOG("HAS VIS\n");
            }
            if (cardObj.HasMember("id") && cardObj["id"].IsInt()) {
                cardConfig.id = cardObj["id"].GetInt();
            }

            config.addTableCard(cardConfig);
        }
    }

    // 解析手牌区
    if (doc.HasMember("handCards") && doc["handCards"].IsArray()) {
        const auto& handArray = doc["handCards"];
        for (rapidjson::SizeType i = 0; i < handArray.Size(); i++) {
            const auto& cardObj = handArray[i];

            LevelCardConfig cardConfig;
            if (cardObj.HasMember("suit") && cardObj["suit"].IsInt()) {
                cardConfig.suit = static_cast<CardSuitType>(cardObj["suit"].GetInt());
            }
            if (cardObj.HasMember("number") && cardObj["number"].IsInt()) {
                cardConfig.number = static_cast<CardFaceType>(cardObj["number"].GetInt());
            }
            if (cardObj.HasMember("x") && cardObj["x"].IsNumber()) {
                cardConfig.position.x = cardObj["x"].GetFloat();
            }
            if (cardObj.HasMember("y") && cardObj["y"].IsNumber()) {
                cardConfig.position.y = cardObj["y"].GetFloat();
            }
            if (cardObj.HasMember("isVisible") && cardObj["isVisible"].IsBool()) {
                cardConfig.isVisible = cardObj["isVisible"].GetBool();
            }
            if (cardObj.HasMember("id") && cardObj["id"].IsInt()) {
                cardConfig.id = cardObj["id"].GetInt();
            }

            config.addHandCard(cardConfig);
        }
    }

    // 解析顶部牌
    if (doc.HasMember("topCard") && doc["topCard"].IsObject()) {
        const auto& cardObj = doc["topCard"];

        LevelCardConfig cardConfig;
        if (cardObj.HasMember("suit") && cardObj["suit"].IsInt()) {
            cardConfig.suit = static_cast<CardSuitType>(cardObj["suit"].GetInt());
        }
        if (cardObj.HasMember("number") && cardObj["number"].IsInt()) {
            cardConfig.number = static_cast<CardFaceType>(cardObj["number"].GetInt());
        }
        if (cardObj.HasMember("x") && cardObj["x"].IsNumber()) {
            cardConfig.position.x = cardObj["x"].GetFloat();
        }
        if (cardObj.HasMember("y") && cardObj["y"].IsNumber()) {
            cardConfig.position.y = cardObj["y"].GetFloat();
        }
        if (cardObj.HasMember("isVisible") && cardObj["isVisible"].IsBool()) {
            cardConfig.isVisible = cardObj["isVisible"].GetBool();
        }
        if (cardObj.HasMember("id") && cardObj["id"].IsInt()) {
            cardConfig.id = cardObj["id"].GetInt();
        }

        config.setTopCard(cardConfig);
    }

    return config;
}

LevelConfig LevelConfigLoader::createDefaultTestLevel() {
    LevelConfig config(1);

    // 桌面牌区：6张牌
    config.addTableCard(LevelCardConfig(CardSuitType::CST_CLUBS, CardFaceType::CFT_THREE, Vec2(200, 600), true, 1));   // ♦3
    config.addTableCard(LevelCardConfig(CardSuitType::CST_SPADES, CardFaceType::CFT_TWO, Vec2(400, 600), true, 2));   // ♠2
    config.addTableCard(LevelCardConfig(CardSuitType::CST_CLUBS, CardFaceType::CFT_SEVEN, Vec2(600, 600), true, 3));   // ♣7
    config.addTableCard(LevelCardConfig(CardSuitType::CST_HEARTS, CardFaceType::CFT_FIVE, Vec2(800, 600), true, 4));   // ♥5
    config.addTableCard(LevelCardConfig(CardSuitType::CST_DIAMONDS, CardFaceType::CFT_KING, Vec2(200, 400), true, 5));   // ♦K
    config.addTableCard(LevelCardConfig(CardSuitType::CST_SPADES, CardFaceType::CFT_SIX, Vec2(400, 400), true, 6));   // ♠6

    // 手牌区：3张牌
    config.addHandCard(LevelCardConfig(CardSuitType::CST_HEARTS, CardFaceType::CFT_ACE, Vec2(400, 200), true, 7));    // ♥A
    config.addHandCard(LevelCardConfig(CardSuitType::CST_SPADES, CardFaceType::CFT_EIGHT, Vec2(500, 200), true, 8));    // ♠8
    config.addHandCard(LevelCardConfig(CardSuitType::CST_DIAMONDS, CardFaceType::CFT_QUEEN, Vec2(600, 200), true, 9));    // ♦Q

    // 顶部牌
    config.setTopCard(LevelCardConfig(CardSuitType::CST_CLUBS, CardFaceType::CFT_FOUR, Vec2(540, 1000), true, 10));   // ♣4

    return config;
}

