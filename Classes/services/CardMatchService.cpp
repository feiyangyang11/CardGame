#include"CardMatchService.h"
CardFaceType CardMatchService::getCardValue(const CardFaceType number) {
	switch (number) {
	case CardFaceType::CFT_ACE:
		return CardFaceType::CFT_ACE;
		break;
	case CardFaceType::CFT_TWO:
		return CardFaceType::CFT_TWO;
		break;
	case CardFaceType::CFT_THREE:
		return CardFaceType::CFT_THREE;
		break;
	case CardFaceType::CFT_FOUR:
		return CardFaceType::CFT_FOUR;
		break;
	case CardFaceType::CFT_FIVE:
		return CardFaceType::CFT_FIVE;
		break;
	case CardFaceType::CFT_SIX:
		return CardFaceType::CFT_SIX;
		break;
	case CardFaceType::CFT_SEVEN:
		return CardFaceType::CFT_SEVEN;
		break;
	case CardFaceType::CFT_EIGHT:
		return CardFaceType::CFT_EIGHT;
		break;
	case CardFaceType::CFT_NINE:
		return CardFaceType::CFT_NINE;
		break;
	case CardFaceType::CFT_TEN:
		return CardFaceType::CFT_TEN;
		break;
	case CardFaceType::CFT_JACK:
		return CardFaceType::CFT_JACK;
		break;
	case CardFaceType::CFT_QUEEN:
		return CardFaceType::CFT_QUEEN;
		break;
	case CardFaceType::CFT_KING:
		return CardFaceType::CFT_KING;
		break;
	}
	return CardFaceType::CFT_NONE;
}

bool CardMatchService::canMatch(const CardFaceType number1, const CardFaceType number2) {
	CardFaceType num1 = CardMatchService::getCardValue(number1);
	CardFaceType num2 = CardMatchService::getCardValue(number2);
	if (num1 == CardFaceType::CFT_NONE || num2 == CardFaceType::CFT_NONE) {
		return false;
	}
	//—≠ª∑∆•≈‰Q∫ÕA
	if ((num1 == CardFaceType::CFT_ACE && num2 == CardFaceType::CFT_QUEEN)
		|| (num1 == CardFaceType::CFT_QUEEN && num2 == CardFaceType::CFT_ACE)) {
		return true;
	}
	return abs(static_cast<int>(num1) - static_cast<int>(num2)) == 1;
}