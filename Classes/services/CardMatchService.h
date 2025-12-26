#ifndef CARDMATCHSERVICE_H
#define CARDMATCHSERVICE_H
#include<string>
#include<vector>
#include"../models/CardModel.h"
#include"../utils/CardTransform.h"
#include"../configs/enums/CardDefine.h"
#include<string>
class CardMatchService {
private:

public:
	/*static bool canMatch(const CardModel& card1, const CardModel& card2) {
		bool matchResult = CardTransform::isMatched(card1.getNumber(), card2.getNumber());
		return matchResult;
	}*/
	static CardFaceType CardMatchService::getCardValue(const CardFaceType number);
	static bool canMatch(const CardFaceType number1, const CardFaceType number2);
	
};
#endif