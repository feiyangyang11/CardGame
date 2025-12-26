#include"GameModel.h"
#include<iostream>

//×ÀÅÆ
void GameModel::addTableCard(const CardModel& card) { tableCards.push_back(card); }

bool GameModel::removeTableCardById(int cardId) {
	for (auto& it=tableCards.begin();it!=tableCards.end();++it) {
		if (it->getId() == cardId) {
			tableCards.erase(it);
			return true;
		}
	}
	return false;
}
CardModel* GameModel::getTableCardById(int cardId) {
	for (auto& it = tableCards.begin(); it != tableCards.end(); ++it) {
		if (it->getId() == cardId) {
			return &(*it);
		}
	}
	return nullptr;
}
//ÊÖÅÆ

void GameModel::addHandCard(const CardModel& card) { handCards.push_back(card); }

void GameModel::removeHandCard() { handCards.pop_back(); }

bool GameModel::removeHandCardById(int cardId) {
	for (auto& it = handCards.begin(); it != handCards.end(); ++it) {
		if (it->getId() == cardId) {
			tableCards.erase(it);
			return true;
		}
	}
	return false;
}
CardModel* GameModel::getHandCardById(int cardId) {
	for (auto& it = handCards.begin(); it != handCards.end(); ++it) {
		if (it->getId() == cardId) {
			return &(*it);
		}
	}
	return nullptr;
}

void GameModel::clear() {
	tableCards.clear();
	handCards.clear();
	topCard = CardModel();
}