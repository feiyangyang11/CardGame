#ifndef CARD_VIEW_H
#define CARD_VIEW_H
#include "cocos2d.h"
#include "../models/CardModel.h"
#include"../configs/enums/CardDefine.h"
#include <functional>
/**
 * @class CardView
 * @brief 卡牌视图类
 *
 * 职责：
 * - 显示单张卡牌的UI
 * - 处理卡牌的点击事件
 * - 执行卡牌动画（移动、翻转等）
 * - 不包含业务逻辑，只负责显示和用户交互
 *
 * 使用场景：
 * - GameView 中创建多个 CardView 显示卡牌
 * - 响应用户点击并通过回调通知 Controller
 *
 * 设计说明：
 * - 继承自 cocos2d::Node
 * - 通过回调函数与 Controller 通信
 * - 可持有 const CardModel* 用于读取数据
 */
class CardView : public cocos2d::Node {
public:
    /**
     * @brief 点击回调函数类型
     * @param cardId 被点击的卡牌ID
     */
    using OnCardClickCallback = std::function<void(int cardId)>;

    /**
     * @brief 创建卡牌视图
     * @param cardModel 卡牌数据模型
     * @return CardView 指针
     */
    static CardView* create(const CardModel& cardModel);

    /**
     * @brief 初始化
     */
    virtual bool init(const CardModel& cardModel);

    /**
     * @brief 设置点击回调
     * @param callback 点击回调函数
     */
    void setOnCardClickCallback(const OnCardClickCallback& callback);

    /**
     * @brief 更新卡牌显示（根据 Model 数据刷新）
     * @param cardModel 卡牌数据
     */
    void updateDisplay(const CardModel& cardModel);

    /**
     * @brief 播放移动动画
     * @param targetPos 目标位置
     * @param duration 动画时长（秒）
     * @param callback 动画完成回调
     */
    void playMoveAnimation(const cocos2d::Vec2& targetPos,
        float duration = 0.3f,
        const std::function<void()>& callback = nullptr);

    /**
     * @brief 播放翻转动画（正面/背面切换）
     * @param showFront true显示正面，false显示背面
     * @param duration 动画时长（秒）
     * @param callback 动画完成回调
     */
    void playFlipAnimation(bool showFront,
        float duration = 0.2f,
        const std::function<void()>& callback = nullptr);

    /**
     * @brief 播放缩放动画（点击反馈）
     * @param duration 动画时长（秒）
     */
    void playScaleAnimation(float duration = 0.1f);

    /**
     * @brief 设置卡牌是否可点击
     * @param enabled true可点击，false不可点击
     */
    void setTouchEnabled(bool enabled);

    /**
     * @brief 获取卡牌ID
     */
    int getCardId() const { return cardId; }

    /**
     * @brief 设置卡牌ID
     */
    void setCardId(int cardId) { cardId = cardId; }

private:
    /**
     * @brief 初始化卡牌精灵
     */
    void initCardSprite(const CardModel& cardModel);
    void CardView::showFront(const CardModel& cardModel);
    void CardView::showBack();

    /**
     * @brief 初始化触摸监听
     */
    void initTouchListener();

    /**
     * @brief 触摸开始回调
     */
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief 触摸结束回调
     */
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    cocos2d::Sprite* generalSprite;           // 卡牌精灵
    cocos2d::Sprite* suitSprite;           // 卡牌精灵
    cocos2d::Sprite* BigFaceSprite;           // 卡牌精灵
    cocos2d::Sprite* SmallFaceSprite;           // 卡牌精灵
    cocos2d::EventListenerTouchOneByOne* touchListener;  // 触摸监听器
    OnCardClickCallback onCardClickCallback;  // 点击回调
    int cardId; 
    CardSuitType suit;
    CardFaceType number;
    bool isFrontVisible;                   // 是否显示正面
};

#endif