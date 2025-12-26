#pragma once
#ifndef CARDMODEL_H
#define CARDMODEL_H
#include <string>
#include"../configs/enums/CardDefine.h"
class CardModel {
private:

	int id;
	CardFaceType number;
	CardSuitType suit;
	bool isVisible;//·­¿ª
public:	
	CardModel(){}
	CardModel::CardModel(int _id, CardFaceType _number, CardSuitType _suit, bool _isVisible = true) :
		id(_id), number(_number), suit(_suit), isVisible(_isVisible) {
	}
	//setter and getter
	int getId() const { return id; }
	void setId(int _id) { id = _id; }

	CardFaceType getNumber() const { return number; }
	void setNumber(CardFaceType _number) { number = _number; }
	
	CardSuitType getSuit() const { return suit; }
	void setSuit(CardSuitType _suit) { suit = _suit; }
	
	bool getIsVisible() const { return isVisible; }
	void setIsVisible(bool _isVisible) { isVisible = _isVisible; }
};
#endif