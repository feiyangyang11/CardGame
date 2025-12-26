
#include "GameScene.h"

#include "../configs/loaders/LevelConfigLoader.h"
bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 1. 创建 GameController
    gameController = new GameController();

    // 2. 创建 GameView
    gameView = GameView::create();
    this->addChild(gameView);

    // 3. 关联 Controller 和 View
    gameController->setGameView(gameView);
    gameView->setGameController(gameController);

    // 4. 随机加载关卡并初始化游戏
    srand(time(NULL));
    int id = rand() % 4 + 1;
     LevelConfig config = LevelConfigLoader::loadLevelConfig(3);

    //// 使用默认测试配置
    //LevelConfig config = LevelConfigLoader::createDefaultTestLevel();

    // 转换配置为 GameModel 数据
    std::vector<CardModel> tableCards;
    for (const auto& cardConfig : config.getTableCards()) {
        CardModel card(cardConfig.id,
                static_cast<CardFaceType>(cardConfig.number),
                static_cast<CardSuitType>(cardConfig.suit),
                cardConfig.isVisible);
        tableCards.push_back(card);
    }

    std::vector<CardModel> handCards;
    for (const auto& cardConfig : config.getHandCards()) {
        CardModel card(cardConfig.id,
            static_cast<CardFaceType>(cardConfig.number),
            static_cast<CardSuitType>(cardConfig.suit),
            cardConfig.isVisible);
        handCards.push_back(card);
    }

    const auto& topCardConfig = config.getTopCard();
    CardModel topCard(topCardConfig.id,
            static_cast<CardFaceType>(topCardConfig.number),
            static_cast<CardSuitType>(topCardConfig.suit),
            topCardConfig.isVisible);

    // 初始化游戏
    gameController->initGame(tableCards, handCards, topCard);

    // 刷新视图
    gameView->refreshAllCards();

    return true;
}

GameScene::~GameScene() {
    // 释放 GameController
    if (gameController) {
        delete gameController;
        gameController = nullptr;
    }
}