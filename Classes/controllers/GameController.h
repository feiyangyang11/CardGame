#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include"../models/GameModel.h"
#include"../models/UndoModel.h"
#include"../models/CardModel.h"
#include"../managers/UndoManager.h"
//#include"../views/GameView.h"
#include"../services/CardMatchService.h"
#include"../configs/loaders/LevelConfigLoader.h"
class GameView;

class GameController {
private:
	GameModel* gameModel;
	GameView* gameView;
	UndoManager undoManager;

	void executeFromTableToTop(const CardModel&card);//从桌牌到顶牌
	void executeFromHandToTop(const CardModel& card);//从手牌到顶牌
	void executeUndo();
public:
	GameController(){
		gameView = nullptr;
		gameModel = new GameModel();
	}
	~GameController() {
		if (gameModel != nullptr) {
			delete gameModel;
			gameModel = nullptr;
		}
	}

	GameView* getGameView() { return gameView; }
	void setGameView(GameView* view){ gameView = view; }
	GameModel* getGameModel() { return gameModel; }
	void setGameModel(GameModel* model){ gameModel = model; }

	//void loadGame(int levelId);
	void initGame(const std::vector<CardModel>& tableCards, const std::vector<CardModel>& handCards, const CardModel& topCard);
	
	bool handleTableClick(int cardId);
	void handleHandClick(int cardId);
	void handleUndoClick();
	
	bool canUndo(){return undoManager.canUndo();}
};
#endif