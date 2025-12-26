#include "CardView.h"
#include "../configs/models/CardResourcesConfig.h"

USING_NS_CC;
//参考CREATE_FUNC
CardView* CardView::create(const CardModel& cardModel) {
    CardView* ret = new (std::nothrow)CardView();
    if (ret && ret->init(cardModel)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::init(const CardModel& cardModel) {
    if (!Node::init()) {
        return false;
    }

    cardId = cardModel.getId();
    suit = cardModel.getSuit();
    number = cardModel.getNumber();
    isFrontVisible = cardModel.getIsVisible();
    
    // 设置节点尺寸
    setContentSize(CardResourcesConfig::getCardSize());//Node类的函数

    // 初始化卡牌精灵
    initCardSprite(cardModel);

    // 初始化触摸监听
    initTouchListener();

    return true;
}

void CardView::initCardSprite(const CardModel& cardModel) {
    // 根据可见状态选择正面或背面图片
    /*std::string imagePath = CardResoucesConfig::resPath;
    if (cardModel.getIsVisible()) {
        imagePath = CardResoucesConfig::getCardFrontImage();
    }
    else {
        imagePath = CardResoucesConfig::getCardBackImage();
    }*/
    if (isFrontVisible) {
        showFront(cardModel);
    }
    else {
        showBack();
    }
    

}
void CardView::showFront(const CardModel& cardModel) {
    
    std::string path = CardResourcesConfig::getCardFrontImage(/*...*/);
    if (generalSprite) {
        // 已经创建过：只换贴图即可（不需要再 addChild）
        generalSprite->setTexture(path);
        generalSprite->setVisible(true);
    }
    else {
        // 第一次：创建并挂到节点树
        generalSprite = cocos2d::Sprite::create(path);
        generalSprite->setScale(0.8);
        if (!generalSprite) {
            CCLOG("ERROR: failed to load sprite: %s", path.c_str());
            return; // 或者创建占位图
        }

        generalSprite->setPosition(getContentSize().width * 0.5f,
            getContentSize().height * 0.5f);
        addChild(generalSprite, 0);
    }

    // 1) suitSprite
    {
        std::string suitPath = CardResourcesConfig::getSuitImage(cardModel.getSuit());
        CCLOG("suitPath:%s\n", suitPath.c_str());
        if (!suitSprite) {
            suitSprite = Sprite::create(suitPath);
            suitSprite->setScale(0.8);
            if (!suitSprite) {
                CCLOG("ERROR: failed to load suit sprite: %s", suitPath.c_str());
            }
            else {
                suitSprite->setPosition(getContentSize().width * 0.75f,getContentSize().height * (5.0f / 6.0f));
                this->addChild(suitSprite, 1);
            }
        }
        else {
            suitSprite->setTexture(suitPath);
            suitSprite->setVisible(true);
        }
    }

    // 2) SmallFaceSprite
    {
        std::string smallFacePath =CardResourcesConfig::getFaceImage(cardModel.getSuit(), cardModel.getNumber(), 0);
        CCLOG("smallFacePath:%s\n", smallFacePath.c_str());

        if (!SmallFaceSprite) {
            SmallFaceSprite = Sprite::create(smallFacePath);
            SmallFaceSprite->setScale(0.8);
            if (!SmallFaceSprite) {
                CCLOG("ERROR: failed to load small face sprite: %s", smallFacePath.c_str());
            }
            else {
                SmallFaceSprite->setPosition(getContentSize().width * 0.25f,getContentSize().height * (5.0f / 6.0f));
                this->addChild(SmallFaceSprite, 1);
            }
        }
        else {
            SmallFaceSprite->setTexture(smallFacePath);
            SmallFaceSprite->setVisible(true);
        }
    }

    // 3) BigFaceSprite
    {
        std::string bigFacePath =
            CardResourcesConfig::getFaceImage(cardModel.getSuit(), cardModel.getNumber(), 1);
        CCLOG("bigFacePath:%s\n", bigFacePath.c_str());
        if (!BigFaceSprite) {
            BigFaceSprite = Sprite::create(bigFacePath);
            BigFaceSprite->setScale(0.8);
            if (!BigFaceSprite) {
                CCLOG("ERROR: failed to load big face sprite: %s", bigFacePath.c_str());
            }
            else {
                BigFaceSprite->setPosition(getContentSize().width * 0.5f,  getContentSize().height / 3.0f);
                this->addChild(BigFaceSprite, 1);
            }
        }
        else {
            BigFaceSprite->setTexture(bigFacePath);
            BigFaceSprite->setVisible(true);
        }
    }

}
void CardView::showBack() {
    
}
void CardView::initTouchListener() {
    //一次触摸只允许一个节点接管
    touchListener = EventListenerTouchOneByOne::create();
    //点击不会穿透到下层节点
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool CardView::onTouchBegan(Touch* touch, Event* event) {
    // 获取触摸点在世界坐标系中的位置
    Vec2 touchPos = touch->getLocation();

    // 转换为节点本地坐标
    Vec2 localPos = this->convertToNodeSpace(touchPos);

    // 检查是否点击在卡牌区域内
    Rect rect = Rect(0, 0, getContentSize().width, getContentSize().height);
    if (rect.containsPoint(localPos)) {
        // 播放点击反馈动画
        playScaleAnimation();
        return true;
    }

    return false;
}

void CardView::onTouchEnded(Touch* touch, Event* event) {
    // 触发点击回调
    if (onCardClickCallback) {
        onCardClickCallback(cardId);
    }
}

void CardView::setOnCardClickCallback(const OnCardClickCallback& callback) {
    onCardClickCallback = callback;
}
//将数据更新到view里
void CardView::updateDisplay(const CardModel& cardModel) {
    cardId = cardModel.getId();
    suit = cardModel.getSuit();
    number = cardModel.getNumber();


    // 更新卡牌图片
    if (cardModel.getIsVisible()) {
        showFront(cardModel);
    }
    else {
        showBack();
    }
}

void CardView::playMoveAnimation(const Vec2& targetPos,float duration,const std::function<void()>& callback) {
    auto moveTo = MoveTo::create(duration, targetPos);
    
    if (callback) {
        //按顺序先执行移动，再回调
        auto callbackAction = CallFunc::create(callback);
        auto sequence = Sequence::create(moveTo, callbackAction, nullptr);
        this->runAction(sequence);
    }
    else {
        this->runAction(moveTo);
    }
}

void CardView::playFlipAnimation(bool showFront, float duration,const std::function<void()>& callback) {
    // 翻转动画：先缩放到0（翻到一半），切换图片，再缩放回1
    auto scaleToZero = ScaleTo::create(duration / 2, 0.0f, 1.0f);

    auto changeTexture = CallFunc::create([this, showFront]() {
        CardModel tempModel(cardId, number, suit,true);
        this->showFront(tempModel);
        });

    auto scaleToOne = ScaleTo::create(duration / 2, 1.0f, 1.0f);

    if (callback) {
        auto callbackAction = CallFunc::create(callback);
        auto sequence = Sequence::create(scaleToZero, changeTexture,scaleToOne, callbackAction, nullptr);
        this->runAction(sequence);
    }
    else {
        auto sequence = Sequence::create(scaleToZero, changeTexture,scaleToOne, nullptr);
        this->runAction(sequence);
    }
}

void CardView::playScaleAnimation(float duration) {
    // 点击反馈：先放大到1.2，再恢复到1.0
    auto scaleDown = ScaleTo::create(duration, 1.0f);
    auto scaleUp = ScaleTo::create(duration, 1.2f);
    auto sequence = Sequence::create(scaleUp, scaleDown, nullptr);
    this->runAction(sequence);
}

void CardView::setTouchEnabled(bool enabled) {
    if (touchListener) {
        touchListener->setEnabled(enabled);
    }
}