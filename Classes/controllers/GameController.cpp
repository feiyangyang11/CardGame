#include"GameController.h"

void error(const std::string& message){
	std::cout << message << std::endl;
}


//void GameController::loadGame(int levelId) {
//	if (levelId <= 0) {
//		CCLOG("Invalid levelId in loadGame()\n");
//		return;
//	}
//	LevelConfig levelConfig = LevelConfigLoader::loadLevelConfig(levelId);
//
//	std::vector<CardModel>tbs, hds;//tablecards,handcards
//	CardModel tpc;//topcard
//	
//	for (auto&cfg:levelConfig.getTableCards()) {
//		CardModel model(cfg.id, cfg.number, cfg.suit, cfg.isVisible);
//		tbs.push_back(model);
//	}
//	for (auto& cfg : levelConfig.getHandCards()) {
//		CardModel model(cfg.id, cfg.number, cfg.suit, cfg.isVisible);
//		hds.push_back(model);
//	}
//	CardModel model(levelConfig.getTopCard().id, levelConfig.getTopCard().number, 
//		levelConfig.getTopCard().suit, levelConfig.getTopCard().isVisible);
//
//	initGame(tbs, hds, model);
//	/*if (gameView) {
//		gameView->refreshAllCards();
//	}*/
//}

void GameController::initGame(const std::vector<CardModel>& tableCards, const std::vector<CardModel>& handCards, const CardModel& topCard) {
	if (gameModel == nullptr) {
		error("gameModel ptr is nullptr in initGame()");
		return;
	}
	
	gameModel->setTableCards(tableCards);
	gameModel->setHandCards(handCards);
	gameModel->setTopCard(topCard);
	undoManager.clear();

}

bool GameController::handleTableClick(int cardId){
	if (gameModel == nullptr) {
		error("gameModel ptr is nullptr in handleTableClick()");
		return false;
	}
	CardModel* clickedCard = gameModel->getTableCardById(cardId);
	CardModel& topCard = gameModel->getTopCard();
	if (clickedCard == nullptr) {
		error("Invalid cardID in handleTableClick()");
		return false;
	}
	if (!clickedCard->getIsVisible()) {
		error("card unvisible in handleTableClick()");
		return false;
	}
	if (!CardMatchService::canMatch(clickedCard->getNumber(), topCard.getNumber())) {
		error("incorrect match in canMatch()");
		return false;
	}
	UndoModel undoCard(UndoModel::OperationType::FROM_TABLE, *clickedCard, gameModel->getTopCard());
	
	executeFromTableToTop(*clickedCard);
	undoManager.save(undoCard);
	if (gameView == nullptr) {
		error("gameView ptr is nullptr in HandleTableClick()");
		return false;
	}
	//gameView->playFromTableToTopAnimation(cardId);
	return true;
}

void GameController::handleHandClick(int cardId){
	if (gameModel == nullptr) {
		error("gameModel ptr is nullptr in handleHandClick()");
		return;
	}
	CardModel* clickedCard = gameModel->getHandCardById(cardId);
	CardModel& topCard = gameModel->getTopCard();
	if (clickedCard == nullptr) {
		error("Invalid cardID in handleHandClick()");
		return;
	}
	if (!clickedCard->getIsVisible()) {
		error("card already flipped over in handleHandClick()");
		return;
	}
	UndoModel undoCard(UndoModel::OperationType::FROM_HAND, *clickedCard, gameModel->getTopCard());
	
	executeFromHandToTop(*clickedCard);
	undoManager.save(undoCard);
	if (gameView == nullptr) {
		error("gameView ptr is nullptr in HandleHandClick()");
		return;
	}
	//gameView->playFromHandToTopAnimation(cardId);
}

void GameController::handleUndoClick(){
	if (gameModel == nullptr) {
		error("gameModel ptr is nullptr in handleUndoClick()");
		return;
	}
	if (!undoManager.canUndo()) {	
		error("undoStack is empty in handleUndoClick()");
		return;
	}
	if (undoManager.peek().getOperationType() != UndoModel::OperationType::FROM_TABLE
		&& undoManager.peek().getOperationType() != UndoModel::OperationType::FROM_HAND) {
		error("Invalid undo operation type in handleUndoClick()");
		return;
	}
	executeUndo();
	if (gameView == nullptr) {
		error("gameView ptr is nullptr in HandleUndoClick()");
		return;
	}

	//gameView->playUndoAnimation();
}
//private
void GameController::executeFromTableToTop(const CardModel& card){
	gameModel->setTopCard(card);
	gameModel->removeTableCardById(card.getId());
	
}
void GameController::executeFromHandToTop(const CardModel& card){
	error("GameController::exec from hand to top logic");
	//gameModel->removeHandCardById(card.getId());
	gameModel->removeHandCard();
	gameModel->setTopCard(card);

}
void GameController::executeUndo(){
	UndoModel model = undoManager.undo();
	gameModel->setTopCard(model.getOriginalTopCard());
	if (model.getOperationType() == UndoModel::OperationType::FROM_TABLE) {
		gameModel->addTableCard(model.getMovedCard());
	}
	else if(model.getOperationType() == UndoModel::OperationType::FROM_HAND) {
		gameModel->addHandCard(model.getMovedCard());
	}

}