纸牌消除游戏 - Card Match Game

## 项目概述

这是一个基于 Cocos2d-x 引擎开发的纸牌消除游戏，采用 MVC 架构，实现了卡牌匹配、回退等核心功能。

### 核心功能

1. **卡牌匹配**：点击桌面牌，如果点数与顶部牌相差1，则可以消除
2. **手牌替换**：点击手牌区的牌，直接替换顶部牌（无需匹配）
3. **回退功能**：支持多步回退操作，恢复之前的游戏状态

### 技术栈

- **引擎**：Cocos2d-x (C++)
- **架构**：MVC (Model-View-Controller)
- **配置**：JSON 格式的关卡配置文件
- **平台**：Windows (Win32)
- **分辨率**：1080 x 2080 (竖屏)

### 演示视频

<video src="D:\cocos2d-x-3.17.2\cocos-project\CardGame\example.mp4"></video>

------

## 项目结构

```
CardGame/
├── Classes/                          # 所有游戏逻辑代码
│   ├── configs/                      # 静态配置
│   │   ├── enums/
│   │   │   └── CardDefine.h         # 卡牌枚举定义（花色和号码）
│   │   ├── models/
│   │   │   ├── CardResourcesConfig.h/cpp  # 卡牌资源配置
│   │   │   ├── LevelCardConfig.h    # 关卡卡牌配置
│   │   │   └── LevelConfig.h/cpp    # 关卡配置
│   │   ├── loaders/
│   │       └── LevelConfigLoader.h/cpp  # 配置加载器
│   │
│   ├── models/                       # 数据模型层
│   │   ├── CardModel.h/cpp          # 卡牌数据模型
│   │   ├── GameModel.h/cpp          # 游戏数据模型
│   │   └── UndoModel.h/cpp          # 回退数据模型
│   │
│   ├── views/                        # 视图层
│   │   ├── CardView.h/cpp           # 卡牌视图
│   │   ├── GameView.h/cpp           # 游戏主视图
│   │   └── GameScene.h/cpp          # 游戏场景
│   │
│   ├── controllers/                  # 控制器层
│   │   └── GameController.h/cpp     # 游戏主控制器
│   │
│   ├── managers/                     # 管理器层
│   │   └── UndoManager.h/cpp        # 回退管理器
│   │
│   ├── services/                     # 服务层
│   │   └── CardMatchService.h/cpp   # 卡牌匹配服务
│   │
│   ├── utils/                        # 工具类，暂用不到
│   │   
│   │
│   └── AppDelegate.h/cpp             # 应用程序入口
│
├── Resources/                        # 资源文件
│   ├── suits/                        # 花色
│   │   ├── spade.png              # 黑桃
│   │   ├── heart.png              # 红心
│   │   ├── ...                      
│   └── /numbers/                          #号码 
│   │   ├── big_black_1.png             
│   │   ├── small_black_1.png  
│   │   ├── big_black_2.png                 
│   │   ├── ... 
	├── card_general.png	#牌面
│   │   	
	└── undo_selected.png	#undo
│   │   	
	└── undo_normal.png		#undo
│   │   
	└──	level_01.json	#关卡配置数据
│   │   
	└──	level_02.json 
│   │   
	└──	level_03.json
│   │   
	└──	level_04.json 
│
└── proj.win32/                       # Windows 项目文件
    └── CardGame.vcxproj
```

------

## 架构设计

### MVC 架构图

```
┌─────────────────────────────────────────────────────────┐
│                        View 层                           │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │  CardView    │  │  GameView    │  │  GameScene   │  │
│  │  (卡牌显示)  │  │  (游戏界面)  │  │  (场景容器)  │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
└────────────┬────────────────────────────────────────────┘
             │ 回调通知
             ↓
┌─────────────────────────────────────────────────────────┐
│                     Controller 层                        │
│  ┌──────────────────────────────────────────────────┐   │
│  │          GameController (游戏主控制器)             │   │
│  │  - handleTableClick()  处理桌面牌点击        		 │   │
│  │  - handleHandClick()   处理手牌点击          	  │   │
│  │  - handleUndoClick()       处理回退               │   │
│  └──────────────────────────────────────────────────┘   │
└────────────┬─────────────────┬──────────────────────────┘
             │                 │
             │ 更新数据        │ 使用服务
             ↓                 ↓
┌─────────────────────┐  ┌─────────────────────┐
│     Model 层         │  │   Service 层         │
│  ┌────────────────┐ │  │  ┌────────────────┐ │
│  │  CardModel     │ │  │  │ CardMatchService││
│  │  GameModel     │ │  │  │ (匹配判断)      │ │
│  │  UndoModel     │ │  │  └────────────────┘ │
│  └────────────────┘ │  └─────────────────────┘
└─────────────────────┘
             ↑
             │ 使用
             │
┌─────────────────────┐
│    Manager 层        │
│  ┌────────────────┐ │
│  │  UndoManager   │ │
│  │  (回退管理)    │ │
│  └────────────────┘ │
└─────────────────────┘
```

### 层次职责

#### 1. Models 层（数据模型）

- **职责**：存储游戏运行时数据，不包含业务逻辑

- 示例：

  - `CardModel`：单张卡牌数据（花色、点数、ID、可见状态）
  - `GameModel`：游戏数据（桌面牌、手牌、顶部牌）
  - `UndoModel`：回退操作数据
  
- **特点**：纯数据类，支持拷贝

#### 2. Services 层（服务）

- **职责**：提供无状态的业务逻辑服务

- 示例：

  - `CardMatchService`：判断卡牌是否可以匹配（点数差1）

- **特点**：静态方法，不持有数据

#### 3. Managers 层（管理器）

- **职责**：管理特定领域的数据和逻辑

- 示例：

  - `UndoManager`：管理回退操作历史栈

- **特点**：作为 Controller 成员，持有数据，不使用单例

#### 4. Controllers 层（控制器）

- **职责**：协调 Model 和 View，处理业务逻辑

- 示例：

  - `GameController`：管理游戏流程，处理用户操作

- **特点**：连接 Model 和 View，调用 Service 和 Manager

#### 5. Views 层（视图）

- **职责**：显示界面，响应用户输入

- 示例：

  - `CardView`：显示单张卡牌，处理点击
  - `GameView`：管理游戏界面布局
  - `GameScene`：游戏场景容器
  
- **特点**：通过回调与 Controller 通信，不包含业务逻辑

#### 6. Configs 层（配置）

- **职责**：存储和加载静态配置

- 示例：

  - `LevelConfigLoader`：从 JSON 加载配置
  - `CardResConfig`：卡牌资源路径配置
  
- **特点**：静态配置，运行时不修改

------

## 核心功能实现

### 1. 卡牌匹配逻辑

#### 匹配规则

- 桌面牌点数与顶部牌点数相差1即可匹配
- 无花色限制
- 例如：顶部牌是4，可以匹配3或5

### 2. 手牌替换

#### 规则

- 点击手牌区的牌，直接替换顶部牌
- 无需匹配判断
- 通常点击末尾手牌

### 3. 回退功能

#### 规则

- 若回退按钮亮起，说明可回退。点击回退按钮即可回退卡牌

#### 回退数据结构

```cpp
class UndoModel {
    OperationType type;           // 操作类型（桌面→顶部 or 手牌→顶部）
    CardModel movedCard;          // 移动的卡牌
    CardModel originalTopCard;    // 原顶部牌
};
```

#### 回退栈管理

```cpp
// UndoManager.cpp
class UndoManager {
    std::vector<UndoModel> undoStack;  // 回退栈
    
    void save(const UndoModel& undoModel);  // 保存操作
    UndoModel undo();                         // 弹出操作
    bool canUndo();                          // 判断是否可回退
};
```

------

## 动画效果

### 1. 点击反馈动画

- **效果**：卡牌放大到 1.1 再恢复到 1.0
- **时长**：0.1 秒
- **触发**：用户点击卡牌时

### 2. 移动动画

- **效果**：卡牌平移到目标位置
- **时长**：0.1 秒
- **触发**：卡牌匹配成功后移动到顶部

### 3. 翻转动画（已实现但未使用）

- **效果**：卡牌水平翻转，切换正面/背面
- **时长**：0.1 秒
- **说明**：当前游戏中所有卡牌都是翻开的，此动画暂未使用

------

## 配置文件

### 关卡配置格式（JSON）

json

```json


{
  "levelId": 1,
  "tableCards": [
    {
      "suit": 2,
      "number": 3,
      "x": 200,
      "y": 600,
      "isVisible": true,
      "id": 1
    },
    {
      "suit": 0,
      "number": 2,
      "x": 400,
      "y": 600,
      "isVisible": true,
      "id": 2
    },
    {
      "suit": 3,
      "number": 3,
      "x": 600,
      "y": 600,
      "isVisible": true,
      "id": 3
    },
    {
      "suit": 1,
      "number": 5,
      "x": 800,
      "y": 600,
      "isVisible": true,
      "id": 4
    },
    {
      "suit": 2,
      "number": 2,
      "x": 200,
      "y": 400,
      "isVisible": true,
      "id": 5
    },
    {
      "suit": 0,
      "number": 3,
      "x": 400,
      "y": 400,
      "isVisible": true,
      "id": 6
    }
  ],
  "handCards": [
    {
      "suit": 1,
      "number": 1,
      "x": 400,
      "y": 200,
      "isVisible": true,
      "id": 7
    },
    {
      "suit": 0,
      "number": 3,
      "x": 500,
      "y": 200,
      "isVisible": true,
      "id": 8
    },
    {
      "suit": 2,
      "number": 4,
      "x": 600,
      "y": 200,
      "isVisible": true,
      "id": 9
    }
  ],
  "topCard": {
    "suit": 3,
    "number": 4,
    "x": 540,
    "y": 1000,
    "isVisible": true,
    "id": 10
  }
}
```

------

## 编译和运行

### 环境要求

- **操作系统**：Windows 10/11
- **开发工具**：Visual Studio 2019 或更高版本
- **引擎版本**：Cocos2d-x 3.x 或 4.x
- **SDK**：Windows SDK 10.0

### 编译步骤

1. **打开项目**

```
   双击打开 proj.win32/CardGame.sln
```

1. 配置平台
   - 选择 Win32 或 x64 平台
   - 选择 Debug 或 Release 模式
2. 编译
   - 点击"生成" → "生成解决方案"（Ctrl+Shift+B）
3. 运行
   - 点击"调试" → "开始执行（不调试）"（Ctrl+F5）

------

## 性能优化建议

### 1. 对象池

对于频繁创建销毁的对象（如 CardView），可以使用对象池：

cpp

```cpp
class CardViewPool {
    std::vector<CardView*> _pool;
public:
    CardView* obtain();
    void recycle(CardView* view);
};
```

### 2. 批量渲染

将多个卡牌合并到一个批次渲染：

cpp

```cpp
auto batchNode = SpriteBatchNode::create("cards/card_atlas.png");
// 所有卡牌作为子节点添加到 batchNode
```

### 3. 减少字符串拷贝

使用引用传递字符串：

cpp

```cpp
// 推荐
void function(const std::string& str);

// 不推荐
void function(std::string str);
```

------

## 调试技巧

### 1. 日志输出

使用 Cocos2d-x 的日志系统：

cpp

```cpp
CCLOG("Card clicked: id=%d, value=%s", cardId, value.c_str());
```

### 2. 断点调试

在 Visual Studio 中设置断点：

cpp

```cpp
bool GameController::handleTableCardClick(int cardId) {
    // 在这里设置断点
    CardModel* card = _gameModel->getTableCardById(cardId);
    
    if (!card) {
        return false;  // 检查 card 是否为空
    }
    // ...
}
```

------

## 已知问题和限制

### 当前限制

1. **单关卡**：目前只支持加载一个关卡(每次运行，随机加载四个关卡中的一个)，没有关卡选择界面
2. **固定布局**：卡牌位置在代码中硬编码，不够灵活
3. **无音效**：没有添加音效和背景音乐
4. **无动画优化**：回退动画较简单

### 待改进功能

1. **关卡选择**：添加关卡选择界面
2. **计分系统**：添加分数、星级评价
3. **提示功能**：高亮可匹配的卡牌
4. **音效系统**：添加点击、匹配、回退的音效
5. **数据持久化**：保存游戏进度和最高分



