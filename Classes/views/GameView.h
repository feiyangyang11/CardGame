#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include<cocos2d.h>
#include"../models/CardModel.h"
#include"../controllers/GameController.h"
#include"CardView.h"
#include "ui/CocosGUI.h"
#include<map>


/**
 * @class GameView
 * @brief 游戏主视图
 *
 * 职责：
 * - 管理所有卡牌视图的显示
 * - 布局桌面牌区、手牌区、顶部牌区
 * - 响应用户操作并通过回调通知 Controller
 * - 根据 Controller 指令播放动画
 * - 不包含业务逻辑
 *
 * 使用场景：
 * - 作为游戏的主界面
 * - 与 GameController 配合完成游戏交互
 *
 * 设计说明：
 * - 继承自 cocos2d::Layer
 * - 可持有 const GameController* 用于读取数据
 * - 通过回调与 Controller 通信
 */
//class GameController;

class GameView : public cocos2d::Layer {
public:
	GameView(){}

	virtual bool init() override;

    void setGameController( GameController* controller) {gameController = controller;}//设置控制器
    GameController* getGameController() { return gameController; }//设置控制器
	
	void playFromTableToTopAnimation(int cardId);
	
	void playFromHandToTopAnimation(int cardId);
	
	void playUndoAnimation();
	
	void refreshAllCards();//刷新所有卡牌

	void updateUndoButton(bool canUndo);//刷新回退按钮

    CREATE_FUNC(GameView);
private:
    CardView* findCardViewById(int cardId);
    void removeCardViewById(int cardId);
    // UI 初始化
    void initUI();
    void createBackground();
    void createUndoButton();

    // 刷新与布局
    //void refreshAllCards();
    //void updateUndoButton(bool canUndo);

    // 事件回调（View 内部）
    void onTableCardClick(int cardId);
    void onHandCardClick(int cardId);
    void onUndoButtonClick();

    // 动画
    //void playTableCardToTopAnimation(int cardId);
    //void playHandCardToTopAnimation(int cardId);
    //void playUndoAnimation();

    // CardView 管理
    

private:
    GameController* gameController;  // 关联的 Controller

    cocos2d::Node* tableCardsLayer;        
    cocos2d::Node* handCardsLayer;         
    cocos2d::Node* topCardLayer;           

    std::map<int, CardView*> cardViewMap;  // 卡牌ID -> CardView 映射

    cocos2d::ui::Button* undoButton;       

    // 布局常量
   
    const float SCREEN_W = 1080.0f;//屏幕宽
    const float TABLE_H = 1500.0f;//主牌高
    const float HAND_H = 580.0f;//手牌高
    const float SCREEN_H = TABLE_H + HAND_H;//屏幕高

    const float HAND_START_Y = 0.0f;//手牌起始Y坐标
    const float TABLE_START_Y = HAND_H;//桌牌起始Y坐标

    // TABLE 
    const float tablePileLeftX = SCREEN_W * 0.13f;//主牌堆左X坐标
    const float tablePileRightX = SCREEN_W * 0.75f;//主牌堆右X坐标
    const float tablePileStartY = TABLE_START_Y + 1080.0f; // 主牌堆顶部起始Y坐标    1700
    const float tablePileSpacingY = -100.0f;                // 每往下叠一张牌，Y-150

    // HAND 
    const float handCardStartX = SCREEN_W * 0.05f;//手牌堆起始X
    const float handCardY = HAND_START_Y + 220.0f;//手牌堆起始Y
    const float handCardSpacingX = 100.0f;//每往右叠一张牌，X+120
   
    //  UI
    const float undoButtonX = 1000.0f;
    const float undoButtonY = handCardY * 1.5f;
    const float undoSizeX = 128.0f;
    const float undoSizeY = 128.0f;
    // TOP
    const float Gap = 280.0f;   // TOP 与 Undo 的水平间距
    const float topCardX = undoButtonX - Gap;//起始X
    const float topCardY = handCardY; // Y


    


};
#endif // GAME_VIEW_H