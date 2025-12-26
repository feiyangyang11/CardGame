#include "GameView.h"
#include "GameView.h"
USING_NS_CC;


bool GameView::init() {
    if (!Layer::init()) {
        return false;
    }

    gameController = nullptr;

    initUI();
    return true;
}


void GameView::initUI() {
    // 背景：TABLE(棕) + HAND(紫)
    createBackground();

    // 各区域容器（注意 z-order）
    tableCardsLayer = Node::create();
    this->addChild(tableCardsLayer, 1);

    handCardsLayer = Node::create();
    this->addChild(handCardsLayer, 1);

    topCardLayer = Node::create();
    this->addChild(topCardLayer, 2);

    // Undo 按钮
    createUndoButton();
}

void GameView::createBackground() {
    // 整体底色（灰）
    auto bg = LayerColor::create(Color4B(120, 120, 120, 255));
    this->addChild(bg, 0);

    // TABLE 区（棕色，上）
    auto tableArea = LayerColor::create(
        Color4B(171, 123, 66, 255),
        SCREEN_W,
        TABLE_H
    );
    tableArea->setPosition(Vec2(0.0f, TABLE_START_Y));
    this->addChild(tableArea, 0);

    // HAND 区（紫色，下）
    auto handArea = LayerColor::create(
        Color4B(136, 36, 146, 255),
        SCREEN_W,
        HAND_H
    );
    handArea->setPosition(Vec2(0.0f, HAND_START_Y));
    this->addChild(handArea, 0);

    // 标题（放在 TABLE 顶部附近）
    auto titleLabel = Label::createWithSystemFont(
        "Card Match Game",
        "Arial",
        56
    );
    titleLabel->setPosition(Vec2(SCREEN_W / 2.0f, SCREEN_H - 30.0f));
    titleLabel->setColor(Color3B::BLACK);
    this->addChild(titleLabel, 1);
}

void GameView::createUndoButton() {
    undoButton = ui::Button::create("undo_normal.png","undo_selected.png");

    if (!undoButton) {
        undoButton = ui::Button::create();
        undoButton->setTitleText("Undo");
        undoButton->setTitleFontSize(40);
        undoButton->setScale9Enabled(true);
        undoButton->setContentSize(Size(200, 100));
        undoButton->setTitleColor(Color3B::BLACK);
    }
    //
    undoButton->setContentSize(Size(undoSizeX, undoSizeY));  
    undoButton->setScale(2.0f);  
    // 
    // ✅ 使用统一的 UI 常量
    undoButton->setPosition(Vec2(undoButtonX, undoButtonY));

    undoButton->addClickEventListener([this](Ref*) {
        onUndoButtonClick();
        });

    this->addChild(undoButton, 3);
    Label* label = Label::create("Undo", "Arial", 50);
    label->setPosition(Vec2(undoButtonX, undoButtonY * 1.3f));
    label->setColor(Color3B::BLACK);
    this->addChild(label, 3);
    updateUndoButton(false);
}


void GameView::refreshAllCards() {
    if (!gameController) return;

    GameModel* gameModel = gameController->getGameModel();
    if (!gameModel) return;

    // 清理旧视图
    cardViewMap.clear();
    tableCardsLayer->removeAllChildren();
    handCardsLayer->removeAllChildren();
    topCardLayer->removeAllChildren();

    
    // TABLE：左右两堆，向下叠放 
    const auto& tableCards = gameModel->getTableCards();

    for (int index = 0; index < static_cast<int>(tableCards.size()); ++index) {
        const auto& card = tableCards[index];
        CardView* cardView = CardView::create(card);
        cardView->showFront(card);
        // 偶数 -> 左堆，奇数 -> 右堆
        bool isLeftPile = (index % 2 == 0);
        int depth = index / 2;

        float x = isLeftPile ? tablePileLeftX : tablePileRightX;
        float y = tablePileStartY + depth * tablePileSpacingY;

        cardView->setPosition(Vec2(x, y));

        cardView->setOnCardClickCallback([this](int cardId) {
            onTableCardClick(cardId);
            });

        tableCardsLayer->addChild(cardView);
        cardViewMap[card.getId()] = cardView;
    }


    //  HAND：左下，向右横向排列
    const auto& handCards = gameModel->getHandCards();

    for (size_t i = 0; i < handCards.size(); ++i) {
        const auto& card = handCards[i];
        CardView* cardView = CardView::create(card);
        cardView->showFront(card);
        float x = handCardStartX + i * handCardSpacingX;
        float y = handCardY;

        cardView->setPosition(Vec2(x, y));

        cardView->setOnCardClickCallback([this](int cardId) {
            onHandCardClick(cardId);
            });

        handCardsLayer->addChild(cardView);
        cardViewMap[card.getId()] = cardView;
    }


    // TOP 左下
    const CardModel& topCard = gameModel->getTopCard();
    
    if (topCard.getId() != -1) {
        CardView* topCardView = CardView::create(topCard);
        topCardView->showFront(topCard);
        topCardView->setPosition(Vec2(topCardX, topCardY));
        topCardView->setTouchEnabled(false); // TOP 不可点击

        topCardLayer->addChild(topCardView);
        cardViewMap[topCard.getId()] = topCardView;
        
    }


    // 更新 Undo 可用状态
    updateUndoButton(gameController->canUndo());
}

void GameView::onTableCardClick(int cardId) {
    if (!gameController) return;

    if (gameController->handleTableClick(cardId)) {
        playFromTableToTopAnimation(cardId);
    }
    updateUndoButton(gameController->canUndo());
}

void GameView::onHandCardClick(int cardId) {
    if (!gameController) return;

    gameController->handleHandClick(cardId);
    playFromHandToTopAnimation(cardId);
    updateUndoButton(gameController->canUndo());
}

void GameView::onUndoButtonClick() {
    if (!gameController) return;

    const_cast<GameController*>(gameController)->handleUndoClick();
    playUndoAnimation();
    updateUndoButton(gameController->canUndo());
}

void GameView::playFromTableToTopAnimation(int cardId) {
    CardView* cardView = findCardViewById(cardId);
    if (!cardView) return;

    cardView->playMoveAnimation(Vec2(topCardX, topCardY), 0.1f, [this]() {
        refreshAllCards();

        });
}

void GameView::playFromHandToTopAnimation(int cardId) {
    CardView* cardView = findCardViewById(cardId);
    if (!cardView) return;

    cardView->playMoveAnimation(Vec2(topCardX, topCardY), 0.1f, [this]() {
        refreshAllCards();
        });
}


void GameView::playUndoAnimation() {
    // 目前简单处理：直接刷新
    refreshAllCards();
}

void GameView::updateUndoButton(bool canUndo) {
    if (undoButton) {
        undoButton->setEnabled(canUndo);
        undoButton->setBright(canUndo);
    }
}

CardView* GameView::findCardViewById(int cardId) {
    auto it = cardViewMap.find(cardId);
    if (it != cardViewMap.end()) {
        return it->second;
    }
    return nullptr;
}

void GameView::removeCardViewById(int cardId) {
    auto it = cardViewMap.find(cardId);
    if (it != cardViewMap.end()) {
        it->second->removeFromParent();
        cardViewMap.erase(it);
    }
}