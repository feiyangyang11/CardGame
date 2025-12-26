#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H
#include<iostream>
#include<string>
#include"CardModel.h"
class UndoModel {
public:
	enum class OperationType {
		FROM_TABLE,	//来自桌牌堆
		FROM_HAND	//来自手牌堆
	};
private:
	OperationType operationType;//操作类型
	CardModel movedCard;//移动的牌
	CardModel originalTopCard;//原来顶部的牌
public:
	UndoModel(){}
	UndoModel(OperationType _operationType, CardModel _movedCard, CardModel _originalTopCard = CardModel()) :
		operationType(_operationType), movedCard(_movedCard), originalTopCard(_originalTopCard) {}
	//getter and setter
	OperationType getOperationType() { return operationType; }
	CardModel& getMovedCard() { return movedCard; }
	CardModel& getOriginalTopCard() { return originalTopCard; }
	
	void setOperationType(OperationType& _operationType) { operationType = _operationType; }
	void setMovedCard(CardModel& _movedCard) { movedCard = _movedCard; }
	void setOriginalTopCard(CardModel& _originalTopCard) { originalTopCard = _originalTopCard; }


};
#endif