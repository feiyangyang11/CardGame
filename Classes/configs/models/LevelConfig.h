
#ifndef LEVEL_CONFIG_H
#define LEVEL_CONFIG_H

#include "LevelCardConfig.h"
#include <vector>

/**
 * 使用场景：
 * - LevelConfigLoader 加载配置后生成此对象
 * - GameController 初始化游戏时使用此配置
 */
class LevelConfig {
private:
    int levelId;                            // 关卡ID
    std::vector<LevelCardConfig> tableCards; // 桌面牌配置
    std::vector<LevelCardConfig> handCards;  // 手牌配置
    LevelCardConfig topCard;                 // 顶部牌配置

public:
    /**
     * @brief 默认构造函数
     */
    LevelConfig(){}

    /**
     * @brief 带参构造函数
     * @param levelId 关卡ID
     */
    LevelConfig(int _levelId):levelId(_levelId){}

    // Getters
    int getLevelId() { return levelId; }
   std::vector<LevelCardConfig>& getTableCards() { return tableCards; }
   std::vector<LevelCardConfig>& getHandCards()  { return handCards; }
   LevelCardConfig& getTopCard()  { return topCard; }

    // Setters
    void setLevelId(int id) { levelId = id; }
    void setTableCards(std::vector<LevelCardConfig>& cards) { tableCards = cards; }
    void setHandCards(std::vector<LevelCardConfig>& cards) { handCards = cards; }
    void setTopCard( LevelCardConfig& card) { topCard = card; }

    /**
     * @brief 添加桌面牌配置
     */
    void addTableCard(const LevelCardConfig& card) { tableCards.push_back(card); }

    /**
     * @brief 添加手牌配置
     */
    void addHandCard(const LevelCardConfig& card) { handCards.push_back(card); }

    /**
     * @brief 清空所有配置
     */
    void clear();


};
#endif // __LEVEL_CONFIG_H__
