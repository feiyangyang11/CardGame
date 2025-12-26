#ifndef LEVEL_CONFIG_LOADER_H
#define LEVEL_CONFIG_LOADER_H

#include "../models/LevelConfig.h"
#include <string>

/**
 * 职责：
 * - 从JSON配置文件加载关卡数据
 * - 解析JSON并生成 LevelConfig 对象
 * - 提供配置文件路径管理
 *
 * 使用场景：
 * - GameController 初始化时调用加载关卡配置
 * - 支持从文件加载或直接创建测试配置

 */
class LevelConfigLoader {
public:
    /**
     * @note 文件路径格式：configs/datas/level_{levelId}.json
     */
    static LevelConfig loadLevelConfig(int levelId);

    /**
     * @brief 从JSON字符串加载配置（用于测试）
     * @param jsonStr JSON字符串
     * @return 解析成功返回配置对象，失败返回空配置
     */
    static LevelConfig loadFromJsonString(const std::string& jsonStr);

    /**
     * @brief 创建默认测试关卡配置（用于笔试演示）
     * @return 默认配置对象
     *
     * @note 创建简单的测试数据，无需配置文件
     */
    static LevelConfig createDefaultTestLevel();

private:
    /**
     * @brief 解析JSON对象为 LevelConfig
     * @param jsonValue JSON根节点
     * @return 解析后的配置对象
     */
    static LevelConfig parseJsonToConfig(const void* jsonValue);

    /**
     * @brief 获取关卡配置文件路径
     * @param levelId 关卡ID
     * @return 配置文件完整路径
     */
    static std::string getLevelConfigPath(int levelId);

    // 禁止实例化
    LevelConfigLoader() = delete;
    ~LevelConfigLoader() = delete;
};

#endif // __LEVEL_CONFIG_LOADER_H__#pragma once
