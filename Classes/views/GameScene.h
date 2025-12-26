
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"
#include"../controllers/GameController.h"
#include"GameView.h"

// 前向声明
class GameController;
class GameView;

/**
 * @class GameScene
 * @brief 游戏场景类
 *
 * 职责：
 * - 作为游戏的顶层容器
 * - 创建和管理 GameController 和 GameView
 * - 协调 Controller 和 View 的关系
 */
class GameScene : public cocos2d::Scene {
    
public:
    /**
     * @brief 创建游戏场景
     */
    //static GameScene* create();
     CREATE_FUNC(GameScene);
    /**
     * @brief 初始化
     */
    virtual bool init() override;

    /**
     * @brief 析构函数
     */
    virtual ~GameScene();

private:
    GameController* gameController;  // 游戏控制器
    GameView* gameView;              // 游戏视图
};

#endif // __GAME_SCENE_H__