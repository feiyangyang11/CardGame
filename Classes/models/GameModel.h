#ifndef GAME_MODEL_H
#define GAME_MODEL_H
#include<string>
#include<vector>
#include"CardModel.h"
class GameModel {
private:
	std::vector<CardModel>tableCards;//◊¿≈∆
	std::vector<CardModel>handCards;// ÷≈∆
	CardModel topCard;//∂•≈∆
public:
	GameModel(){}
	GameModel::GameModel(const std::vector<CardModel>& _tableCards, const std::vector<CardModel>& _handCards, const CardModel& _topCard) :
		tableCards(_tableCards), handCards(_handCards), topCard(_topCard) {
	}
	//◊¿≈∆
	std::vector<CardModel>& getTableCards() { return tableCards; }
	void setTableCards(const std::vector<CardModel>& _tableCards) { tableCards = _tableCards; }

	void addTableCard(const CardModel& card);
	bool removeTableCardById(int cardId);
	CardModel* getTableCardById(int cardId);
	// ÷≈∆
	std::vector<CardModel>& getHandCards() { return handCards; }
	void setHandCards(const std::vector<CardModel>& _handCards) { handCards = _handCards; }

	void addHandCard(const CardModel& card);
	void removeHandCard();
	bool removeHandCardById(int cardId);
	CardModel* getHandCardById(int cardId);
	//∂•≈∆
	CardModel& getTopCard() { return topCard; }
	void setTopCard(const CardModel& _topCard) { topCard = _topCard; }
	void clear();
};
#endif